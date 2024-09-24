#include "read_and_process.hpp"
#include <iostream>

size_t get_page(size_t key) {
    return key;
}
void is_cin_good() {
    if (!std::cin.good()) {
        throw std::runtime_error("Input error: something went wrong with input");
    }
}

void read_input_pages(ideal_cache_t<size_t, size_t>& cache, size_t pages_amount) {
    size_t buf;

    for (size_t page_num = 0; page_num < pages_amount; page_num++) {
        std::cin >> buf;
        is_cin_good();
        cache.add_page(buf, page_num);
    }
}

void processing_cache(ideal_cache_t<size_t, size_t>& cache, size_t pages_amount) {
    read_input_pages(cache, pages_amount);
    size_t key;

    for (size_t page_num = 0; page_num < pages_amount; page_num++) {
        key = cache.get_key(page_num);
        cache.lookup_update(key, get_page(key));
    }
}

void processing_cache(cache_t<size_t, size_t>& cache, size_t pages_amount) {
    size_t buf;
 
    for (size_t page_num = 0; page_num < pages_amount; page_num++) {
        std::cin >> buf;
        is_cin_good();
        cache.lookup_update(buf, get_page(buf));
    }
}