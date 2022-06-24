cmake_minimum_required(VERSION 3.9)
project(INTUIT_baseAlgorithmsForPupil_lec8_precision_of_calculations)

set(SOURCES
        src/main.cpp
        )

add_executable(lec8_geometry ${SOURCES})
target_compile_features(lec8_geometry PUBLIC cxx_std_17)
target_include_directories(lec8_geometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(INTUIT_baseAlgorithmsForPupil_lec8_geometry_lib INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec8_geometry::lib
        ALIAS INTUIT_baseAlgorithmsForPupil_lec8_geometry_lib)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec8_geometry_lib INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec8_geometry_lib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)


add_library(INTUIT_baseAlgorithmsForPupil_lec8_geometry_practice INTERFACE)
add_library(INTUIT::baseAlgorithmsForPupil::lec8_geometry::practice
        ALIAS INTUIT_baseAlgorithmsForPupil_lec8_geometry_practice)
target_compile_features(INTUIT_baseAlgorithmsForPupil_lec8_geometry_practice INTERFACE cxx_std_17)
target_include_directories(INTUIT_baseAlgorithmsForPupil_lec8_geometry_practice
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)
target_compile_definitions(INTUIT_baseAlgorithmsForPupil_lec8_geometry_practice INTERFACE -DPRACTICE)


add_subdirectory(test)