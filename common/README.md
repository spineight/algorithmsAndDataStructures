# Learning algorithms & data structures
Нужно в ручную (ручка + бумага) прогонять алгоритм на разных данных, подобранных так, чтобы показать особенности алгоритмов
(Я пытался разобраться в работе KMP и подобранные входные данные позволили мне найти и исправить ошибку)   
Learn algo by running it with a pen and on paper


# Tasks solving approaches

## Solving with a pen and paper
After solving smaller task, I got an idea:  
[leetcode/strings/repeatedDNAsequences](leetcode/strings/repeatedDNAsequences.hpp)  

## Getting Time limit exceeded - solved using smarter algorithm
1. Берем разные входные данные и на них вручную решаем задачу  
После нескольких таких решений может появиться догадка и формуле/закономерности  
Используем slowSolve - медленное решение написанное ранее и проверяем догадку (сравнивая вручную посчитанный результат и
ответ solveSlow) - если результаты не совпадают, думаем почему  
Пример использования такого подхода:  
[CodeForces. D. Количество хороших подстрок-1](../Codeforces/itmoAcademy/step1_problemD.cpp)  

## Getting Time limit exceeded - solved using precomputations
[CodeForces step2. B - Z-функция строки Грея ](../Codeforces/itmoAcademy/step2_problemB.cpp)  

# Debugging
## pen & paper

Helpful:
- invariant (a condition that is true within certain scope): loop invariant, function call invariant helps a lot  
- call stack representation  
- call frame representation  
- proof of corectness by dividing input on classes (cases) and showing that all of them were covered  

I spent a lot of time debugging this task:  
[leetcode/lists/flattenMultilevelDoublyLinkedList](../leetcode/lists/flattenMultilevelDoublyLinkedList.hpp)  

# Implementation approaches
## Simplify by avoiding code duplicate
Use pointers to store branch results on which algorithm will be performed  
see `leetcode: /twoPointers/intervalListIntersections.hpp`  

## Introduce methods for aux operations
This will allow to simplify code,
easy to test overall functionality by testing separate methods
An example when intro of aux methods made code simpler for comprehension and testing:  
[leetcode/lists/reverseNodesInKGroup](../leetcode/lists/reverseNodesInKGroup.hpp)

# Common mistakes
## corner cases
### integer overflow
when doing comparision for ex. to check if triple could form a triangle
```a < b+c``` - sum here could overflow

```c++
#include <algorithm>
int solution(vector<int> &A) {
    const size_t n(A.size());
    if(n <3) return 0;

    sort(begin(A), end(A), greater<int>());
    for(size_t i = 0; i <= n-3; ++i) {
        if(static_cast<long long>(A[i]) < static_cast<long long>(A[i+1]) + A[i+2] ) return 1;
    }
    return 0;
}
```  
[codility/sorting/triangle](../codility/sorting/triangle.cpp)

## Accessing elements of an empty array 

## short circuit evaluation
```c++
isSubIsland = isSubIsland && DFS(grid1, grid2, nr, nc); //! This is mistake!!! DFS will not be called if isSubIsland is false!!!
```

```c++
  bool DFS(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int r, int c) {
    grid2[r][c] = 0;
    
    bool isSubIsland = (grid1[r][c] == 1);
    cout << r << "," << c << ":" << isSubIsland << '\n';
    
    for(int i = 0; i < size(dr); ++i) {
      const int nr = r + dr[i];
      const int nc = c + dc[i];
      if( 0 <= nr && nr < rowsN && 0 <= nc && nc < colsN && grid2[nr][nc])
        isSubIsland = isSubIsland && DFS(grid1, grid2, nr, nc); //! This is mistake!!! DFS will not be called if isSubIsland is false!!!
    }
    
    return isSubIsland;
  }
```

# Optimizations
## using integers instead of double
As operations on integers are faster for case when we only need relative comparision we could replace division.
For ex. when comparing avg of 2 and 3 elements sequences we could instead of multiply by LCM (least common multiply)
```c++
avg2 = (a[i] + a[i+1]) / 2;
avg3 = (a[i] + a[i+1] + a[i+2]) / 3;
int min = min(avg2, avg3);
```

```c++
avg2 = (a[i] + a[i+1]) * 3; // * 6
avg3 = (a[i] + a[i+1] + a[i+2]) * 2; // *6
int min = min(avg2, avg3);
```

