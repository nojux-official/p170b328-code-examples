cmake_minimum_required(VERSION 3.23)
project(simple_cuda)

set(CMAKE_CXX_STANDARD 20)
enable_language(CUDA)

add_executable(simple_cuda main.cu)
set_target_properties(simple_cuda PROPERTIES CUDA_ARCHITECTURES all-major)