cmake_minimum_required(VERSION 3.16)
project(cs106b)

set(CMAKE_CXX_STANDARD 20)

add_executable(cs106b main.cpp)
target_include_directories(cs106b PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(lec8 lec8.cpp)
target_include_directories(lec8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(lec9 lec9.cpp)
target_include_directories(lec8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(drawTriangle drawTriangle.cpp)
target_link_libraries(drawTriangle PRIVATE ncurses)
target_include_directories(drawTriangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(moveTower moveTower.cpp)
target_include_directories(moveTower PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(permutations permutations.cpp)
target_include_directories(permutations PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(subset subset.cpp)
target_include_directories(subset PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(isAnagram isAnagram.cpp)
target_include_directories(isAnagram PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)
target_compile_definitions(isAnagram PRIVATE -DDataDir="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(queens8 queens8.cpp)
target_include_directories(queens8 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(sudokuSolver sudokuSolver.cpp)
target_include_directories(sudokuSolver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)