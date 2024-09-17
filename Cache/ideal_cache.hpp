#ifndef IDEAL_CACHE_HPP_
#define IDEAL_CACHE_HPP_

template <typename PageT, typename KeyT = int>
class ideal_cache_t {
    private:
        const size_t cache_size;
        const size_t pages_amount;
    public:
        struct cache_node {
            PageT page;
            KeyT key;
        };

        using cache_node_it = typename std::list<cache_node>::iterator;
        
        size_t hits = 0;

        std::unordered_map<KeyT, cache_node_it> cache_hash_table;
        std::unordered_map<KeyT, std::list<size_t>> pages_hash_table;

        std::list<cache_node> cache_list;
        std::vector<KeyT> pages_list;

        ideal_cache_t(const size_t size, const size_t amount) : cache_size(size), pages_amount(amount)  {}

        int add_cache(PageT page, KeyT key) {

            cache_list.push_front({page, key});

            if (pages_hash_table[key].size() != 0) {
                pages_hash_table[key].pop_front();
            }

            cache_hash_table[key] = cache_list.begin();

            return 0;
        }

        int delete_cache(cache_node_it cache_it) {
            cache_hash_table.erase(cache_it->key);
            cache_list.erase(cache_it);
            
            return 0;
        }
        
        int delete_latest() {
            cache_node_it latest_page_it = cache_list.begin();

            for (cache_node_it node_it = latest_page_it; node_it != cache_list.end(); node_it++) { 
                if (pages_hash_table[node_it->key].size() == 0) {
                    delete_cache(node_it);

                    return 0;
                }
                else {
                    if (pages_hash_table[node_it->key].front() >
                        pages_hash_table[latest_page_it->key].front()) {
                        latest_page_it = node_it;
                    }
                }
            }

            delete_cache(latest_page_it);
            
            return 0;
        }

        bool full() const{
            if (cache_size == cache_hash_table.size()) {
                return true;
            }
            return false;
        } 

        bool lookup_update(PageT page, KeyT key) {

            auto hit = cache_hash_table.find(key);

            if (hit == cache_hash_table.end()) {
                if (pages_hash_table[key].size() == 1) {
                    pages_hash_table[key].pop_front();
                    return false;
                }
                else if (full()) {
                    delete_latest();
                }
                else {
                    add_cache(page, key);
                }
                return false;
            }

            pages_hash_table[key].pop_front();

            hits++;

            return true;
        }

        int read_input_pages() {
            KeyT buf;

            for (size_t page_num = 0; page_num < pages_amount; page_num++) {
                std::cin >> buf;

                pages_hash_table[buf].push_back(page_num);
                pages_list.push_back(buf);
            }

            return 0;
        }

        int processing_cache() {
            read_input_pages();

            for (KeyT key : pages_list) {
                lookup_update(key, key);
            }

            return 0;
        }

};


#endif