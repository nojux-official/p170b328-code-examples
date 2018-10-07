cmake_minimum_required(VERSION 3.12)
project(async_cpp)

set(CMAKE_CXX_STANDARD 11)

add_executable(async_cpp main.cpp)
TARGET_LINK_LIBRARIES(async_cpp pthread)
