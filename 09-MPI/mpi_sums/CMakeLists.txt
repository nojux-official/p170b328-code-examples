cmake_minimum_required(VERSION 3.12)
project(mpi_sums)

set(CMAKE_CXX_STANDARD 11)
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)
SET(CMAKE_CXX_COMPILER mpicxx)

add_executable(mpi_sums main.cpp)