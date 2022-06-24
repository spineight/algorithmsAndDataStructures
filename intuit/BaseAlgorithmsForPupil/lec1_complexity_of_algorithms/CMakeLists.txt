cmake_minimum_required(VERSION 3.9)
project(lec1_complexity_of_algorithms)


set(SOURCES
    src/main.cpp
)

add_executable(lec1_complexity_of_algorithms ${SOURCES})
target_compile_features(lec1_complexity_of_algorithms PUBLIC cxx_std_17)
target_include_directories(lec1_complexity_of_algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(lec1_complexity_of_algorithms_lib INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec1_complexity_of_algorithms::lib
        ALIAS lec1_complexity_of_algorithms_lib)
target_compile_features(lec1_complexity_of_algorithms_lib INTERFACE cxx_std_17)
target_include_directories(lec1_complexity_of_algorithms_lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)



add_library(lec1_complexity_of_algorithms_practice INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec1_complexity_of_algorithms::practice
        ALIAS lec1_complexity_of_algorithms_practice)
target_compile_features(lec1_complexity_of_algorithms_practice INTERFACE cxx_std_17)
target_include_directories(lec1_complexity_of_algorithms_practice
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_compile_definitions(lec1_complexity_of_algorithms_practice INTERFACE -DPRACTICE)


add_subdirectory(test)
