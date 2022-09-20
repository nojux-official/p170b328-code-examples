cmake_minimum_required(VERSION 3.12)
project(openmp_private)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")
add_executable(openmp_private main.cpp)