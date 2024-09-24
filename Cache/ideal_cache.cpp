#include "ideal_cache.hpp"
#include "read_and_process.hpp"
#include <iostream>

int main() {
    size_t cache_size, pages_amount;

    is_cin_good();

    std::cin >> cache_size >> pages_amount;

    ideal_cache_t<size_t, size_t> cache(cache_size, pages_amount);

    processing_cache(cache, pages_amount);

    std::cout << cache.get_hits() << std::endl;

    return 0;
}
