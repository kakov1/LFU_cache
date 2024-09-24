cmake_minimum_required(VERSION 3.11)
project("LFU_cache")

add_library(read_and_process ../Process/read_and_process.cpp)

target_include_directories(read_and_process PUBLIC ../Process/)

add_executable(cache cache.cpp) 
add_executable(ideal_cache ideal_cache.cpp)

target_link_libraries(cache read_and_process)
target_link_libraries(ideal_cache read_and_process)