example:  
[codility/prefixSum/minAvgTwoSlice](../codility/prefixSum/minAvgTwoSlice.cpp)

## given 2 arrays process the smaller one
[leetcode/arrays/intersectionOfTwoArrays2](../leetcode/arrays/intersectionOfTwoArrays2.hpp)
```c++
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    if(nums1.size() > nums2.size()) return intersect(nums2, nums1);
    ...
}
```

## space optimization
Reusing initial array for storage of some information during processing  
(in case if there are only positive values in the array):  
[leetcode/arrays/findAllNumbersDisappearedInAnArray](leetcode/arrays/findAllNumbersDisappearedInAnArray.hpp)

## Sorting idxs of elements (if they are heavy) instead of elements
We are going to sort `vector<MyType> elements`  
We assign idxs to elements we are going to sort: 0,1,2,3,4,5,6,7
This vector of idxs we pass to sorting routine, which get`s information of comparision of elements for ex. from unordered_map by index
As a resulting vector we get a permutation of idxs: res,
where `res[i] = j, means at i-th position should be elements[j] element `
[leetcode/arrays/kClosestPointsToOrigin](../leetcode/arrays/kClosestPointsToOrigin.hpp)

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

##### Rotated sorted array (different from Andrei Stankevich, all ends are included)
[leetcode/binary_search/searchInRotatedSortedArray](leetcode/binary_search/searchInRotatedSortedArray.hpp)     
[leetcode/arrays/findMinimumInRotatedSortedArray](leetcode/arrays/findMinimumInRotatedSortedArray.hpp)   

##### Some problems with Binary search application
[leetcode/binary_search/TheKWeekestRowsInAMatrix](../leetcode/binary_search/TheKWeekestRowsInAMatrix.hpp)

#### k-th element
This is my implementation based on Stankevich Quick sort implementation  
Also the same implementation is presented in  
[Лекция 4. Сортировка подсчетом и применение встроенных сортировок](../shujkova/lectures/lec4.pdf)  
[nth_element](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/nth_element.hpp)   
[Pestov lecture LKSH b prime 2008 Разбор задачи Kth ("K-ый минимум") из контеста первого дня: модификация алгоритма быстрой сортировки для нахождения k-й порядковой статистики.]
`/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item5.mp4`  
[leetcode/arrays/kLargestElementInAnArray](../leetcode/arrays/kLargestElementInAnArray.hpp)  

Different partiton schemes: Stankevich & Shujkova, Lomuto`s
[leetcode/arrays/topKFrequentElements](../leetcode/arrays/topKFrequentElements.hpp)  
One more exemple of quick select:  
[leetcode/arrays/kClosestPointsToOrigin](../leetcode/arrays/kClosestPointsToOrigin.hpp)

## Recursion
Great explanation at Stanford CS 106B (2008) by Julie Zelenski: `/run/media/oleg/TOSHIBA EXT/cs106b_2008_ProgrammingAbstractionsStanford`    
Problem types:  
[permutation problem](../cs106b/permutations.cpp)    
[subset_problem](../cs106b/subset.cpp)  
[towers of Hanoi](../cs106b/moveTower.cpp)  

### Backtracking:  
[sudoku Solver](../cs106b/sudokuSolver.cpp)  
[queens8](../cs106b/queens8.cpp)
[leetcode/graphs/tree/pathSum2](../leetcode/graphs/tree/pathSum2.hpp)

### Tail recursion
Is mentioned as a solution to this problem: [leetcode/graphs/tree/maximumDepthOfBinaryTree](../leetcode/graphs/tree/maximumDepthOfBinaryTree.hpp)  
 the idea is explained here: [leetcode/graphs/tree/maximumDepthOfBinaryTree](../leetcode/graphs/tree/maximumDepthOfBinaryTree.odt)  

## greedy
[leetcode/arrays/minimumNumberOfArrorsToBurstBaloons](../leetcode/arrays/minimumNumberOfArrorsToBurstBaloons.hpp)

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

### states storage
For some problems we don't need to store all the states,  
for ex. for these problems:  
[leetcode/DP/Fibonacci](../leetcode/DP/Fibonacci.hpp)  
[leetcode/DP/Tribonacci](../leetcode/DP/Tribonacci.hpp)  
[leetcode/DP/climbingStairs](../leetcode/DP/climbingStairs.hpp)  
[leetcode/DP/minCostClimbingStairs](../leetcode/DP/minCostClimbingStairs.hpp)  
[leetcode/DP/house_robber](../leetcode/DP/house_robber.hpp)  
for the current state estimation we need only to now a few previous states, so there is no need in an array to store all states

