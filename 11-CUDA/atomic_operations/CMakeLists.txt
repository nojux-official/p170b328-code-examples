cmake_minimum_required(VERSION 3.12)
project(atomic_operations)

set(CMAKE_CXX_STANDARD 17)
enable_language(CUDA)

add_executable(atomic_operations main.cu)
set_target_properties(atomic_operations PROPERTIES CUDA_ARCHITECTURES all-major)