cmake_minimum_required(VERSION 3.12)
project(data_concurrency)

set(CMAKE_CXX_STANDARD 11)

add_executable(data_concurrency main.cpp)
TARGET_LINK_LIBRARIES(data_concurrency pthread)