## Two pointers
[pashka/algos/include/two_pointers_method](../pashka/algos/include/two_pointers_method.hpp)  
[pashka/README](../pashka/README.md)  

### common tasks
longest-substring-without-repeating-characters   
[twoPointers/longestSubstringWithoutRepeatingCharacters](../leetcode/twoPointers/longestSubstringWithoutRepeatingCharacters.hpp)
```c++
//! 10/02/2022
//! Two pointers technique by Pavel Marvin rocks!!!
/*
    Runtime: 34 ms, faster than 50.39% of C++ online submissions for Longest Substring Without Repeating Characters.
    Memory Usage: 8.4 MB, less than 60.91% of C++ online submissions for Longest Substring Without Repeating Characters.
 */
class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> freq;
    int best{0};

    int j{0};
    for(int i = 0; i < s.size(); ++i) {
      ++freq[s[i]];
      while(freq[s[i]] > 1 ) {
        --freq[s[j]];
        ++j;
      }
      best = max(best, i-j+1);
    }

    return best;
  }
};
```

## Combinatorics
### Combinations
[Skiena_programmingChallenges_book/combinations](../Skiena_programmingChallenges_book/combinations.cpp)

## Geometry
### Sweep line (Scan line)
[Rucode/scanline/README](../Rucode/scanline/README.md)  
`/run/media/oleg/TOSHIBA EXT/RUCODE/ScanLineNevstruev.mp4`     
[HSE/LKSH_2018/8_Metod_skaniruyuschei_774_pryamoi_774](../HSE/LKSH_2018/8_Metod_skaniruyuschei_774_pryamoi_774.pdf)  

[codility/sorting/numberOfDiscIntersections](../codility/sorting/numberOfDiscIntersections.cpp)

## Graphs
### state representation by setting bits in number
[leetcode/DFS_BFS/shortestPathsVisitingAllNodes](../leetcode/DFS_BFS/shortestPathsVisitingAllNodes.hpp)   
[leetcode/DFS_BFS/shortestPathsVisitingAllNodes.odt](../leetcode/DFS_BFS/shortestPathsVisitingAllNodes.odt)

### DFS

#### Important problems
##### Shortest Paths with alternating color
[leetcode/DFS_BFS/shortestPathWithAlternatingColors](../leetcode/DFS_BFS/shortestPathWithAlternatingColors.hpp)


#### WHITE/GRAY/BLACK DFS
[leetcode/DFS_BFS/findEventualSafeStates](../leetcode/DFS_BFS/findEventualSafeStates.hpp)

#### for DAG no need in visited array
Very important that it is Directed Graph, for Undirected graph we need visited array!!!
(because on Undirected graph we might move back and fourth between parent and child node infinitly)  
see: [leetcode/DFS_BFS/reoderRoutesToMakeAllPathsLeadToTheCityZero](../leetcode/DFS_BFS/reoderRoutesToMakeAllPathsLeadToTheCityZero.hpp)

[leetcode/DFS_BFS/timeNeedToInformAllEmployees](../leetcode/DFS_BFS/timeNeedToInformAllEmployees.hpp)  
Because there are no cycles we will not encounter the same node multiple times so we don't need visited information

#### for undirected graph with no cycles
We need parent array, in order to avoid visiting parent vertex from child  
(as graph is undirected it can be seen as graph where each edge is represented by 2 directed edges,  
in that sense there are cycles between parent & child, to avoid these cycles during traversal - we use parent array)  
[leetcode/graphs/graphValidTree](../leetcode/graphs/graphValidTree.hpp)  

#### Find All Paths from source to target on DAG  
[leetcode/DFS_BFS/allPathsFromSourceToTarget](../leetcode/DFS_BFS/allPathsFromSourceToTarget.hpp)  

#### backtracking
Arises when we use procedural recursion(no return value) (we store some state in the internal variables)  
When we have functional recursion(with a return value) there is no need in backtracking, compare 2 implementations

