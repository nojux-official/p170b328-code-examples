cmake_minimum_required(VERSION 3.12)
project(2d_arrays)

set(CMAKE_CXX_STANDARD 11)
enable_language(CUDA)

add_executable(2d_arrays main.cu)