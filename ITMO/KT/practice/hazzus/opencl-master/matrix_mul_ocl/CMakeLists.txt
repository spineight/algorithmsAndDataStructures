cmake_minimum_required(VERSION 3.1)
project(matrix_mul_ocl)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARY})
target_link_libraries(${PROJECT_NAME} COMMON_LIB)
