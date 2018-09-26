cmake_minimum_required(VERSION 3.12)
project(counter_cpp)

set(CMAKE_CXX_STANDARD 11)

add_executable(counter_cpp main.cpp SimpleBoundedCounter.cpp SimpleBoundedCounter.h)

TARGET_LINK_LIBRARIES(counter_cpp pthread)