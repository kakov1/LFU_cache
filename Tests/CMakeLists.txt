cmake_minimum_required(VERSION 3.14)
project("LFU_cache")

add_library(read_and_process ../Process/read_and_process.cpp)

target_include_directories(read_and_process PUBLIC ../Process/)

set(SOURCES test.cpp)
add_executable(test_cache ${SOURCES})

target_link_libraries(test_cache gtest gmock pthread)
target_link_libraries(test_cache read_and_process)
