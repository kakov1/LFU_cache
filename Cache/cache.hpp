#ifndef CACHE_HPP_
#define CACHE_HPP_

#include <unordered_map>
#include <list>
#include <vector>
#include <cstddef>
#include <cassert>

template <typename KeyT, typename PageT>
class cache_t {
    private:
        const size_t cache_size;
        const size_t pages_amount;

        struct frequency_node;
        struct cache_node;

        using cache_node_it = typename std::list<cache_node>::iterator;
        using freq_node_it = typename std::list<frequency_node>::iterator;

        struct cache_node {
            PageT page;
            KeyT key;
            freq_node_it freq_node;

            cache_node(PageT page_, KeyT key_, freq_node_it freq_node_) :
                       page(page_), key(key_), freq_node(freq_node_) {};
        };

        struct frequency_node {
            size_t frequency = 0;
            std::list<cache_node> cache_nodes = {};

            frequency_node(size_t frequency_) : frequency(frequency_) {};
        };

        std::list<frequency_node> frequency_list;
        std::unordered_map<KeyT, cache_node_it> cache_hash_table;

        void move_cache_node(cache_node_it hit) {
            size_t new_frequency = hit->freq_node->frequency + 1;
            freq_node_it prev_freq_node = hit->freq_node;
            freq_node_it next_freq_node = std::next(prev_freq_node, 1);

            if (new_frequency != next_freq_node->frequency) {
                next_freq_node = create_frequency_node(new_frequency, next_freq_node);
            }
            
            prev_freq_node->cache_nodes.erase(hit);

            if (prev_freq_node->cache_nodes.empty()) {
                frequency_list.erase(prev_freq_node);
            }

            next_freq_node->cache_nodes.push_front(*hit);
            cache_hash_table[hit->key] = next_freq_node->cache_nodes.begin();
            cache_hash_table[hit->key]->freq_node = next_freq_node;
        }

        void delete_least_used() {
            if (!frequency_list.empty()) {

                if (!frequency_list.begin()->cache_nodes.empty()) {
                    const KeyT& key = frequency_list.begin()->cache_nodes.back().key;

                    frequency_list.begin()->cache_nodes.pop_back();
                    cache_hash_table.erase(key);
                }
                else {
                    frequency_list.pop_front();
                }
            }
        }

        void create_cache_node(const KeyT& key, const PageT& page) {

            if (frequency_list.empty() || frequency_list.begin()->frequency != 1) {
                create_frequency_node(1, frequency_list.begin());
            }

            frequency_list.begin()->cache_nodes.emplace_front(page, key, frequency_list.begin());
            cache_hash_table.emplace(key, frequency_list.begin()->cache_nodes.begin());
        }

        freq_node_it create_frequency_node(size_t frequency, freq_node_it position) {            
            return frequency_list.emplace(position, frequency);    
        }

        void add_cache(const KeyT& key, const PageT& page) {
            create_cache_node(page, key);

            cache_node_it node = cache_hash_table[key];

            assert(frequency_list.begin() != frequency_list.end());

            size_t frequency_list_head_value = frequency_list.begin()->frequency;

            if (frequency_list_head_value != 1) {
                create_frequency_node(1, frequency_list.begin());
            }

            node->freq_node = frequency_list.begin();
        }
    public:
        cache_t(const size_t size, const size_t amount) : cache_size(size), pages_amount(amount)  {}

        bool full() const{
            return cache_size == cache_hash_table.size();
        } 

        bool lookup_update(const KeyT& key, const PageT& page) {
            auto hit = cache_hash_table.find(key);

            if (full()) {
                if (hit == cache_hash_table.end()) {
                    delete_least_used();    
                }
            }

            if (hit == cache_hash_table.end()) {
                add_cache(page, key);
                return false;
            }  

            move_cache_node(hit->second);

            return true;
        }
};


#endif