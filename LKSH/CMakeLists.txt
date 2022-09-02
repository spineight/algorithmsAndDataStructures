cmake_minimum_required(VERSION 3.16)
project(LKSH)

set(CMAKE_CXX_STANDARD 20)
add_executable(LKSH_2008_day1 ${CMAKE_CURRENT_SOURCE_DIR}/2008/solutions/day1.cpp)
add_executable(LKSH_2008_mergeSort ${CMAKE_CURRENT_SOURCE_DIR}/2008/src/mergeSort.cpp)
add_executable(LKSH_2008_KMP ${CMAKE_CURRENT_SOURCE_DIR}/2008/src/kmp.cpp)
add_executable(LKSH_2008_prefixFunction ${CMAKE_CURRENT_SOURCE_DIR}/2008/src/prefixFunctionUsages.cpp)
add_executable(LKSH_2008_zFunction ${CMAKE_CURRENT_SOURCE_DIR}/2008/src/zFunction.cpp)
