cmake_minimum_required(VERSION 3.23)
project(simple_cuda)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CUDA_ARCHITECTURES all-major)
enable_language(CUDA)

add_executable(simple_cuda main.cu)
