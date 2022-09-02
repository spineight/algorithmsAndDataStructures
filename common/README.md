# Learning algorithms & data structures
Нужно в ручную(ручка + бумага) прогонять алгоритм на разных данных, подобранных так, чтобы показать особенности алгоритмов
(Я пытался разобраться в работе KMP и подобранные входные данные позволили мне найти и исправить ошибку)  


# Tasks solving approaches
## Getting Time limit exceeded - solved using smarter algorithm
1. Берем разные входные данные и на них вручную решаем задачу  
После нескольких таких решений может появиться догадка и формуле/закономерности  
Используем slowSolve - медленное решение написанное ранее и проверяем догадку (сравнивая вручную посчитанный результат и
ответ solveSlow) - если результаты не совпадают, думаем почему  
Пример использования такого подхода:  
[CodeForces. D. Количество хороших подстрок-1](../Codeforces/itmoAcademy/step1_problemD.cpp)  

## Getting Time limit exceeded - solved using precomputations
[CodeForces step2. B - Z-функция строки Грея ](../Codeforces/itmoAcademy/step2_problemB.cpp)  

# Implementation approaches
## Simplify by avoiding code duplicate
Use pointers to store branch results on which algorithm will be performed  
see `leetcode: /twoPointers/intervalListIntersections.hpp`  

# Algorithms
## sorting & search

#### counting sort
[countingSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/countingSort.cpp)

Based on Сергей Копелиович lecture: `/run/media/oleg/TOSHIBA EXT/ITMO/BaseAndAdvancedAlgsForSchoolStudents/Lecture2_Sorting_Lists_ShortestPathsInGraphs.mp4`    
Important idea that if data elements associated with keys are expensive to copy we instead od copying them  
can return permutation, where `permutation[i] - idx of element in initial array at i-th position in the resulting array`  
Using permutation we can access elements data in sorted order without need for copy   

[Сортировка подсчетом] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item9.mp4`

#### radix sort
[radixSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/radixSort.cpp)  
Based on Сергей Копелиович lecture: `/run/media/oleg/TOSHIBA EXT/ITMO/BaseAndAdvancedAlgsForSchoolStudents/Lecture2_Sorting_Lists_ShortestPathsInGraphs.mp4`  
uses [countingSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/countingSort.cpp)   

#### Quick sort
[quick_sort](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/quick_sort.hpp)  
[Stankevich lecture] `/run/media/oleg/TOSHIBA EXT/ITMO/BaseAlgsForSchoolStudents/lec2_sorting_and_search`  
[Pestov lecture LKSH b prime 2008] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item4.mp4`    
[Лекция 4. Сортировка подсчетом и применение встроенных сортировок](../shujkova/lectures/lec4.pdf)  

