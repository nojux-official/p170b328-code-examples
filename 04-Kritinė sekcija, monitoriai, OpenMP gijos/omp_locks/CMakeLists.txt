cmake_minimum_required(VERSION 3.29)
project(omp_locks)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
add_executable(omp_locks main.cpp)
