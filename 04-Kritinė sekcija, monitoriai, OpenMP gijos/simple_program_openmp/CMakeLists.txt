cmake_minimum_required(VERSION 3.14)
project(simple_program_openmp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")
add_executable(simple_program_openmp main.cpp)