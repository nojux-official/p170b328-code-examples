cmake_minimum_required(VERSION 3.12)
project(counter_omp)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
add_executable(counter_omp main.cpp)