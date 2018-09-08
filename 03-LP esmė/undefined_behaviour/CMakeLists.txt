cmake_minimum_required(VERSION 3.12)
project(undefined_behaviour)

set(CMAKE_CXX_STANDARD 11)

add_executable(undefined_behaviour main.cpp)
TARGET_LINK_LIBRARIES(undefined_behaviour pthread)
