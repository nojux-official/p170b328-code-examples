cmake_minimum_required(VERSION 3.12)
project(openmp_lastprivate)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
add_executable(openmp_lastprivate main.cpp)
