cmake_minimum_required(VERSION 3.1)
project(matrix_mul_omp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} COMMON_LIB)
