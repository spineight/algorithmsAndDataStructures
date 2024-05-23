cmake_minimum_required(VERSION 3.9)
project(pashka_algos)


set(SOURCES
    src/main.cpp
)

add_executable(pashka_algos ${SOURCES})
target_compile_features(pashka_algos PUBLIC cxx_std_17)
target_include_directories(pashka_algos PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(pashka_algos_lib INTERFACE)
add_library(pashka::algos::lib
        ALIAS pashka_algos_lib)
target_compile_features(pashka_algos_lib INTERFACE cxx_std_17)
target_include_directories(pashka_algos_lib
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)


add_library(pashka_algos_practice INTERFACE)
add_library(pashka::algos::practice
        ALIAS pashka_algos_practice)
target_compile_features(pashka_algos_practice INTERFACE cxx_std_17)
target_include_directories(pashka_algos_practice
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/
        )
target_compile_definitions(pashka_algos_practice INTERFACE -DPRACTICE)


add_subdirectory(test)