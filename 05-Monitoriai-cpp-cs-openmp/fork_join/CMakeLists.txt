cmake_minimum_required(VERSION 3.17)
project(fork_join)

set(CMAKE_CXX_STANDARD 17)

add_executable(fork_join main.cpp TinyPngOut.hpp TinyPngOut.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")