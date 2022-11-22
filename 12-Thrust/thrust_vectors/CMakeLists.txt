cmake_minimum_required(VERSION 3.12)
project(thrust_vectors)

set(CMAKE_CXX_STANDARD 11)
find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})
link_directories(${CUDA_LIBRARY_DIRS})

enable_language(CUDA)

add_executable(thrust_vectors main.cu)
set_target_properties(thrust_vectors PROPERTIES CUDA_ARCHITECTURES all-major)