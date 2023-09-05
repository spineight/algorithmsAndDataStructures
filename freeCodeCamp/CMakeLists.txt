cmake_minimum_required(VERSION 3.16)
project(freeCodeCamp)

set(CMAKE_CXX_STANDARD 20)

add_executable(freeCodeCamp freeCodeCamp.cpp)

add_subdirectory(Recursion_and_DP)
add_subdirectory(DataStructures)
