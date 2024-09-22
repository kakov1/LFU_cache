cmake_minimum_required(VERSION 3.14)
project("LFU_cache")

set(SOURCES test.cpp ../Process/read_and_process.cpp)
add_executable(test_cache ${SOURCES})

target_link_libraries(test_cache gtest gmock pthread)
