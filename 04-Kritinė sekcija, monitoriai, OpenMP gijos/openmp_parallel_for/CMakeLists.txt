cmake_minimum_required(VERSION 3.17)
project(openmp_parallel_for)

set(CMAKE_CXX_STANDARD 20)

add_executable(openmp_parallel_for main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