[leetcode/DFS_BFS/timeNeedToInformAllEmployees](../leetcode/DFS_BFS/timeNeedToInformAllEmployees.hpp)  
Because there are no cycles we will not encounter the same node multiple times so we don't need visited information
Functional recursion with a return value  
```c++
class Solution {
public:

  int DFS(int id, unordered_map<int, vector<int> >& graph, vector<int>& informTime) {
    int maxSubordTime{0};
    for(auto subordinateId : graph[id]) {
      maxSubordTime = max(maxSubordTime, DFS(subordinateId, graph, informTime));
    }
    return informTime[id] + maxSubordTime;
  }
  int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
    unordered_map<int, vector<int>> graph;
    for(int i = 0; i < n; ++i) {
      graph[manager[i]].push_back(i);
    }
    return DFS(headID, graph, informTime);
  }
};
```

Procedural recursion where the state is stored in an internal variable  
```c++
class Solution {
public:
  /*
  15
  0
  [-1,0,0,1,1,2,2,3,3,4,4,5,5,6,6]
  [1,1,1,1,1,1,1,0,0,0,0,0,0,0,0]

  */
  int timeSoFar{0};
  int maxTime{0};
  void DFS(unordered_map<int, vector<int> >& graph, int id, vector<int>& informTime) {
    timeSoFar += informTime[id];

    if(informTime[id] == 0)
      maxTime = max(maxTime, timeSoFar);

    for(auto subordinateId : graph[id]) {
      DFS(graph, subordinateId, informTime);
    }

    timeSoFar -= informTime[id]; // done with the node, backtrack
  }

  int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
    unordered_map<int,vector<int> > graph;
    for(int i = 0; i < n; ++i) {
      if(manager[i] >=0) graph[manager[i]].push_back(i);
    }

    DFS(graph, headID, informTime);
    return maxTime;
  }
};
```

##### Combinations
several methods: recursive, iterative, using number as a bit mask  
[leetcode/combinatorics/combinations](../leetcode/combinatorics/combinations.hpp)

### BFS
[Алгоритм BFS. Очередь.] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day2_item3.mp4`  

Level by level traversal idea (no need to store level information per node):  
at any given moment during BFS there are nodes in queue with dist k and possibly with k + 1    
If we save queue size before we start adding nodes at distance K+1 - we will have number of nodes at distance k  
So we know how many nodes are on the given level and how many we are going to pop and process in order to populate  
the next level  
so we don't need to store explicit distance per node  
An example of this approach:  
[leetcode/DFS_BFS/asFarFromLandAsPossible](../leetcode/DFS_BFS/asFarFromLandAsPossible.hpp)

#### Corner cases
This might be the case that some nodes are not reachable  
[leetcode/DFS_BFS/rottingOranges](leetcode/DFS_BFS/rottingOranges.hpp)

#### optimizations
##### prioritizing nodes based on distance to target, queue state representation

[leetcode/DFS_BFS/minimumGeneticMutation](../leetcode/DFS_BFS/minimumGeneticMutation.hpp)  


##### using preprocessing for faster transition between states
[leetcode/DFS_BFS/wordLadder](../leetcode/DFS_BFS/wordLadder.hpp)  

##### BiDirectional BFS
[leetcode/DFS_BFS/wordLadder](../leetcode/DFS_BFS/wordLadder.hpp)  


##### state representation
[leetcode/DFS_BFS/openTheLock](../leetcode/DFS_BFS/openTheLock.hpp)  


#### Some tasks solved by BFS
[leetcode/DFS_BFS/minimumJumpsToReachHome](../leetcode/DFS_BFS/minimumJumpsToReachHome.hpp)

### Дейкстра

#### lectures
[Дейкстра Лектор: Сергей Копелиович] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day2_item8.mp4`
[Дейкстра. Реализация алгоритма. Лектор: Сергей Копелиович]`/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day2_item9.mp4`  

### Floyd Warshall algorithm
TODO: understand why it works from https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm  
[Skiena_programmingChallenges_book/FloydWarshall](../Skiena_programmingChallenges_book/FloydWarshall.cpp)

#### books
Steven S. Skiena, Miguel A. Revilla. Programming Challenges. The Programming Contest Training Manual.pdf  

#### Algorithm:
[Skiena_programmingChallenges_book/Dijkstra](../Skiena_programmingChallenges_book/Dijkstra.cpp)  

### Беллман-Форд
[Алгоритм Форда-Беллмана. Поиск кратчайшего пути от данной вершины в графе с отрицательными ребрами. Описание алгоритма. Циклы отрицательного веса. Лектор: Сергей Копелиович]
`/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day3_item4.mp4`

