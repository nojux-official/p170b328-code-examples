cmake_minimum_required(VERSION 3.20)
project(reference_returns_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(reference_returns_cpp main.cpp SortedThreadSafeList.h)

TARGET_LINK_LIBRARIES(reference_returns_cpp pthread)

