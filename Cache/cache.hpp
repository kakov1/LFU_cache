#ifndef CACHE_HPP_
#define CACHE_HPP_

template <typename PageT, typename KeyT = int>
class cache_t {
    private:
        const size_t cache_size;
        const size_t pages_amount;
    public:
        struct frequency_node;
        struct cache_node;

        using cache_node_it = typename std::list<cache_node>::iterator;
        using freq_node_it = typename std::list<frequency_node>::iterator;

        struct cache_node {
            PageT page;
            KeyT key;
            freq_node_it freq_node;
        };

        struct frequency_node {
            size_t frequency = 0;
            std::list<cache_node> cache_nodes;
        };
        
        size_t hits = 0;
        
        std::list<frequency_node> frequency_list;
        std::unordered_map<KeyT, cache_node_it> cache_hash_table;

        cache_t(const size_t size, const size_t amount) : cache_size(size), pages_amount(amount)  {}

        int create_cache_node(PageT page, KeyT key) {
            if (frequency_list.size() == 0 or frequency_list.begin()->frequency != 1) {
                create_frequency_node(1, frequency_list.begin());
            }

            cache_node node = {page, key, frequency_list.begin()};
            frequency_list.begin()->cache_nodes.push_front(node);
            cache_hash_table[key] = frequency_list.begin()->cache_nodes.begin();

            return 0;
        }

        freq_node_it create_frequency_node(size_t frequency, freq_node_it position) {
            frequency_node node = {frequency, {}};
            
            return frequency_list.insert(position, node);;
        }

        int add_cache(PageT page, KeyT key) {
            create_cache_node(page, key);

            cache_node_it node = cache_hash_table[key];

            size_t frequency_list_head_value = frequency_list.begin()->frequency;

            if (frequency_list_head_value != 1) {
                create_frequency_node(1, frequency_list.begin());
            }

            node->freq_node = frequency_list.begin();

            return 0;
        }
        
        int delete_least_used() {
            if (frequency_list.size() != 0) {

                if (frequency_list.begin()->cache_nodes.size() != 0) {
                    int key = frequency_list.begin()->cache_nodes.back().key;

                    frequency_list.begin()->cache_nodes.pop_back();
                    cache_hash_table.erase(key);
                }
                else {
                    frequency_list.pop_front();
                }
            }
            return 0;
        }

        bool full() const{
            if (cache_size == cache_hash_table.size()) {
                return true;
            }
            return false;
        } 

        int move_cache_node(cache_node_it hit) {
            size_t new_frequency = hit->freq_node->frequency + 1;
            freq_node_it prev_freq_node = hit->freq_node;
            freq_node_it next_freq_node = std::next(prev_freq_node, 1);

            if (new_frequency != next_freq_node->frequency) {
                next_freq_node = create_frequency_node(new_frequency, next_freq_node);
            }
            
            prev_freq_node->cache_nodes.erase(hit);

            if (prev_freq_node->cache_nodes.size() == 0) {
                frequency_list.erase(prev_freq_node);
            }

            next_freq_node->cache_nodes.push_front(*hit);
            cache_hash_table[hit->key] = next_freq_node->cache_nodes.begin();
            cache_hash_table[hit->key]->freq_node = next_freq_node;

            return 0;
        }

        bool lookup_update(PageT page, KeyT key) {
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

            hits++;

            return true;
        }

        int processing_cache() {
            PageT buf;

            for (int page_num = 0; page_num < pages_amount; page_num++) {
                std::cin >> buf;
                lookup_update(buf, buf);
            }

            return 0;
        }

        int print_hash_table() const {
            std::cout << "Hash table:\n";
            std::cout << "[";

            for (auto element = cache_hash_table.begin();
                element != cache_hash_table.end(); element++) {

                std::cout << "{" << element->first << ", {"
                << element->second->key << ", }}";

                if (++cache_hash_table.find(element->first) != cache_hash_table.end()) {
                    std::cout << ", ";
                }
            }
            std::cout << "]" << '\n';
            return 0;
        }

        int print_frequency_list() const {
            std::cout << "Frequency list:\n";
            std::cout << "[";

            for (auto element = frequency_list.begin();
                 element != frequency_list.end(); element++) {

                std::cout << "{" << element->frequency << ", ";
                print_cache_nodes_list(element->cache_nodes);
                std::cout << "}";

                if (element->frequency != (--frequency_list.end())->frequency) {
                    std::cout << ", ";
                }
            }
            std::cout << "]" << '\n';
            return 0;
        }
        int print_cache_nodes_list(const std::list<cache_node> list) const {
            std::cout << "[";

            for (auto element = list.begin(); element != list.end(); element++) {
                std::cout << element->key;

                if (element != --list.end()) {
                    std::cout << ", ";
                }
            }
            std::cout << "]";
            return 0;
        }
};


#endif