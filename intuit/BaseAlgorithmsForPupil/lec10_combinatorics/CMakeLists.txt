cmake_minimum_required(VERSION 3.9)
project(INTUIT_baseAlgorithmsForPupil_lec10_combinatorics)

set(SOURCES
        src/main.cpp
)

add_executable(lec10_combinatorics ${SOURCES})
target_compile_features(lec10_combinatorics PUBLIC cxx_std_17)
target_include_directories(lec10_combinatorics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_lib INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec10_combinatorics::lib
        ALIAS INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_lib)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_lib INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_lib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        )



add_library(INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_practice INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec10_combinatorics::practice
        ALIAS INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_practice)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_practice INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_practice
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        )
target_compile_definitions(INTUIT_baseAlgorithmsForPupil_lec10_combinatorics_practice INTERFACE -DPRACTICE)


add_subdirectory(test)

