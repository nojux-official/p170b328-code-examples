cmake_minimum_required(VERSION 3.12)
project(task_concurrency)

set(CMAKE_CXX_STANDARD 11)

add_executable(task_concurrency main.cpp)
TARGET_LINK_LIBRARIES(task_concurrency pthread)