#### Merge sort
I wrote code based on the lecture: `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item7.mp4`  
[LKSH 2008 b` merge sort](LKSH/2008/src/mergeSort.cpp)
[Лекция 4. Сортировка подсчетом и применение встроенных сортировок](../shujkova/lectures/lec4.pdf)  
#### Merge sort. Number of inversions
[Применение сортировки слиянием: количество инверсий.] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item8.mp4`  
[Merge sort. Number of inversinos](../LKSH/2008/src/mergeSort.cpp)

#### Binary search. Binary search by answer. Real numbers binary search.
Main source:
Based on Andrei Stankevich lecture:`/run/media/oleg/TOSHIBA EXT/ITMO/BaseAlgsForSchoolStudents/lec2_sorting_and_search`    
[binarySearch](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/binary_search.hpp)   
[binarySearch Pestov lecture LKSH b prime 2008] examples of binary search on an answer:  
 * `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item1.mp4`    
* `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item2.mp4`   
* `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item3.mp4`    

##### Non standard binary search (different from Andrei Stankevich, all ends are included)
/home/oleg/github/leetcode/binary_search/searchInRotatedSortedArray.hpp  


#### k-th element
This is my implementation based on Stankevich Quick sort implementation  
Also the same implementation is presented in  
[Лекция 4. Сортировка подсчетом и применение встроенных сортировок](../shujkova/lectures/lec4.pdf)  
[nth_element](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/nth_element.hpp)   
[Pestov lecture LKSH b prime 2008 Разбор задачи Kth ("K-ый минимум") из контеста первого дня: модификация алгоритма быстрой сортировки для нахождения k-й порядковой статистики.]
`/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item5.mp4`

## Recursion
Great explanation at Stanford CS 106B (2008) by Julie Zelenski: `/run/media/oleg/TOSHIBA EXT/cs106b_2008_ProgrammingAbstractionsStanford`    
Problem types:  
[permutation problem](../cs106b/permutations.cpp)    
[subset_problem](../cs106b/subset.cpp)  
[towers of Hanoi](../cs106b/moveTower.cpp)  

Backtracking:  
[sudoku Solver](../cs106b/sudokuSolver.cpp)  
[queens8](../cs106b/queens8.cpp)  

## DP
Good explanation of base types in Andrei Stankevich lecture:`/run/media/oleg/TOSHIBA EXT/ITMO/BaseAlgsForSchoolStudents/lec3_dynamic_programming`    
[grasshopper](../intuit/BaseAlgorithmsForPupil/lec3_dynamic_programming/include/grasshopper.hpp)  
[turtle](../intuit/BaseAlgorithmsForPupil/lec3_dynamic_programming/include/turtle.hpp)  
[zoo_store](../intuit/BaseAlgorithmsForPupil/lec3_dynamic_programming/include/zoo_store.hpp)  

Good explanation of thought process how to go from recursive version -> recursive + memoization -> DP  
video lectures: `/run/media/oleg/TOSHIBA EXT/FreeCodeCamp/DynamicProgramming_LearntoSolveAlgorithmicProblems_26CodingChallenges.mp4)`  
In the order of difficulty:  
[gridTraveller](../freeCodeCamp/DP/gridTraveller.cpp) - according to Stankevich lecture on DP (this can be solved using combinatorics formula)  
[canSum](../freeCodeCamp/DP/canSum.cpp)  
[howSum](../freeCodeCamp/DP/howSum.cpp)  
[bestSum](../freeCodeCamp/DP/bestSum.cpp)  
[canConstruct](../freeCodeCamp/DP/canConstruct.cpp)    
[countConstruct](../freeCodeCamp/DP/countConstruct.cpp)  
[allConstruct](../freeCodeCamp/DP/allConstruct.cpp)  

## Geometry
### Sweep line (Scan line)
[Rucode/scanline/README](../Rucode/scanline/README.md)  
`/run/media/oleg/TOSHIBA EXT/RUCODE/ScanLineNevstruev.mp4`     
[HSE/LKSH_2018/8_Metod_skaniruyuschei_774_pryamoi_774](../HSE/LKSH_2018/8_Metod_skaniruyuschei_774_pryamoi_774.pdf)

## Graphs
### BFS
[Алгоритм BFS. Очередь.] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day2_item3.mp4`  
### Дейкстра
[Дейкстра Лектор: Сергей Копелиович] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day2_item8.mp4`
[Дейкстра. Реализация алгоритма. Лектор: Сергей Копелиович]`/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day2_item9.mp4`

### Беллман-Форд
[Алгоритм Форда-Беллмана. Поиск кратчайшего пути от данной вершины в графе с отрицательными ребрами. Описание алгоритма. Циклы отрицательного веса. Лектор: Сергей Копелиович]
`/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day3_item4.mp4`

### Алгоритм Флойда
[Алгоритм Флойда. Описание алгоритма, реализация, оценка сложности. Оптимизация по памяти.]
`/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day3_item5.mp4`

# Data structures
### trees
#### traversal
[leetcode/tree/n-aryTreePreorderTraversal](../leetcode/tree/n-aryTreePreorderTraversal.hpp)  
[leetcode/tree/n-aryTreePostOrderTraversal](../leetcode/tree/n-aryTreePostOrderTraversal.hpp)

### Fenwick tree (Binary Indexed Tree)
[Fenwick Tree or Binary Indexed Tree](../freeCodeCamp/DataStructures/BIT.cpp)  

### Trie
https://www.quora.com/What-is-the-best-open-source-C-implementation-of-a-trie


## Strings
### Main definitions
[main definitions]`/run/media/oleg/TOSHIBA EXT/codeforces/itmoAcademy/stringsMainDefinitions.mp4`
### Prefix function
[Применения prefix function Лектор: Олег Пестов] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day12_item3.mp4`  
[Поиск подстроки в строке с использованием префикс функции](../LKSH/2008/src/prefixFunctionUsages.cpp)  
[Определить является ли одна строка циклическим сдвигом другой с использованием префикс функции](../LKSH/2008/src/prefixFunctionUsages.cpp)      

### Prefix function + KMP
[Prefix function. KMP](../e-maxx/strings/prefixFunction.cpp)    
[Префикс-функция. Алгоритм Кнута-Морриса-Пратта (КМП).  Лектор: Олег Пестов] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day12_item2.mp4`  

[KMP](../LKSH/2008/src/kmp.cpp)  
Пока сложно для понимания и реализации:  
[KMP using Discrete Finite Automaton Sedgewick](../Sedgewick/RobertSedgewick_and_KevinWayne_Algorithms_4th_edition_Princeton_University_2011_ENG.pdf)

### Z algorithm
[Z алгоритм.  Лектор: Олег Пестов] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day12_item4.mp4`  
[Z алгоритм](../LKSH/2008/src/zFunction.cpp)   
[Z алгоритм. Компактная реализация CodeForces ITMO Academy](../Codeforces/itmoAcademy/step3_problemA.cpp)  
[Восстановление строки по Z function](../Codeforces/itmoAcademy/step2_problemC.cpp)  
[ITMO WikiConspect Z function](../ITMO/wikiConspects/Zfunction.pdf)  
[ITMO Academy Z function](../Codeforces/itmoAcademy/Edu_Z-функция.pdf)

Для поиска суффикса p в t используется прием разворота строк  
[Неточный поиск с окном k символов](../Codeforces/itmoAcademy/step4_problemI.cpp)   

Z algo using O(m) space in comparision to standard where O(n + m) space is used (m=p.size(), n = t.size())  
My Implementation, based on the lecture: /run/media/oleg/TOSHIBA EXT/compscicenter/2018_part2/lec1_strings_zFunction.mp4  
[Z algo O(m) space](../compscicenter/ASD_part2_2018/zFunction.cpp)