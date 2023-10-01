cmake_minimum_required(VERSION 3.14)
project(recursive_parallelism_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(recursive_parallelism_cpp main.cpp)
target_link_libraries(recursive_parallelism_cpp pthread)