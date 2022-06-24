cmake_minimum_required(VERSION 3.9)
project(INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search)

set(SOURCES
    src/main.cpp
)

add_executable(lec2_sorting_and_search ${SOURCES})
target_compile_features(lec2_sorting_and_search PUBLIC cxx_std_17)
target_include_directories(lec2_sorting_and_search PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_lib INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec2_sorting_and_search::lib
        ALIAS INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_lib)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_lib INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_lib
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/
)



add_library(INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_practice INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec2_sorting_and_search::practice
        ALIAS INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_practice)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_practice INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_practice
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_compile_definitions(INTUIT_baseAlgorithmsForPupil_lec2_sorting_and_search_practice INTERFACE -DPRACTICE)


add_subdirectory(test)