#include "cache.hpp"
#include "../Process/read_and_process.hpp"
#include <iostream>

int main() {
    size_t cache_size, pages_amount;
  
    std::cin >> cache_size >> pages_amount;

    cache_t<size_t, size_t> cache(cache_size, pages_amount);
    processing_cache(cache, pages_amount);

    std::cout << cache.hits << std::endl;

    return 0;
}
