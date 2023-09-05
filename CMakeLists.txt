cmake_minimum_required(VERSION 3.16)
project(algorithmsAndDataStructures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


###     Google Test     Start###
### http://google.github.io/googletest/quickstart-cmake.html
### https://github.com/google/googletest/releases/tag/v1.13.0

### [27/08/2023][0] cmake The DOWNLOAD_EXTRACT_TIMESTAMP option was not given
### "cmake The DOWNLOAD_EXTRACT_TIMESTAMP option was not given"
### https://cmake.org/cmake/help/latest/module/ExternalProject.html#command:externalproject_add
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP false ### [27/08/2023][0]
)
FetchContent_MakeAvailable(googletest)
###     Google Test     End###

add_subdirectory(intuit/BaseAlgorithmsForPupil)

add_subdirectory(e-maxx)

add_executable(algorithmsAndDataStructures main.cpp)

add_subdirectory(freeCodeCamp)

add_subdirectory(FPMI/Stepanov)
#
#add_subdirectory(intuit/baseAndAdvancedAlgsForPupil)
#add_subdirectory(LKSH)

#add_subdirectory(Codeforces)
#add_subdirectory(compscicenter)
#add_subdirectory(Rucode)
#add_subdirectory(Skiena_programmingChallenges_book)
#add_subdirectory(MIT/CLRS)