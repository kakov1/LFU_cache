cmake_minimum_required(VERSION 3.14)
project("LFU_cache")

add_executable(test_cache test.cpp)

target_link_libraries(test_cache gtest gmock pthread)