### Алгоритм Флойда
[Алгоритм Флойда. Описание алгоритма, реализация, оценка сложности. Оптимизация по памяти.]
`/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day3_item5.mp4`

# Data structures
### arrays

### shift (rotate an array)
[leetcode/arrays/rotateArray](../leetcode/arrays/rotateArray.hpp)  
[leetcode/arrays/performStringShifts](../leetcode/arrays/performStringShifts.hpp)

### matrix
#### Spiral traversal (idea with an array of offsets for moves)
[leetcode/arrays/spiralMatrix](../leetcode/arrays/spiralMatrix.hpp)  
[leetcode/arrays/spiralMatrix2](../leetcode/arrays/spiralMatrix2.hpp)

#### boyer-moore voting algorithm
https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm  


#### Kadane's algorithm (max subarray)
https://en.wikipedia.org/wiki/Maximum_subarray_problem  
https://www.interviewbit.com/blog/maximum-subarray-sum/  
[leetcode/buySellStock/bestTimeToBuySellStock](../leetcode/buySellStock/bestTimeToBuySellStock.hpp)  
[codility/maximumSlice/maxSliceSum](../codility/maximumSlice/maxSliceSum.cpp)  
####  Bidirectional Kadane's algorithm
[codility/maximumSlice/maxDoubleSliceSum](../codility/maximumSlice/maxDoubleSliceSum.cpp)   

#### prefix sum
[codility/prefixSum/passingCars](../codility/prefixSum/passingCars.cpp)  
[codility/prefixSum/genomicRangeQuery](../codility/prefixSum/genomicRangeQuery.cpp)  

Sometimes you don't have to store prefixSum explicitly:  
[leetcode/arrays/maximumSizeSubarraySumEqualsK](../leetcode/arrays/maximumSizeSubarraySumEqualsK.hpp)

#### Sliding window
[leetcode/arrays/minimumSwapsToGroupAllOnceTogether](../leetcode/arrays/minimumSwapsToGroupAllOnceTogether.hpp)

#### Move zeros
[arrays/moveZeros](../leetcode/arrays/moveZeros.hpp)

#### in array of duplicate elements and only one distinct find distinct element
[codility/oddOccurienciesInArray](../codility/arrays/oddOccurienciesInArray.cpp)

#### in an array all elements are from 1..n, one element is missing, find it
[codility/timeComplexity/permMissingElem](../codility/timeComplexity/permMissingElem.cpp)  

#### Leader
[codility/leader/6-Leader](../codility/leader/6-Leader.pdf)
[codility/leader/dominator](../codility/leader/dominator.cpp)

### Stack
[codility/stacks&Queues/fish](../codility/stacks&Queues/fish.cpp)
#### Brackets validation
for multiple types - we use stack:  
[codility/stacks&Queues/brackets](../codility/stacks&Queues/brackets.cpp)  
if there is only one type of brackets - simple counter (balance) is sufficient:    
[codility/stacks&Queues/nesting](../codility/stacks&Queues/nesting.cpp)    


### linked list
#### reverse linked list
Reverse using 2 pointers (prev, cur)  
[leetcode/Recursion_Backtracking/reverseLinkedList](../leetcode/Recursion_Backtracking/reverseLinkedList.hpp)  
[leetcode/lists/plusOneLinkedList](../leetcode/lists/plusOneLinkedList.hpp)  

#### dummy node technique
[leetcode/lists/removeDuplicatesFromSortedList2](../leetcode/lists/removeDuplicatesFromSortedList2.hpp)  
[leetcode/lists/swapNodesInPairs](../leetcode/lists/swapNodesInPairs.hpp)  
[leetcode/lists/designLinkedList](../leetcode/lists/designLinkedList.hpp)
[leetcode/lists/reverseNodesInKGroup](../leetcode/lists/reverseNodesInKGroup.hpp)  
[leetcode/lists/addTwoPolynomialsRepresentedAsLinkedLists](../leetcode/lists/addTwoPolynomialsRepresentedAsLinkedLists.hpp)  
[leetcode/lists/sortList](../leetcode/lists/sortList.hpp)   
[leetcode/lists/copyListWithRandomPointer](../leetcode/lists/copyListWithRandomPointer.hpp)

