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

# Common mistakes
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

##### Binary search in sorted rotated array
[leetcode/binary_search/searchInRotatedSortedArray](leetcode/binary_search/searchInRotatedSortedArray.hpp)   
```c++
//! Idea: use binary search, l & r - denote ends of the array,
//! every step we cut search area on half, by observing values at arr[l], arr[r] and arr[m]
//! We could tell whether the part under consideration is rotated or not, if not we use ordinary binary search
//! otherwise we detect in which part of the array (high/low) is element under consideration
//! and there is helpful this checks:
//! nums[l] <= target && target <= nums[m]
//! nums[m] <= target && target <= nums[r]
class Solution {
public:

  // 1 3 5
  // 5 1 3
  // 8 2 4 6
  // 7 8 9 11 1 3 5
  int search(vector<int>& nums, int target) {
    const int n = nums.size();
    int l{0}, r{n-1};
    while(r-l>1) {
      const int m = l + (r-l) / 2;
      if(nums[l] < nums[r]) {
        if(nums[m] >= target) r=m;
        else l = m;
      }
      else {
        if(nums[l] <= nums[m]) {// large part
          if(nums[l] <= target && target <= nums[m]) r = m;
          else l =m;
        }
        else { // smallest part
          if(nums[m] <= target && target <= nums[r]) l = m;
          else r = m;
        }
      }
    }
    if(nums[l] == target) return l;
    if(nums[r] == target) return r;
    return -1;
  }
};
```

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

## Recursion
Great explanation at Stanford CS 106B (2008) by Julie Zelenski: `/run/media/oleg/TOSHIBA EXT/cs106b_2008_ProgrammingAbstractionsStanford`    
Problem types:  
[permutation problem](../cs106b/permutations.cpp)    
[subset_problem](../cs106b/subset.cpp)  
[towers of Hanoi](../cs106b/moveTower.cpp)  

### Backtracking:  
[sudoku Solver](../cs106b/sudokuSolver.cpp)  
[queens8](../cs106b/queens8.cpp)

### Tail recursion
Is mentioned as a solution to this problem: [leetcode/graphs/tree/maximumDepthOfBinaryTree](../leetcode/graphs/tree/maximumDepthOfBinaryTree.hpp)  
 the idea is explained here: [leetcode/graphs/tree/maximumDepthOfBinaryTree](../leetcode/graphs/tree/maximumDepthOfBinaryTree.odt)  

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

## Graphs
### state representation by setting bits in number
[leetcode/DFS_BFS/shortestPathsVisitingAllNodes](../leetcode/DFS_BFS/shortestPathsVisitingAllNodes.hpp)   
[leetcode/DFS_BFS/shortestPathsVisitingAllNodes.odt](../leetcode/DFS_BFS/shortestPathsVisitingAllNodes.odt)

### DFS

#### Important problems
##### Shortest Paths with alternating color
[leetcode/DFS_BFS/shortestPathWithAlternatingColors](../leetcode/DFS_BFS/shortestPathWithAlternatingColors.hpp)
```c++
//! https://leetcode.com/problems/shortest-path-with-alternating-colors/

//! 10/06/2022
//! Idea use BFS (as graph is unweighted and we need shortest dist)
//! As graph might have cycles - we need visited array,
//! To be able to traverse only valid vertexes (color alternating condition is obeyed) we introduce for each vertex
//! information about what color edge we took to get to this vertex
//! we trick here to allow the same vertex to be visited from edges of different colors (1), that is why:
//!  set<pair<int,Color/*color of edge we took*/>> visited;
//!
//! Because of (1) trick we could visit vertex 2 times, so it is important not to overwrite min distance calculated for it,
//! that is why:
//!         if(distance[v] == -1)
//!          distance[v] = curDist;
//!        else
//!          distance[v] = min(distance[v], curDist);
//!
//! For BFS - we use trick with getting layer size before processing it and populating a new layer
//! this allows to estimate distance to each layer without need to store this information per node

/*
    Runtime: 25 ms, faster than 82.14% of C++ online submissions for Shortest Path with Alternating Colors.
    Memory Usage: 15.5 MB, less than 39.94% of C++ online submissions for Shortest Path with Alternating Colors.
 */
class Solution {
public:
  enum Color{NOCOLOR, RED, BLUE};
  vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {

    unordered_map<int, vector<int>> redGraph, blueGraph;
    for(auto& edge : redEdges) {
      redGraph[edge[0]].push_back(edge[1]);
    }
    for(auto& edge : blueEdges) {
      blueGraph[edge[0]].push_back(edge[1]);
    }

    vector<int> distance(n, -1);

    queue<pair<int, Color>> q;
    set<pair<int,Color/*color of edge we took*/>> visited;
    visited.emplace(0, RED);
    visited.emplace(0, BLUE);
    q.emplace(0, NOCOLOR);

    int curDist{-1};
    while(!q.empty()) {
      int levelSize = q.size();
      ++curDist;
      while(levelSize--) {
        auto [v, color] = q.front();
        q.pop();
        if(distance[v] == -1)
          distance[v] = curDist;
        else
          distance[v] = min(distance[v], curDist);

        if(color == NOCOLOR) {
          for(auto u : redGraph[v]) {
            if(!visited.count({u, RED})) {
              q.emplace(u, RED);
              visited.emplace(u,RED);
            }
          }
          for(auto u : blueGraph[v]) {
            if(!visited.count({u, BLUE})) {
              q.emplace(u, BLUE);
              visited.emplace(u,BLUE);
            }
          }
        } else if (color == RED) {
          for(auto u : blueGraph[v]) {
            if(!visited.count({u, BLUE})) {
              q.emplace(u, BLUE);
              visited.emplace(u, BLUE);
            }
          }
        } else {
          for(auto u : redGraph[v]) {
            if(!visited.count({u,RED})) {
              q.emplace(u, RED);
              visited.emplace(u, RED);
            }
          }
        }
      }
    }
    return distance;
  }
};
``` 


