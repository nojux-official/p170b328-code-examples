cmake_minimum_required(VERSION 3.12)
project(thrust_functional)

set(CMAKE_CXX_STANDARD 17)

enable_language(CUDA)

add_executable(thrust_functional main.cu)
set_target_properties(thrust_functional PROPERTIES CUDA_ARCHITECTURES all-major)