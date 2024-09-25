#ifndef IDEAL_CACHE_HPP_
#define IDEAL_CACHE_HPP_

#include <unordered_map>
#include <list>
#include <vector>
#include <cstddef>
#include <cassert>

template <typename KeyT, typename PageT>
class ideal_cache_t {
    private:
        const size_t cache_size;
        const size_t pages_amount;

        struct cache_node {
            PageT page;
            KeyT key;
        };

        using cache_node_it = typename std::list<cache_node>::iterator;

        std::unordered_map<KeyT, cache_node_it> cache_hash_table;
        std::unordered_map<KeyT, std::list<size_t>> pages_hash_table;

        std::list<cache_node> cache_list;
        std::vector<KeyT> pages_list;

        void add_cache(const KeyT& key, const PageT& page) {

            cache_list.push_front({page, key});

            if (!pages_hash_table[key].empty()) {
                pages_hash_table[key].pop_front();
            }

            cache_hash_table[key] = cache_list.begin();
        }

        void delete_cache(cache_node_it cache_it) {
            cache_hash_table.erase(cache_it->key);
            cache_list.erase(cache_it);
        }

        void delete_latest() {
            cache_node_it latest_page_it = cache_list.begin();

            for (cache_node_it node_it = latest_page_it; node_it != cache_list.end(); node_it++) { 
                if (pages_hash_table[node_it->key].empty()) {
                    delete_cache(node_it);

                    return;
                }
                else {
                    if (pages_hash_table[node_it->key].front() >
                        pages_hash_table[latest_page_it->key].front()) {
                        latest_page_it = node_it;
                    }
                }
            }

            delete_cache(latest_page_it);
        }

    public:
        ideal_cache_t(const size_t size, const size_t amount) : cache_size(size), pages_amount(amount)  {}

        bool full() const{
            return cache_size == cache_hash_table.size();
        } 

        bool lookup_update(const KeyT& key, const PageT& page) {

            auto hit = cache_hash_table.find(key);

            if (hit == cache_hash_table.end()) {
                if (pages_hash_table[key].size() == 1) {
                    pages_hash_table[key].pop_front();
                    return false;
                }
                if (full()) {
                    delete_latest();
                }
                add_cache(page, key);
                return false;
            }

            pages_hash_table[key].pop_front();

            return true;
        }

        void add_page(KeyT key, size_t page_num) {
            pages_hash_table[key].push_back(page_num);
            pages_list.push_back(key);
        }

        const KeyT& get_key(size_t page_num) {
            return pages_list[page_num];
        }

};


#endif