add_executable(Stepanov_binary_heap binary_heap.cpp)

### Введение в программирование 3. Сортировки. MergeSort, недетерминированный QuickSort
add_executable(Stepanov_mergeSort mergeSort.cpp)

### Введение в программирование 4. QuickSelect, детерминированный QuickSort, LSD
add_executable(Stepanov_countingSort countingSort.cpp)
add_executable(Stepanov_stableCountingSort stableCountingSort.cpp)


### Введение в программирование 7. Амортизационный анализ метод монет, потенциалов. Sparse table
### У него ошибка в реализации - выход за пределы массива
add_executable(Stepanov_sparseTable sparseTable.cpp)