cmake_minimum_required(VERSION 3.17)
project(openmp_parallel_for)

set(CMAKE_CXX_STANDARD 14)

add_executable(openmp_parallel_for main.cpp)
find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    target_link_libraries(openmp_parallel_for PUBLIC OpenMP::OpenMP_CXX)
endif()
