cmake_minimum_required(VERSION 3.14)
project(pointer_stealing)

set(CMAKE_CXX_STANDARD 20)

add_executable(pointer_stealing main.cpp ThreadSafeStack.cpp ThreadSafeStack.h)
target_link_libraries(pointer_stealing pthread)