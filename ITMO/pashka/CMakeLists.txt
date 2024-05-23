cmake_minimum_required(VERSION 3.16)
project(Pashka
    VERSION 1.0.0
    DESCRIPTION "ITMO Pavel Mavrin"
    HOMEPAGE_URL "https://www.youtube.com/channel/UC9WDkCyUlNTncq1Y-mFSgLQ"
    LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(algos)
add_subdirectory(lectures)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    add_subdirectory(extern/googletest)
    include(GoogleTest)
endif()
#
#add_subdirectory(docs)