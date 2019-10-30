cmake_minimum_required(VERSION 3.12)
project(thrust_functional)

set(CMAKE_CXX_STANDARD 11)
include_directories(${CUDA_INCLUDE_DIRS})
link_directories(${CUDA_LIBRARY_DIRS})

enable_language(CUDA)

add_executable(thrust_functional main.cu)