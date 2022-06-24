cmake_minimum_required(VERSION 3.9)
project(INTUIT_baseAlgorithmsForPupil_lec4_graph_theory)

set(SOURCES
    src/main.cpp
)

add_executable(lec4_graph_theory ${SOURCES})
target_compile_features(lec4_graph_theory PUBLIC cxx_std_17)
target_include_directories(lec4_graph_theory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_lib INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::lib
        ALIAS INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_lib)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_lib INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)



add_library(INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_practice INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec4_graph_theory::practice
        ALIAS INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_practice)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_practice INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_practice
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        )
target_compile_definitions(INTUIT_baseAlgorithmsForPupil_lec4_graph_theory_practice INTERFACE -DPRACTICE)


add_subdirectory(test)