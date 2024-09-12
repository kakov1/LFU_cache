struct frequency_node;
struct cache_node;

struct frequency_node {
    size_t frequency = 0;
    std::list<cache_node> cache_nodes;
};

struct cache_node {
    int index;
    size_t frequency = 0;
    std::list<frequency_node>::iterator freq_node;
};

using cache_node_it = std::list<cache_node>::iterator;
using freq_node_it = std::list<frequency_node>::iterator;

class cache_t {
    private:
        size_t cache_size;
        const size_t pages_amount;
        int least_used_page;
    public:
        size_t hits = 0;
        
        std::list<frequency_node> frequency_list;

        std::unordered_map<int, cache_node_it> cache_hash_table;

        cache_t(const size_t size, const size_t amount) : cache_size(size), pages_amount(amount)  {}

        bool full() const;
        bool empty() const;
        bool lookup_update(int key);
        int add_cache(int key);
        int delete_least_used();
        int read_input_pages(std::vector<int>* list);
        int print_hash_table() const;
        int print_frequency_list() const;
        int print_cache_nodes_list(const std::list<cache_node> node) const;
        int create_cache_node(int key);
        freq_node_it create_frequency_node(size_t frequency, freq_node_it position);
};
