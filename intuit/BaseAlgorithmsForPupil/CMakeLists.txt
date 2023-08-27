cmake_minimum_required(VERSION 3.16)
project(INTUIT_baseAlgorithmsForPupils)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(lec1_complexity_of_algorithms)
add_subdirectory(lec2_sorting_and_search)
add_subdirectory(lec3_dynamic_programming)
add_subdirectory(lec4_graph_theory)
add_subdirectory(lec5_graph_theory)
add_subdirectory(lec6_graph_theory)
add_subdirectory(lec7_geometry)
add_subdirectory(lec8_geometry)
add_subdirectory(lec9_long_arithmetic)
#add_subdirectory(lec10_combinatorics)


## [27/08/2023] - I replaced this block with fetch content
#if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
#        include(CTest)
#        add_subdirectory(extern/googletest)
#        include(GoogleTest)
#endif()

add_subdirectory(docs)