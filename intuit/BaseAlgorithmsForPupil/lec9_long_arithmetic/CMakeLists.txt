cmake_minimum_required(VERSION 3.9)
project(INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics)

set(SOURCES
    src/main.cpp
)

add_executable(lec9_long_arithmetics ${SOURCES})
target_compile_features(lec9_long_arithmetics PUBLIC cxx_std_17)
target_include_directories(lec9_long_arithmetics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_lib INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec9_long_arithmetics::lib
        ALIAS INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_lib)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_lib INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_lib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        )



add_library(INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_practice INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec9_long_arithmetics::practice
        ALIAS INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_practice)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_practice INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_practice
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        )
target_compile_definitions(INTUIT_baseAlgorithmsForPupil_lec9_long_arithmetics_practice INTERFACE -DPRACTICE)


add_subdirectory(test)