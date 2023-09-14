cmake_minimum_required(VERSION 3.16)
project(e-maxx)

set(CMAKE_CXX_STANDARD 20)
add_executable(e-maxx_strings_prefix_function ${CMAKE_CURRENT_SOURCE_DIR}/strings/prefixFunction.cpp)

add_executable(e-maxx_manaker ${CMAKE_CURRENT_SOURCE_DIR}/strings/manaker.cpp)

add_executable(e-maxx_LCA ${CMAKE_CURRENT_SOURCE_DIR}/graphs/LCA/LCA.cpp)

add_executable(e-maxx_LCA_chip_Dale ${CMAKE_CURRENT_SOURCE_DIR}/graphs/LCA/LCA_chip_Dale.cpp)
