cmake_minimum_required(VERSION 3.17)
project(atomic_operations CUDA)

set(CMAKE_CUDA_STANDARD 14)

add_executable(atomic_operations main.cu)

set_target_properties(
        atomic_operations
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)