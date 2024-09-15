#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include "ideal_cache.hpp"


int main() {
    size_t cache_size, pages_amount;

    std::cin >> cache_size >> pages_amount;

    ideal_cache_t<size_t, size_t> cache(cache_size, pages_amount);

    cache.read_input_pages();

    cache.processing_cache();

    std::cout << cache.hits << std::endl;

    return 0;
}