#### WHITE/GRAY/BLACK DFS
[leetcode/DFS_BFS/findEventualSafeStates](../leetcode/DFS_BFS/findEventualSafeStates.hpp)
```c++
//! https://leetcode.com/problems/find-eventual-safe-states/

//! 10/06/2022
//! The idea to use WHITE/GRAY/BLACK DFS for a cycle detection
//! Once a cycle is detected we exit from it and pass return value indicating what it was found to callers
//! If return value is false for any children of the current vertex - we don't mark it BLACK(Done)
//! So if there is a cycle all nodes on the path from starting vertex to the cycle itself will be not completed
//! But as they are visited they will be GRAY
//! After running DFS - nodes marked BLACK are safe
/*
  Runtime: 413 ms, faster than 24.19% of C++ online submissions for Find Eventual Safe States.
  Memory Usage: 54 MB, less than 40.47% of C++ online submissions for Find Eventual Safe States.
 */
class Solution {
public:
  enum Color{WHITE, GRAY, BLACK};
  unordered_map<int,Color> color; // By default color[v] == 0 (WHITE)

  bool DFS(vector<vector<int>>& graph, int v) {
    if(color[v] == GRAY) return false; // we have not completed the vertex due to it was in cycle or leaded to cycle

    // we have completed vertex and the same for it's children it is safe
    // might be the case in the main loop (1)
    if(color[v] == BLACK) return true;

    color[v] = GRAY;
    for(auto u : graph[v]) {
      if(color[u] == GRAY) return false;
      if(color[u] == WHITE)
        if(!DFS(graph, u)) return false; // will not reach (0) and v will not be marked as finished (BLACK)
    }
    color[v] = BLACK; // (0)
    return true;
  }

  vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    vector<int> res;
    for(int v = 0; v < graph.size(); ++v) { // (1)
      if(DFS(graph, v))
        res.push_back(v);
    }

    return res;
  }
};
```

#### for DAG no need in visited array
Very important that it is Directed Graph, for Undirected graph we need visited array!!!
(because on Undirected graph we might move back and fourth between parent and child node infinitly)  
see: [leetcode/DFS_BFS/reoderRoutesToMakeAllPathsLeadToTheCityZero](../leetcode/DFS_BFS/reoderRoutesToMakeAllPathsLeadToTheCityZero.hpp)

[leetcode/DFS_BFS/timeNeedToInformAllEmployees](../leetcode/DFS_BFS/timeNeedToInformAllEmployees.hpp)  
Because there are no cycles we will not encounter the same node multiple times so we don't need visited information
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

#### Find All Paths from source to target on DAG  
[leetcode/DFS_BFS/allPathsFromSourceToTarget](../leetcode/DFS_BFS/allPathsFromSourceToTarget.hpp)  
```c++
//! 18/05/2022
/*
 Runtime: 29 ms, faster than 39.20% of C++ online submissions for All Paths From Source to Target.
 Memory Usage: 11.9 MB, less than 62.97% of C++ online submissions for All Paths From Source to Target.
 */
class Solution {
  void dfs(vector<vector<int>>& graph, int v) {
    _path.push_back(v);
    if(v == graph.size()-1) _result.push_back(_path);
    for(auto u : graph[v]) {
      dfs(graph, u);
    }
    _path.pop_back(); // when done with the v (have visited all it's children), backtrack
  }
  vector<int> _path;
  vector<vector<int>> _result;
public:
  vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    dfs(graph, 0);
    return _result;
  }
};

```
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

#### optimizations
##### prioritizing nodes based on distance to target, queue state representation

