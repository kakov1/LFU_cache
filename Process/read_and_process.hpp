#ifndef READ_AND_PROCESS_HPP__
#define READ_AND_PROCESS_HPP__

#include "../Cache/cache.hpp"
#include "../Cache/ideal_cache.hpp"

size_t get_page(size_t key);
int read_input_pages(ideal_cache_t<size_t, size_t>& cache, size_t pages_amount);
int processing_cache(ideal_cache_t<size_t, size_t>& cache, size_t pages_amount);
int processing_cache(cache_t<size_t, size_t>& cache, size_t pages_amount);

#endif