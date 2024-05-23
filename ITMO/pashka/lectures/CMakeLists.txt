cmake_minimum_required(VERSION 3.9)
project(pashka_lectures)


add_subdirectory(Semestr1)


#add_library(pashka_algos_practice INTERFACE)
#add_library(pashka::algos::practice
#        ALIAS pashka_algos_practice)
#target_compile_features(pashka_algos_practice INTERFACE cxx_std_17)
#target_include_directories(pashka_algos_practice
#        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/
#        )
#target_compile_definitions(pashka_algos_practice INTERFACE -DPRACTICE)
#
#
#add_subdirectory(test)