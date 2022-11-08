cmake_minimum_required(VERSION 3.12)
project(2d_arrays)

set(CMAKE_CXX_STANDARD 14)
enable_language(CUDA)

add_executable(2d_arrays main.cu)
set_target_properties(2d_arrays PROPERTIES CUDA_ARCHITECTURES all-major)