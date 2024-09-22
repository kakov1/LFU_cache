cmake_minimum_required(VERSION 3.11)
project("LFU_cache")

add_executable(cache cache.cpp ../Process/read_and_process.cpp)
add_executable(ideal_cache ideal_cache.cpp ../Process/read_and_process.cpp)
