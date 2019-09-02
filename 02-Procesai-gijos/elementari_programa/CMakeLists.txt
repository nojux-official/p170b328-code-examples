cmake_minimum_required(VERSION 3.12)
project(elementari_programa)

set(CMAKE_CXX_STANDARD 14)

add_executable(elementari_programa main.cpp)

TARGET_LINK_LIBRARIES(elementari_programa pthread)