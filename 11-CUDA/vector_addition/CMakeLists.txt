cmake_minimum_required(VERSION 3.12)
project(simple_cuda)

set(CMAKE_CXX_STANDARD 11)
enable_language(CUDA)

add_executable(simple_cuda main.cu)