cmake_minimum_required(VERSION 3.16)
project(freeCodeCamp)

set(CMAKE_CXX_STANDARD 20)

add_executable(gridTraveller DP/gridTraveller.cpp)
add_executable(canSum DP/canSum.cpp)
add_executable(howSum DP/howSum.cpp)
add_executable(bestSum DP/bestSum.cpp)
add_executable(canConstruct DP/canConstruct.cpp)
add_executable(countConstruct DP/countConstruct.cpp)
add_executable(allConstruct DP/allConstruct.cpp)

add_executable(BIT DataStructures/BIT.cpp)