cmake_minimum_required(VERSION 3.9)
project(INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming)

set(SOURCES
    src/main.cpp
)

add_executable(lec3_dynamic_programming ${SOURCES})
target_compile_features(lec3_dynamic_programming PUBLIC cxx_std_17)
target_include_directories(lec3_dynamic_programming PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_lib INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec3_dynamic_programming::lib
        ALIAS INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_lib)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_lib INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)



add_library(INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_practice INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec3_dynamic_programming::practice
        ALIAS INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_practice)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_practice INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_practice
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_compile_definitions(INTUIT_baseAlgorithmsForPupil_lec3_dynamic_programming_practice INTERFACE -DPRACTICE)


add_subdirectory(test)