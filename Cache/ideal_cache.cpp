#include "ideal_cache.hpp"
#include "read_and_process.hpp"
#include <iostream>

int main() {
    size_t cache_size, pages_amount;

    std::cin >> cache_size >> pages_amount;

    is_cin_good();

    ideal_cache_t<size_t, size_t> cache(cache_size, pages_amount);

    std::cout << processing_cache(cache, pages_amount) << std::endl;

    return 0;
}