#### partition linked list
[leetcode/lists/sortList](../leetcode/lists/sortList.hpp)  

### multiset
good example of application ransomeNote  
[strings/ransomNote](../leetcode/strings/ransomNote.hpp)
```c++
//! using std::multiset https://leetcode.com/problems/ransom-note/discuss/611644/C%2B%2B-solution-in-3-lines
class Solution {
public:
  bool canConstruct(string ransomNote, string magazine) {
    std::multiset<char> mag(magazine.begin(), magazine.end());
    std::multiset<char> ransom(ransomNote.begin(), ransomNote.end());
    return std::includes(mag.begin(), mag.end(), ransom.begin(), ransom.end());
  }
};
```

### trees
#### Construction
[leetcode/graphs/tree/constructBinaryTreeFromPreorderAndInorderTraversal](../leetcode/graphs/tree/constructBinaryTreeFromPreorderAndInorderTraversal.hpp)  
[leetcode/graphs/tree/constructBinaryTreeFromPreorderAndInorderTraversal](../leetcode/graphs/tree/constructBinaryTreeFromPreorderAndInorderTraversal.odt)

[graphs/tree/serializeAndDeserializeBinaryTree](../graphs/tree/serializeAndDeserializeBinaryTree.hpp)  

#### traversal
[leetcode/tree/n-aryTreePreorderTraversal](../leetcode/graphs/tree/n-aryTreePreorderTraversal.hpp)  

Recursive version:  
```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
 */
 
 class Solution {
 public:
   void dfs(Node* v, vector<int>& preorder) {
     preorder.push_back(v->val);
 
     if(v->children.empty()) return;
 
     for(auto& u : v->children) {
       dfs(u, preorder);
     }
   }
 
   vector<int> preorder(Node* root) {
     vector<int> res;
     if(!root) return res;
 
     dfs(root, res);
     return res;
   }
 };
```
Iterative version:  
```c++
//! 10/01/2022
//! I wrote comments on how calls would look like if we do recursive traversal
//! Looked at the tree, how it should be traversed and came out with this idea
/*
  Runtime: 28 ms, faster than 77.48% of C++ online submissions for N-ary Tree Preorder Traversal.
  Memory Usage: 11.2 MB, less than 75.98% of C++ online submissions for N-ary Tree Preorder Traversal.
 */
class Solution {
public:
  vector<int> preorder(Node* root) {
    vector<int> res;
    if(!root) return res;
    // root
    // left
    // right
    stack<Node*> s;

    s.push(root);

    while(!s.empty()){
      auto v = s.top();
      s.pop();
      res.push_back(v->val);
      for(auto it = rbegin(v->children); it!= rend(v->children); ++ it) {
        s.push(*it);
      }
    }

    return res;
  }
};
```

[leetcode/tree/n-aryTreePostOrderTraversal](../leetcode/graphs/tree/n-aryTreePostOrderTraversal.hpp)

##### Level order traversal
[Using queue or using stack](../leetcode/graphs/tree/binaryTreeZigZagLevelOrderTraversal.odt)  
[Different implementations](../leetcode/graphs/tree/binaryTreeRightSideView.odt)

#### BST
https://cse.taylor.edu/~jdenning/classes/cos265/slides/09_BinarySearchTrees.html  

##### Find k-th element
[leetcode/graphs/tree/kthSmallestElementInABST](../leetcode/graphs/tree/kthSmallestElementInABST.hpp)  
[leetcode/graphs/tree/kthSmallestElementInABST.odt](../leetcode/graphs/tree/kthSmallestElementInABST.odt)  

##### Find successor
[companies/Citadel/inorderSuccessorInBST](../leetcode/companies/Citadel/inorderSuccessorInBST.cpp)

##### Iterator
[leetcode/graphs/tree/binarySearchTreeIterator](../leetcode/graphs/tree/binarySearchTreeIterator.hpp)  
[leetcode/graphs/tree/binarySearchTreeIterator.odt](../leetcode/graphs/tree/binarySearchTreeIterator.odt)  

##### deletion
Hibbard deletion:  
https://joshhug.gitbooks.io/hug61b/content/chap10/chap102.html  
https://algs4.cs.princeton.edu/32bst/  
[leetcode/graphs/tree/deleteNodeInABST](../leetcode/graphs/tree/deleteNodeInABST.hpp)  
[leetcode/graphs/tree/deleteNodeInABST.odt](../leetcode/graphs/tree/deleteNodeInABST.odt)  

