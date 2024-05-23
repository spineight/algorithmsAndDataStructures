cmake_minimum_required(VERSION 3.1)
project(opencl)

include_directories(.)
add_library(COMMON_LIB
        common/utils.h
        common/utils.cpp
        common/matrix.h
        common/matrix.cpp)

find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})


target_link_libraries(COMMON_LIB ${OpenCL_LIBRARY})

set(MAT_OCL_SUBDIR matrix_mul_ocl)
set(PREFSUM_OCL_SUBDIR prefsum_ocl)

add_subdirectory(matrix_mul_omp)
add_subdirectory(${MAT_OCL_SUBDIR})
add_subdirectory(${PREFSUM_OCL_SUBDIR})

file(COPY ${MAT_OCL_SUBDIR}/mat_mp.cl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${MAT_OCL_SUBDIR})
file(COPY ${PREFSUM_OCL_SUBDIR}/prefsum.cl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${PREFSUM_OCL_SUBDIR})
