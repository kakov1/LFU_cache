cmake_minimum_required(VERSION 3.11)
project("LFU_cache")

SET(SRCS cache.cpp)

add_library(lclib STATIC ${SRCS})
target_include_directories(lclib PUBLIC "include")

add_executable(cache cache.cpp)
target_link_libraries(cache lclib)