# Algorithms
## sorting

#### counting sort
[countingSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/countingSort.cpp)

Based on Сергей Копелиович lecture: `/run/media/oleg/TOSHIBA EXT/ITMO/BaseAndAdvancedAlgsForSchoolStudents/Lecture2_Sorting_Lists_ShortestPathsInGraphs.mp4`    
Important idea that if data elements associated with keys are expensive to copy we instead od copying them  
can return permutation, where `permutation[i] - idx of element in initial array at i-th position in the resulting array`  
Using permutation we can access elements data in sorted order without need for copy  

#### radix sort
[radixSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/radixSort.cpp)  
Based on Сергей Копелиович lecture: `/run/media/oleg/TOSHIBA EXT/ITMO/BaseAndAdvancedAlgsForSchoolStudents/Lecture2_Sorting_Lists_ShortestPathsInGraphs.mp4`  
uses [countingSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/countingSort.cpp)   

## Searching
Based on Andrei Stankevich lecture:`/run/media/oleg/TOSHIBA EXT/ITMO/BaseAlgsForSchoolStudents/lec2_sorting_and_search`    
[binarySearch](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/binary_search.hpp)  
[nth_element](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/nth_element.hpp)

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

# Data structures
[Fenwick Tree or Binary Indexed Tree](../freeCodeCamp/DataStructures/BIT.cpp)  