[leetcode/DFS_BFS/minimumGeneticMutation](../leetcode/DFS_BFS/minimumGeneticMutation.hpp)  
```c++
//! https://leetcode.com/problems/minimum-genetic-mutation/

//! 10/09/2022
/*
    Runtime: 0 ms, faster than 100.00% of C++ online submissions for Minimum Genetic Mutation.
    Memory Usage: 6.6 MB, less than 83.30% of C++ online submissions for Minimum Genetic Mutation.
 */
//! Several concepts : using BFS (getting layer size before it's processing allows to distinguish layers and estimate distance to each
//! without need for storage distance information per node)
//! As we might have 10^8 variants at the last layer we optimizing our BFS:
//! - we organize nodes by distance to the end node, and add to next layer only nodes with min distance to end
//! - instead of strings we store idxs in bank
class Solution {
public:

  static size_t distance(string_view a, const string_view b) {
    size_t cnt{0};
    for(int i = 0; i < a.size(); ++i) {
      if(a[i]!=b[i])++cnt;
    }
    return cnt;
  }

  int minMutation(string start, string end, vector<string>& bank) {
    if(start == end) return 0;

    queue<int> q;
    unordered_set<int> visited;

    for(int i = 0; i < bank.size(); ++i) {
      if(distance(start, bank[i]) == 1) {
        q.push(i);
        visited.insert(i);
      }
    }

    int dist{0};
    while(!q.empty()) {
      int levelSize = q.size();

      using ElemT = pair<size_t/*distance*/, int /*strIdx*/>;
      priority_queue<ElemT, vector<ElemT>, std::greater<ElemT> > pq;

      ++dist;

      while(levelSize--) {
        const auto strIdx = q.front();
        q.pop();
        if(bank[strIdx] == end) return dist;

        for(int i = 0; i < bank.size(); ++i) {
          if(!visited.count(i) && distance(bank[strIdx], bank[i]) == 1) {
            pq.emplace(distance(bank[i], end), i);
            visited.insert(i);
          }
        }
      }

      while(!pq.empty()) {
        auto [curDist, strIdx] = pq.top();
        pq.pop();
        q.push(strIdx);
      }
    }
    return -1;
  }
};


//! TODO: try bidirectional BFS
//! https://leetcode.com/problems/minimum-genetic-mutation/discuss/91559/JAVA-Bidirectional-BFS-method-same-as-Word-Ladder
//! https://leetcode.com/problems/minimum-genetic-mutation/discuss/91604/C%2B%2B-two-end-BFS-solution-exactly-same-as-127.Word-Ladder
```

##### state representation
[leetcode/DFS_BFS/openTheLock](../leetcode/DFS_BFS/openTheLock.hpp)  
```c++
//! https://leetcode.com/problems/open-the-lock/


//! 10/09/2022
/*
    Runtime: 1861 ms, faster than 5.05% of C++ online submissions for Open the Lock.
    Memory Usage: 23.5 MB, less than 92.99% of C++ online submissions for Open the Lock.
 */
class Solution {
public:
  int openLock(vector<string>& deadends, string target) {
    using ElemT = array<char, 4>;

    vector<ElemT> deadEndsInt(deadends.size());
    ElemT targetInt;

    for(int i = 0; i < deadends.size(); ++i) {
      for(int j = 0; j < target.size(); ++j) {
        deadEndsInt[i][j] = deadends[i][j] - '0';
      }
    }

    for(int j = 0; j < target.size(); ++j) {
      targetInt[j] = target[j] - '0';
    }


    auto isDeadEnd = [&deadEndsInt](const auto& arr) {
      for(auto& d : deadEndsInt) {
        if(d == arr) return true;
      }
      return false;
    };


    queue<ElemT> q;
    set<ElemT> seen;
    ElemT start = {0,0,0,0};
    if(isDeadEnd(start)) return -1;

    q.emplace(start);
    seen.insert(start);

    int dist{-1};
    while(!q.empty()) {
      int levelSize = q.size();
      ++dist;
      while(levelSize--) {
        auto comb = q.front();
        // for(auto v : comb) {
        //   cout << (int)v << '\n';
        // }
        // cout << '\n';
        q.pop();

        if(comb == targetInt) return dist;

        for(int i = 0; i < target.size(); ++i) {
          auto comb1 = comb;
          auto comb2 = comb;
          comb1[i] = (comb1[i] + 1) % 10;
          comb2[i] = (comb2[i] -1 + 10) % 10;
          if(!seen.count(comb1) && !isDeadEnd(comb1)) {
            q.push(comb1);
            seen.insert(comb1);
          }
          if(!seen.count(comb2) && !isDeadEnd(comb2)) {
            q.push(comb2);
            seen.insert(comb2);
          }
        }
      }
    }

    return -1;
  }
};
```

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
#### Move zeros
[arrays/moveZeros](../leetcode/arrays/moveZeros.hpp)
```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
      int pos{0};
      for(int i = 0; i < nums.size(); ++i) {
        if(nums[i]) {
          nums[pos++] = nums[i];
        }
      }
      while(pos < nums.size()) {
        nums[pos++] = 0;
      }
    }
};
```

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

#### BST
##### Find successor
[companies/Citadel/inorderSuccessorInBST](../leetcode/companies/Citadel/inorderSuccessorInBST.cpp)

### Fenwick tree (Binary Indexed Tree)
[Fenwick Tree or Binary Indexed Tree](../freeCodeCamp/DataStructures/BIT.cpp)  

### Trie
https://www.quora.com/What-is-the-best-open-source-C-implementation-of-a-trie


## Strings
### Main facts about characters
26 letters in english alphabet    
'a' - 97    
'A' - 65  
switching case for the given letter upper/lower is about toggling one bit in the char - 32 (2^5)  
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
