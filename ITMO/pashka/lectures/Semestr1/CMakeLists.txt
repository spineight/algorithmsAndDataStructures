set(SOURCES
    src/main.cpp
)

add_executable(pashka_S1 ${SOURCES})
target_compile_features(pashka_S1 PUBLIC cxx_std_17)
target_include_directories(pashka_S1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(pashka_S1_lib INTERFACE)
add_library(pashka::S1::lib
        ALIAS pashka_S1_lib)
target_compile_features(pashka_S1_lib INTERFACE cxx_std_17)
target_include_directories(pashka_S1_lib
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
)
### Lec 1
add_executable(Pashka_insertionSort src/insertionSort.cpp)
add_executable(Pashka_mergeSort src/mergeSort.cpp)

### Lec 2
add_executable(Pashka_binaryHeap src/binaryHeap.cpp)

### Lec 3
add_executable(Pashka_quickSort src/quickSort_incorrect.cpp)
add_executable(Pashka_kth_element src/kth_element_incorrect.cpp)