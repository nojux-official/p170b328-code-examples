cmake_minimum_required(VERSION 3.12)
project(async_exceptions)

set(CMAKE_CXX_STANDARD 11)

add_executable(async_exceptions main.cpp)
TARGET_LINK_LIBRARIES(async_exceptions pthread)