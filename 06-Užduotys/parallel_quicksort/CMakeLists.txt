cmake_minimum_required(VERSION 3.12)
project(parallel_quicksort)

set(CMAKE_CXX_STANDARD 11)

add_executable(parallel_quicksort main.cpp)
TARGET_LINK_LIBRARIES(parallel_quicksort pthread)