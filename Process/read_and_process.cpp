#include "read_and_process.hpp"
#include <iostream>

size_t get_page(size_t key) {
    return key;
}

int read_input_pages(ideal_cache_t<size_t, size_t>& cache, size_t pages_amount) {
    size_t buf;

    for (size_t page_num = 0; page_num < pages_amount; page_num++) {
        std::cin >> buf;

        cache.pages_hash_table[buf].push_back(page_num);
        cache.pages_list.push_back(buf);
    }

    return 0;
}

int processing_cache(ideal_cache_t<size_t, size_t>& cache, size_t pages_amount) {
    read_input_pages(cache, pages_amount);

    for (size_t key : cache.pages_list) {
        cache.lookup_update(key, get_page(key));
    }

    return 0;
}

int processing_cache(cache_t<size_t, size_t>& cache, size_t pages_amount) {
    size_t buf;

    for (int page_num = 0; page_num < pages_amount; page_num++) {
        std::cin >> buf;
        cache.lookup_update(buf, get_page(buf));
    }

    return 0;
}