### Fenwick tree (Binary Indexed Tree)
[Fenwick Tree or Binary Indexed Tree](../freeCodeCamp/DataStructures/BIT.cpp)  

### Trie
https://www.quora.com/What-is-the-best-open-source-C-implementation-of-a-trie


### Disjoint set
usage:  
The primary use of disjoint sets is to address the connectivity between the components of a network.   
The “network“ here can be a computer network or a social network.  
For instance, we can use a disjoint set to determine if two people share a common ancestor.

[leetcode/graphs/graphValidTree](../leetcode/graphs/graphValidTree.hpp)

## Strings
### Main facts about characters
26 letters in english alphabet    
'a' - 97    
'A' - 65  
switching case for the given letter upper/lower is about toggling one bit in the char - 32 (2^5)  
### Main definitions
[main definitions]`/run/media/oleg/TOSHIBA EXT/codeforces/itmoAcademy/stringsMainDefinitions.mp4`

### match
#### Rabin-Karp
Main ideas: use sliding window for efficient computation of hash,
called rolling hash.
As computed hash might be very large, o computations by modulo to make sure that results fits within computer words  

Running time: when number of matches is small or we are interested only in a first match - `O(m + n-m)`  
Worst case: large number of matches (e.g. `t = "aaaaaaaaaaaaaaaaaa...", p = "aaaaaaaaaaa" `) - `O( (n-m)*m)`  
Spurious hits - when different strings hav the same hash value, hence in case of equal hash - eqaulity check is obligatory  
Also for modulo - it is adviced to choose prime, larger then p size;
[MIT/CLRS/ch32/rabin-karp](../MIT/CLRS/ch32/rabin-karp.cpp)   
[/run/media/oleg/TOSHIBA EXT/MIT/CS6-006_fall2011/Lec9_table_doubling_Karp-Rabin.mp4](/run/media/oleg/TOSHIBA EXT/MIT/CS6-006_fall2011/Lec9_table_doubling_Karp-Rabin.mp4)

#### KMP (Knuth Morris Prat)
Idea: use previous information about matches, for this compare pattern with itself.  
Concept of prefix function `pi(x)` - length of prefix that is also a suffix for prefix of pattern of length x  
Two stages: construct prefix function and use it for search  
[MIT/CLRS/ch32/KMP](../MIT/CLRS/ch32/KMP.cpp)  




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

### Pattern matching
#### Using DP
[leetcode/strings/wildcardMatching](../leetcode/strings/wildcardMatching.hpp)

# Implementation techniques
## using array of offsets for a matrix exploration
TODO include here leetcode problems that I solved using this technique:
arrays/spiralMatrix.hpp    
and one of for DFS/BFS: DFS_BFS/maxAreaOfIsland.hpp  

## using arrays to store initially given separate but related values
[leetcode/tricks/designParkingSystem](../leetcode/tricks/designParkingSystem.hpp)

# Bits manipulation
## count number of bits in a number
```c++
__builtin_popcount
```
here: https://stackoverflow.com/questions/60165922/stdbitsetncount-vs-builtin-popcount
is mentioned that `__builtin_popcount` is an gcc extension, so it is not portable in comparision to `std::bitset`,  
which is defined in standard, and mentioned that on godBolt their code is generated by the same instructions  
Also there is `std::popcount` since C++20 (https://en.cppreference.com/w/cpp/numeric/popcount)  

# Math
## divisors
### count divisors
[codility/primeAndCompositeNumbers/countFactors](../codility/primeAndCompositeNumbers/countFactors.cpp)

### find divisors
`/run/media/oleg/TOSHIBA EXT/ITMO/pashka/Паша_и_алгосы/Быстрое_нахождение_делителей_пилотный_выпуск.mp4`
## factorization

## Euclidean algorithm (gcd)
[codility/euclideanAlgorithm/chocolatesByNumbers](../codility/euclideanAlgorithm/chocolatesByNumbers.cpp)

## Modulo operations
[codility/fibonacciNumbers/ladders](../codility/fibonacciNumbers/ladders.cpp)

# Long arithmetics
[leetcode/strings/addStrings](../leetcode/strings/addStrings.hpp)  
[leetcode/strings/multiplyString](../leetcode/strings/multiplyStrings.hpp)  