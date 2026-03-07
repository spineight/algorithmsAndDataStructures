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
## pretty print variables
```c++
#define show_vars(args...) { \
  string names = #args; \
  replace(begin(names), end(names), ',' , ' ');\
  stringstream ss(names); \
  istream_iterator<string> it(ss);\
  _show_vars(it, args);\
}

void _show_vars(istream_iterator<string>& it) {
  cout << "!\n";
}

template<typename T, typename ... TArgs>
void _show_vars(istream_iterator<string>& it, const T& val, TArgs ... args) {
  cout << *it++ << ":" << val << '\n';
  _show_vars(it, args...);
}
```
## pen & paper

Helpful:
- invariant (a condition that is true within certain scope): loop invariant, function call invariant helps a lot  
  ex.: [leetcode/arrays/remove-duplicates-from-sorted-array](../leetcode/arrays/remove-duplicates-from-sorted-array.hpp)

- call stack representation  
- call frame representation  
- proof of corectness by dividing input on classes (cases) and showing that all of them were covered  

I spent a lot of time debugging this task:  
[leetcode/lists/flattenMultilevelDoublyLinkedList](../leetcode/lists/flattenMultilevelDoublyLinkedList.hpp)  

# Implementation approaches
## Simplify by avoiding code duplicate
Use pointers to store branch results on which algorithm will be performed  
see `leetcode: /twoPointers/intervalListIntersections.hpp`  
[leetcode/twoPointers/intervalListIntersections](../leetcode/twoPointers/intervalListIntersections.hpp)

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


```c++
int solution(int N) {
  int res{0};
  size_t i = 1;
  //! i*i might overflow, that is why size_t is needed
  while(i*i < (size_t)N) {
    if( (N % i) == 0) res += 2;
    ++i;
  }
  if(i*i == (size_t)N)
    ++res;
  return res;
}
```
[codility/primeAndCompositeNumbers/countFactors](../codility/primeAndCompositeNumbers/countFactors.cpp)

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
## Forgetting to check remaining elements
```c++
include <stack>
#include <unordered_map>
int solution(string &S) {
  stack<char> s;
  unordered_map<char, char> closedMatch {
          {'(', ')'},
          {'{', '}'},
          {'[', ']'} };
  for(auto ch : S) {
    if(ch == '(' || ch == '{' || ch == '[')
      s.push(ch);
    else {
      if(s.empty() || closedMatch[s.top()] != ch)
        return 0;
      s.pop();
    }
  }
  return s.empty(); //! NB!!!
}
```
[codility/stacks&Queues/brackets](../codility/stacks&Queues/brackets.cpp)


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
[leetcode/arrays/findAllNumbersDisappearedInAnArray](../leetcode/arrays/findAllNumbersDisappearedInAnArray.hpp)

## Sorting idxs of elements (if they are heavy) instead of elements
We are going to sort `vector<MyType> elements`  
We assign idxs to elements we are going to sort: 0,1,2,3,4,5,6,7
This vector of idxs we pass to sorting routine, which get`s information of comparision of elements for ex. from unordered_map by index
As a resulting vector we get a permutation of idxs: res,
where `res[i] = j, means at i-th position should be elements[j] element `
[leetcode/arrays/kClosestPointsToOrigin](../leetcode/arrays/kClosestPointsToOrigin.hpp)

# Algorithms
## Collection of implemented algos
[peltorator_ru/cp_book](../peltorator_ru/cp_book.pdf)  
https://github.com/Peltorator/peltorator-cp-book  

https://github.com/spineight/cp-algorithms  
## Complexity analysis
### types of measurements
ITMO. Pashka semester 1 АиСД S01E01. Алгоритмы. Оценка времени. Сортировка слиянием.
[ITMO/pashka/algos_2019_semester1](../ITMO/pashka/algos_2019_semester1/README.md)
RAM model
Asymptotic measure
`O(n) - worst, Omega(n) - best,Theta(n) -avg`
Good example of algo for analysis - insertion sort
[ITMO/pashka/lectures/Semestr1/src/insertionSort](../ITMO/pashka/lectures/Semestr1/src/insertionSort.cpp)
Insertion sort:
    `1 2 3 4 5 6 7` - best, `Omega(n)`
    ` 7 6 5 4 3 2 1` - worst, `O(n^2)`
### some examples
```c++
//!! O(n^2)
 for(int i = 0; i < n; ++i)
   for(int j = 0; j < n; ++j)
     
 //! O(n^2)
 for(int i = 0; i < n; ++i)
   for(int j = i+1; j < n; ++j)
     
 //! O(sqrt(n))
while(i*i < n)
  
//! O(logn)
for(int i = 0; i < n; i*=2)
```

### Analysis of recursive algos
on example of merge sort
[ITMO/pashka/lectures/Semestr1/src/mergeSort](../ITMO/pashka/lectures/Semestr1/src/mergeSort.cpp)
Visual proof by drawing recursion tree
Divide & Conquer method & Master theorem  - TODO
TODO: refresh/review properties of logarithms

## Proof of correctness
### Induction
### Copy paste method ???
I recall it was on Stepik on Olympiad programming

## sorting & search
### Нижняя оценка для сортировок основанных только на сравнениях
`Omega(nlogn)`
Хорошее доказательство:
[Введение в программирование 3. Сортировки. MergeSort, недетерминированный QuickSort](/run/media/oleg/Kotyamba2/FPMI/first_course_autmn2021/intro_to_programming_StepanovDI_1course_autum2021/Введение в программирование 3. Сортировки. MergeSort, недетерминированный QuickSort.mp4)

### stable sort
Stable sort guarantee that order of equal elements wrt to the comparison function stays the same
[MFTI_FPMI/Stepanov/autumn_2021/stableCountingSort](../MFTI_FPMI/Stepanov/autumn_2021/stableCountingSort.cpp)
Stable sorts are used as a helper routines for several algos: convexHull,
[intuit/baseAndAdvancedAlgsForPupil/lec2/radixSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/radixSort.cpp)
uses [MFTI_FPMI/Stepanov/autumn_2021/stableCountingSort](../MFTI_FPMI/Stepanov/autumn_2021/stableCountingSort.cpp)

### bubble sort
[bubble sort](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/bubble_sort.hpp)

### counting sort
[countingSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/countingSort.cpp)

Based on Сергей Копелиович lecture: `/run/media/oleg/TOSHIBA EXT/ITMO/BaseAndAdvancedAlgsForSchoolStudents/Lecture2_Sorting_Lists_ShortestPathsInGraphs.mp4`    
Important idea that if data elements associated with keys are expensive to copy we instead od copying them  
can return permutation, where `permutation[i] - idx of element in initial array at i-th position in the resulting array`  
Using permutation we can access elements data in sorted order without need for copy   

[Сортировка подсчетом] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item9.mp4`

### radix sort
[radixSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/radixSort.cpp)  
Based on Сергей Копелиович lecture: `/run/media/oleg/TOSHIBA EXT/ITMO/BaseAndAdvancedAlgsForSchoolStudents/Lecture2_Sorting_Lists_ShortestPathsInGraphs.mp4`  
uses [countingSort](../intuit/baseAndAdvancedAlgsForPupil/lec2/countingSort.cpp)   

### Quick sort
[quick_sort](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/quick_sort.hpp)  
Stankevich quick sort
```c++
#pragma once
#include <vector>
#include <utility>
#include <random>

// Partition (Рассечение)
//  given x
// i ищет элемент >= X
// j ищет элемент <= X
// ##### Start
// |                             |
//   i                          j
// ##### Running
// |           A          B      |  =========> A >= X and B <= X , then  swap(A,B)
//             i          j
// ##### Finish
// |    <=x     |  >=x           |
//              j i

// В худщем случае за O(n^2) - если рассекающий элемент все время первый
// Если в качестве рассекающего мы берем случайный элемент, то можно доказать,
// что
// всреднем время работы O(nlogn)
namespace lec2 {

void quick_sort(std::vector<int> &a, int l, int r) {
  int i = l, j = r;
  static std::random_device rd;
  static std::mt19937 urng(rd());
  std::uniform_int_distribution<int> dist(l, r);
  int x = a[dist(urng)];
  while (i <= j) {
    while (a[i] < x) // после окончания этого цикла, i указывает на элемент >= x
      ++i;
    while (a[j] > x) // после окончания этого чиклв, j указывает на элемент <= x
      --j;
    // Example when this check is important:
    // 7 2 2 3 3 :
    //  1) 7 2 2 3 3  x = 7
    //     i       j
    //  2) 3 2 2 3 7
    //       i   j
    //  3) 3 2 2 3 7
    //           j i
    if (i <= j) {
      std::swap(a[i], a[j]);
      ++i;
      --j;
    }
  }
  if (l < j)
    quick_sort(a, l, j); // at least 2 elements
  if (i < r)
    quick_sort(a, i, r); // at least 2 elements
}
}

```
[Stankevich lecture] `/run/media/oleg/TOSHIBA EXT/ITMO/BaseAlgsForSchoolStudents/lec2_sorting_and_search`  
[Pestov lecture LKSH b prime 2008] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item4.mp4`    
[Лекция 4. Сортировка подсчетом и применение встроенных сортировок](../shujkova/lectures/lec4.pdf)  

Пример некорректной реализации предложенной Пашей:
(Не будет работать, когда есть одинаковые элементы
Так как когда все элементы подмассива с которым мы работаем >= X, то у нас задача разбивается на два массива:
пустой и такой же, поэтом мы зацикливаемся
)
[ITMO/pashka/lectures/Semestr1/src/quickSort_incorrect](../ITMO/pashka/lectures/Semestr1/src/quickSort_incorrect.cpp)

TODO: реализовать дитерминированный quick sort (алгоритм Блюма Флойда Пратта Ривеста и Тарьяна)
Общая идея рассказана: "АиСД S01E03. Быстрая сортировка. К-я порядковая статистика"
[ITMO/pashka/algos_2019_semester1](../ITMO/pashka/algos_2019_semester1/README.md)

### heapsort
Stankevich heap sort
[heap_sort](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/heapSort.hpp)

### Merge sort
I wrote code based on the lecture: `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item7.mp4`  
[LKSH 2008 b` merge sort](LKSH/2008/src/mergeSort.cpp)
[Лекция 4. Сортировка подсчетом и применение встроенных сортировок](../shujkova/lectures/lec4.pdf)  

В этой лекции хорошая идея нерекурсивной реализации + я ее оптимизировал (`std::span`):
[Введение в программирование 3. Сортировки. MergeSort, недетерминированный QuickSort](/run/media/oleg/Kotyamba2/FPMI/first_course_autmn2021/intro_to_programming_StepanovDI_1course_autum2021/Введение в программирование 3. Сортировки. MergeSort, недетерминированный QuickSort.mp4)  
[MFTI_FPMI/Stepanov/autumn_2021/mergeSort](../MFTI_FPMI/Stepanov/autumn_2021/mergeSort.cpp)  

Моя оптимизация рекурсивной версии: использование вспомогательного массива для слияния, который передается как параметр функции
(нам не нужно каждый раз его создавать):
[MFTI_FPMI/Stepanov/autumn_2021/mergeSort](../MFTI_FPMI/Stepanov/autumn_2021/mergeSort.cpp)

#### Merge sort. Number of inversions
[Применение сортировки слиянием: количество инверсий.] `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item8.mp4`  
[Merge sort. Number of inversinos](../LKSH/2008/src/mergeSort.cpp)
Хорошо рассказано в лекции: 
[Введение в программирование 3. Сортировки. MergeSort, недетерминированный QuickSort](/run/media/oleg/Kotyamba2/FPMI/first_course_autmn2021/intro_to_programming_StepanovDI_1course_autum2021/Введение в программирование 3. Сортировки. MergeSort, недетерминированный QuickSort.mp4)
[MFTI_FPMI/Stepanov/autumn_2021/mergeSort](../MFTI_FPMI/Stepanov/autumn_2021/mergeSort.cpp)

### Binary search. Binary search by answer. Real numbers binary search.
Main source:
Based on Andrei Stankevich lecture:`/run/media/oleg/TOSHIBA EXT/ITMO/BaseAlgsForSchoolStudents/lec2_sorting_and_search`    
[binarySearch](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/binary_search.hpp)   
[binarySearch Pestov lecture LKSH b prime 2008] examples of binary search on an answer:  
 * `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item1.mp4`    
* `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item2.mp4`   
* `/run/media/oleg/TOSHIBA EXT/ITMO/LKSH_2008_b_prime/day1_item3.mp4`    


#### Rotated sorted array (different from Andrei Stankevich, all ends are included)
[leetcode/binary_search/searchInRotatedSortedArray](leetcode/binary_search/searchInRotatedSortedArray.hpp)     
[leetcode/arrays/findMinimumInRotatedSortedArray](leetcode/arrays/findMinimumInRotatedSortedArray.hpp)   

#### Combination of 2 binary searches / usage of std::equal_range
[leetcode/binary_search/findFirstAndLastPositionOfElementInSortedArray](../leetcode/binary_search/findFirstAndLastPositionOfElementInSortedArray.hpp)

#### Some problems with Binary search application
[leetcode/binary_search/TheKWeekestRowsInAMatrix](../leetcode/binary_search/TheKWeekestRowsInAMatrix.hpp)

### k-th element
This is my implementation based on Stankevich Quick sort implementation  
Modification of quick sort can be used to find n-th largest / smallest element in O(n)
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
### General ideas
With recursion we go depth first and once reach a base case start unwinding
### understanding
Great explanation at Stanford CS 106B (2008) by Julie Zelenski: `/run/media/oleg/TOSHIBA EXT/cs106b_2008_ProgrammingAbstractionsStanford`    
Every recursion problem can be mapped to one of the following types:
[permutation problem](../cs106b/permutations.cpp)    
[subset_problem](../cs106b/subset.cpp)  
[towers of Hanoi](../cs106b/moveTower.cpp)  

### progression of problems (by increasing difficulty) solved recursevly and iterativly 
[leetcode/data_structures/stack/valid-parentheses](../leetcode/data_structures/stack/valid-parentheses.hpp)

recursion progression problems (show different types and how to gradually transition from one type of a problem to another)
Exit earlier once there is a suitable combination without considering others
[freeCodeCamp/Recursion_and_DP/canSum](../freeCodeCamp/Recursion_and_DP/canSum.cpp)

[freeCodeCamp/Recursion_and_DP/howSum](../freeCodeCamp/Recursion_and_DP/howSum.cpp)

We need to consider all combinations to choose the best once
[freeCodeCamp/Recursion_and_DP/bestSum](../freeCodeCamp/Recursion_and_DP/bestSum.cpp)

[freeCodeCamp/Recursion_and_DP/canConstruct](../freeCodeCamp/Recursion_and_DP/canConstruct.cpp)
[freeCodeCamp/Recursion_and_DP/countConstruct](../freeCodeCamp/Recursion_and_DP/countConstruct.cpp)
[freeCodeCamp/Recursion_and_DP/allConstruct](../freeCodeCamp/Recursion_and_DP/allConstruct.cpp)

### memoization
[codility/sieveOfEratosthenes/countNonDivisible](../codility/sieveOfEratosthenes/countNonDivisible.cpp)

### Backtracking:  
[sudoku Solver](../cs106b/sudokuSolver.cpp)  
[queens8](../cs106b/queens8.cpp)
[leetcode/graphs/tree/pathSum2](../leetcode/graphs/tree/pathSum2.hpp)

### Tail recursion
Is mentioned as a solution to this problem: [leetcode/graphs/tree/maximumDepthOfBinaryTree](../leetcode/graphs/tree/maximumDepthOfBinaryTree.hpp)  
 the idea is explained here: [leetcode/graphs/tree/maximumDepthOfBinaryTree](../leetcode/graphs/tree/maximumDepthOfBinaryTree.odt)  

### Hard tasks
Shows recursion design: 
problem reduction, delegation of similar subproblem of smaller size, combining solution to subproblems.
It seemed hard to me to solve, as initially was hard to define subproblem and what to delegate
[leetcode/data_structures/stack/decodeString](../leetcode/data_structures/stack/decodeString.hpp)

## greedy
[leetcode/arrays/minimumNumberOfArrorsToBurstBaloons](../leetcode/arrays/minimumNumberOfArrorsToBurstBaloons.hpp)

# Динамическое программирование (DP)
## Стратегии
- Хорошая стратегия - составляем состояние и смотрим из каких состояний мы могли в него прийти
- При составлении состояния помогает следующее размышление: допустим я знаю решение для меньшей задачи,
как из него получить решение для следующей

## Схема решения и примеры классических задач
[Stankevich DP3 lecture](../intuit/BaseAlgorithmsForPupil/lec3_dynamic_programming/README.md)
lecture:`/run/media/oleg/TOSHIBA EXT/ITMO/BaseAlgsForSchoolStudents/lec3_dynamic_programming`
My reflection on the lecture and practice
For forward DP good idea for the current state to reason from which previous states we could come here

**1D**
- [grasshopper](../intuit/BaseAlgorithmsForPupil/lec3_dynamic_programming/include/grasshopper.hpp)
- [MFTI_FPMI/Stepanov/DP/grashopper](../MFTI_FPMI/Stepanov/spring_2023_advancedAlgs/DP/grashopper.cpp)
  Оптимизация по памяти (нам достаточно только две переменные, вместо массива)
  Примеры задач:
  https://leetcode.com/problems/jump-game/
  [jump_game](../leetcode/DP/jumpGame.hpp) - can be solved with 1D DP, but exists simplier and more efficient solution

### 2D
**Простой обход**
- [turtle](../intuit/BaseAlgorithmsForPupil/lec3_dynamic_programming/include/turtle.hpp)
- [MFTI_FPMI/Stepanov/DP/grasshopper2D][../MFTI_FPMI/Stepanov/spring_2023_advancedAlgs/DP/grasshopper2D.cpp]
  Оптимизация по памяти (достаточно только две строки, вместо матрицы)
- [unique_paths](../leetcode/DP/unique-paths.hpp)
- [unique_paths_omptimized](../leetcode/DP/unique_paths_optimized.hpp)
- [grid paths](../cses.fi/grid_paths.cpp)
  В некоторых клетках есть ловушки

**Храним информацию и последнем элементе подпоследовательности**
- [zoo_store](../intuit/BaseAlgorithmsForPupil/lec3_dynamic_programming/include/zoo_store.hpp)
- [array description](../cses.fi/array_description.cpp)

### Задача о рюкзаке
- [book shoop](../cses.fi/book_shop.cpp)

### Задачи о монетах
- [coin_combinations_I](../cses.fi/coin_combinations_I.cpp)
Посчитать число способов составить заданную сумму используя монеты заданного номинала,
число монет не ограничено, порядок монет имеет значение.
- [dice_combinations](../cses.fi/dice_combinations.cpp)
В этой задаче вместо монет разных номиналов выступает кубик, также посчитать число способов,
порядок имеет значение
- [coin_combinations_II](../cses.fi/coin_combinations_II.cpp)
Посчитать число способов составить заданную сумму используя монеты заданного номинала,
число монет не ограничено, порядок монет не имеет значение.
- [minimizing_coins](../cses.fi/minimizing_coins.cpp)
Найти минимально необходимое число монет для составления заданной суммы

TODO: Not clear to which type of dynamics these problems belong to
Max Common Subsequence Length. My idea with memory optimization (only 2 rows for DP)
[MFTI_FPMI/Stepanov/DP/maxCommonSubsequence](../MFTI_FPMI/Stepanov/spring_2023_advancedAlgs/DP/maxCommonSubsequence.cpp)

Find Max Common Subsequence. My idea: we don't need aux matrix for answ restoring, as all needed info we have in DP matrix
[MFTI_FPMI/Stepanov/DP/maxCommonSubsequence](../MFTI_FPMI/Stepanov/spring_2023_advancedAlgs/DP/maxCommonSubsequence.cpp)




TODO: practice problems
https://cses.fi/problemset/task/2413
https://informatics.msk.ru/course/view.php?id=9
https://codeforces.com/blog/entry/325

## Вариации одной задачи с увеличением сложности
Показан мыслительный процесс перехода рекурсия -> рекурсия + мемо -> Динамическое программирование
Но на практике, это не эффективный подход, так как на интервью на это уйдет слишком много времени
video lectures: `/run/media/oleg/TOSHIBA EXT/FreeCodeCamp/DynamicProgramming_LearntoSolveAlgorithmicProblems_26CodingChallenges.mp4)`  
Idea is to have in mind a graph of transitions when solving recursively, this helps to establish dependencies
and order in which subproblems are solved for iterative dp.
In the order of difficulty:  
[gridTraveller](../freeCodeCamp/DP/gridTraveller.cpp) - according to Stankevich lecture on DP (this can be solved using combinatorics formula)
https://leetcode.com/problems/unique-paths/description/

freeCodeCamp - проблема в том, что я не на все примеры нашел задачи на платформах,
чтобы проверить решение (нужно написать тесты + случайные тесты)

[canSum](../freeCodeCamp/Recursion_and_DP/canSum.cpp)  
[canSumTest](../freeCodeCamp/Recursion_and_DP/canSum_test.cpp)

Using parent array to reconstruct the answer
[howSum](../freeCodeCamp/Recursion_and_DP/howSum.cpp)
[howSumTest](../freeCodeCamp/Recursion_and_DP/howSum_test.cpp)

[Dice Combinations](../cses.fi/dice_combinations.cpp)
[coin_combinations_I](../cses.fi/coin_combinations_I.cpp)

[Minimizing Coins](../cses.fi/minimizing_coins.cpp)

[bestSum](../freeCodeCamp/Recursion_and_DP/bestSum.cpp)  
Can be tested with [Minimizing Coins](../cses.fi/minimizing_coins.cpp)




[canConstruct](../freeCodeCamp/Recursion_and_DP/canConstruct.cpp)    
[countConstruct](../freeCodeCamp/Recursion_and_DP/countConstruct.cpp)  

[allConstruct](../freeCodeCamp/Recursion_and_DP/allConstruct.cpp)  

## Coins
Идея - решая разные вариации одной задачи про монеты понять основные моменты в реализации ДП:
- порядок обхода
- пересчет состояний
- [coin_combinations_I](../cses.fi/coin_combinations_I.cpp)
- [coin_combinations_II](../cses.fi/coin_combinations_II.cpp)
- [Minimizing Coins](../cses.fi/minimizing_coins.cpp)
- [Removing digits](../cses.fi/removing_digits.cpp)
My greedy solution seems to work here but I am struggling to proof it,
and don't get the [chatGPT explanation](../chatGPT/greedySolution.md)
Мне кажется для доказательства жадного решения нужно показать, что чем меньше число - тем меньше шагов нужно
для его обнуления.
I solved it using DP as well.
- [grid paths](../cses.fi/grid_paths.cpp)
- [book shoop](../cses.fi/book_shop.cpp)
knapsack: given the weights (prices) and values (pages) of items, maximize the profit within a capacity(amount) constraint.

## Динамика по подотрезкам
- Задача про сжатие строки
https://acm.timus.ru/problem.aspx?space=1&num=1238
Объяснение которой я пока не понял

- задача (Дубы):
Объяснения от yeputons
https://habr.com/ru/articles/112386/
По этой ссылке можно скачать текст задачи и тесты
https://neerc.ifmo.ru/school/archive/2007-2008.html#practice


## informatics
https://informatics.msk.ru/course/view.php?id=9

## CodeForces
https://codeforces.com/blog/entry/67679
https://codeforces.com/blog/entry/80064


### states storage
For some problems we don't need to store all the states,  
for ex. for these problems:  
[leetcode/DP/Fibonacci](../leetcode/DP/Fibonacci.hpp)  
[leetcode/DP/Tribonacci](../leetcode/DP/Tribonacci.hpp)  
[leetcode/DP/climbingStairs](../leetcode/DP/climbingStairs.hpp)  
[leetcode/DP/minCostClimbingStairs](../leetcode/DP/minCostClimbingStairs.hpp)  
[leetcode/DP/house_robber](../leetcode/DP/house_robber.hpp)  
for the current state estimation we need only to now a few previous states, so there is no need in an array to store all states

### Динамика по подотрезкам
28.10.2024
Пока не понимаю как такие задачи решаются.
Возьмусь за них после более простых


## Two pointers
[pashka/algos/include/two_pointers_method](../ITMO/pashka/algos/include/two_pointers_method.hpp)  
[pashka/README](../ITMO/pashka/README.md)  

### leet code
[lengthOfLongestSubstringWithoutRepeatingCharacters](../leetcode/twoPointers/lengthOfLongestSubstringWithoutRepeatingCharacters.hpp)
[leetcode/twoPointers/trappingRainWater](../leetcode/twoPointers/trappingRainWater.hpp)

### common tasks
 
[twoPointers/longestSubstringWithoutRepeatingCharacters](../leetcode/twoPointers/longestSubstringWithoutRepeatingCharacters.hpp)

longest-substring-without-repeating-characters
```c++
//! 
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

    int l{0};
    for(int r = 0; i < s.size(); ++r) {
      ++freq[s[r]];
      while(freq[s[r]] > 1 ) {
        --freq[s[l]];
        ++l;
      }
      best = max(best, r-l+1);
    }

    return best;
  }
};
```

## Combinatorics
### Combinations
[Skiena_programmingChallenges_book/combinations](../Skiena_programmingChallenges_book/combinations.cpp)
[leetcode/combinatorics/combinations](../leetcode/combinatorics/combinations.hpp)
### Permutations
https://en.wikipedia.org/wiki/Permutation#Algorithms_to_generate_permutations
https://stackoverflow.com/questions/11483060/stdnext-permutation-implementation-explanation

### Letter combinations of a phone number
[leetcode/combinatorics/letter-combinations-of-a-phone-number](../leetcode/combinatorics/letter-combinations-of-a-phone-number.hpp)

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
[leetcode/DFS_BFS/rottingOranges](../leetcode/DFS_BFS/rottingOranges.hpp)

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
## arrays
### processing
Make sure that you handle unprocessed array`s suffix after iteration is done:
[leetcode/strings/string-compression](leetcode/strings/string-compression.hpp)
### shift (rotate an array)
[leetcode/arrays/rotateArray](../leetcode/arrays/rotateArray.hpp)  
[leetcode/arrays/performStringShifts](../leetcode/arrays/performStringShifts.hpp)

### remove duplicates
[leetcode/arrays/removeDuplicatesFromSortedArray2](../leetcode/arrays/removeDuplicatesFromSortedArray2.hpp)
[leetcode/arrays/remove-duplicates-from-sorted-array](../leetcode/arrays/remove-duplicates-from-sorted-array.hpp)

### remove element
[leetcode/arrays/removeElement](../leetcode/arrays/removeElement.hpp)

### search in rotated-sorted array
Crutial to solution understand in which part of array you are located at the moment
2 cases: 
 - array is sorted - use binary search
 - greater part | smaller part
[leetcode/binary_search/searchInRotatedSortedArra](../leetcode/binary_search/searchInRotatedSortedArray.hpp)

### k-sums
#### 2sum
[leetcode/arrays/2sum](../leetcode/arrays/2sum.hpp)
#### 2sum array is sorted
Idea with 2 pointers
[leetcode/arrays/2sumII_input_array_is_sorted](../leetcode/arrays/2sumII_input_array_is_sorted.hpp)
#### 3sum
[leetcode/arrays/3sum](../leetcode/arrays/3sum.hpp)
#### 4sum
[leetcode/arrays/4sum](../leetcode/arrays/4sum.hpp)
#### ksum
[leetcode/arrays/ksum](../leetcode/arrays/ksum.odt)
[leetcode/arrays/ksum](../leetcode/arrays/4sum.hpp)


### matrix
#### Spiral traversal (idea with an array of offsets for moves)
[leetcode/arrays/spiralMatrix](../leetcode/arrays/spiralMatrix.hpp)  
[leetcode/arrays/spiralMatrix2](../leetcode/arrays/spiralMatrix2.hpp)

### boyer-moore voting algorithm
https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_majority_vote_algorithm  


### Kadane's algorithm (max subarray)
https://en.wikipedia.org/wiki/Maximum_subarray_problem  
https://www.interviewbit.com/blog/maximum-subarray-sum/  
[leetcode/buySellStock/bestTimeToBuySellStock](../leetcode/buySellStock/bestTimeToBuySellStock.hpp)  
[codility/maximumSlice/maxSliceSum](../codility/maximumSlice/maxSliceSum.cpp)  
###  Bidirectional Kadane's algorithm
[codility/maximumSlice/maxDoubleSliceSum](../codility/maximumSlice/maxDoubleSliceSum.cpp)   

### prefix sum
[codility/prefixSum/passingCars](../codility/prefixSum/passingCars.cpp)  
[codility/prefixSum/genomicRangeQuery](../codility/prefixSum/genomicRangeQuery.cpp)
[codility/maximumSlice/maxDoubleSliceSum](../codility/maximumSlice/maxDoubleSliceSum.cpp)
[codility/primeAndCompositeNumbers](../codility/primeAndCompositeNumbers/peaks.cpp)

#### Theory
Две реализации prefixSum:
1. На полуинтервалах(`[0,r)`):  `b[i]` - сумма первых `i` элементов,
   здесь нам нужен доп массив `b` размера `n+1` где мы суммируем значения из массива `a`
   `b[0]=0; b[i+1] = b[i] + a[i]`
2. На отрезках(`[0,r]`): `a[i]` - сумма i+1 первых элементов,
   доп массив не нужен, мы можем хранить в `a`, так как
   `a[0]` - первый элемент исходного массива
   `a[i] = a[i-1] + a[i]`

https://codeforces.com/edu/course/3/lesson/10
##### Step 1
[Codeforces/edu/prefixSum/step1_Префиксные_суммы_и_разностные_массивы_Codeforces](../Codeforces/edu/prefixSum/step1_Префиксные_суммы_и_разностные_массивы_Codeforces.pdf)
/run/media/oleg/Kotyamba2/codeforces/edu/prefixSumsStep1.mp4
https://codeforces.com/edu/course/3/lesson/10/1/practice
/home/oleg/github/algorithmsAndDataStructures/Codeforces/edu/prefixSum/step1_a_prefixSum.cpp

##### Step 2
[Codeforces/edu/prefixSum/step2_Префиксные_суммы_и_разностные_массивы_Codeforces](../Codeforces/edu/prefixSum/step2_Префиксные_суммы_и_разностные_массивы_Codeforces.pdf)
/run/media/oleg/Kotyamba2/codeforces/edu/prefixSumsStep2.mp4
https://codeforces.com/edu/course/3/lesson/10/2/practice


Sometimes you don't have to store prefixSum explicitly:  
[leetcode/arrays/maximumSizeSubarraySumEqualsK](../leetcode/arrays/maximumSizeSubarraySumEqualsK.hpp)

### Sliding window
[leetcode/arrays/minimumSwapsToGroupAllOnceTogether](../leetcode/arrays/minimumSwapsToGroupAllOnceTogether.hpp)

### Move zeros
[arrays/moveZeros](../leetcode/arrays/moveZeros.hpp)

### in array of duplicate elements and only one distinct find distinct element
[codility/oddOccurienciesInArray](../codility/arrays/oddOccurienciesInArray.cpp)

### in an array all elements are from 1..n, one element is missing, find it
[codility/timeComplexity/permMissingElem](../codility/timeComplexity/permMissingElem.cpp)  

### Leader
[codility/leader/6-Leader](../codility/leader/6-Leader.pdf)
[codility/leader/dominator](../codility/leader/dominator.cpp)

## Binary Heap
[Heap](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/heap.hpp)
Heap by Stankevich
```c++
#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2 {

/** Куча / Пирамида
 * https://neerc.ifmo.ru/wiki/index.php?title=%D0%94%D0%B2%D0%BE%D0%B8%D1%87%D0%BD%D0%B0%D1%8F_%D0%BA%D1%83%D1%87%D0%B0
 * 1. Почти полное двоичное дерево (последний ряд заполнен не доконца,
*заполнение
* слева на право) - на i-ом слое 2^i вершин, кроме последнего (слои нумеруются с
*нуля)
 * 2. у которого в узлах хранятся ключи такие что ключ родителя <=
* ключа его детей (если куча на минимум)
 *
 *
* Двоичное дерево - каждый узел имеет не более 2-х детей
* Лист - узел без детей
 * Высота - расстояние от корня до самого далекого листа
 *
 * Так как она почти полное двоичное дерево, ее можно упаковать в массив
 *
 *                    3(1)
 *               4(2)                     5(3)
 *       7(4)           8(5)       10(6)       15(7)
 *    9(8)   10(9)   20(10)
 *
 *    left_child_idx = 2 * parent_idx
 *    right_child_idx = 2 * parent_idx + 1
 *    parent_idx = child / 2
 *    Условие кучи: a[i/2] <= a[i]
 */
//! Корень имеет индекс 1

//! [28/08/2023][0]
//! Вычисления детей и предка с таким индексом проще
//! Можно брать и с корнем с индексом 0, но тогда:
//! parent(i) = (i-1) / 2
//! leftChild(i) = 2*i+1
//! rightChild(i) = 2*i+2

template<size_t SZ>
struct MinHeapStankevich {
  // Просеивание вверх ( всплывание)

  int a[SZ+1]; // +1 as array starts from 1
  int n{0};
  void insert(int val) {
    ++n;
    a[n] = val;
    siftUp(n);
  }
  //! Просеивание вверх (всплывание) Swim
  //! @param i - какой элемент нужно просеить
  void siftUp(int i) {
    while (i > 1 && a[i / 2] > a[i]) {
      swap(a[i / 2], a[i]);
      i = i / 2;
    }
  }
  int peek_min() const { return a[1]; }

  //! Просееивание вниз (утапливание) Sink
  void siftDown(int i) {
    while (2 * i <= n) { // левый ребенок имеет индекс 2*i, пока он есть можно топить
      int j = i; // Поиск минимума из 3-х, в j хранится индекс минимума из 3-х: i, 2*i,
                 // 2*i + 1
      if (a[2 * i] < a[i])
        j = 2 * i;
      if (2 * i + 1 <= n && a[2 * i + 1] < a[j])
        j = 2 * i + 1;
      if (j == i)
        break;
      swap(a[i], a[j]);
      i = j;
    }
  }
  int extract_min() {
    int res = a[1];
    swap(a[1], a[n]);
    --n;
    siftDown(1);
    return res;
  }
  bool empty() const {
    return 0 == n;
  }
};
}
```
Based on Stankevich`s Heap + some C++ techniques + DecreaseKey
[MFTI_FPMI/Stepanov/autumn_2021/binary_heap](../MFTI_FPMI/Stepanov/autumn_2021/binary_heap.cpp)

Theory:
[](../informatics_mccme/heap/bin_heap_ig-091022.pdf)

Возможны несколько вариантов реализации в зависимости от индексации в массиве
0-idx:
В лекции Pashka "АиСД S01E02. Структуры данных. Куча. Сортировка кучей"
[ITMO/pashka/algos_2019_semester1](../ITMO/pashka/algos_2019_semester1/README.md)
Implementation on 0-idx array + as global functions on array
(siftUp, siftDown, Heapify O(n), HeapSort)
[](../ITMO/pashka/lectures/Semestr1/src/binaryHeap.cpp)

Задачи:
https://informatics.msk.ru/mod/statements/view.php?id=3205#1

https://informatics.msk.ru/mod/statements/view.php?id=1234#1
Задачи с этого листочка:
(informatics_mccme/heap/bin_heap_ig-091022.pdf)[../informatics_mccme/heap/bin_heap_ig-091022.pdf]
[informatics_mccme/heap/heap_tasks](../informatics_mccme/heap/heap_tasks.cpp)

Важные моменты при реализации (выявлены при решении задач):
1. При удалении последнего элемента из кучи не нужно делать swap + siftDown
2. При удалении элемента по индексу (похоже на изменение элемента по индексу, мы заменяем удаляемый элемент на последний,
если значение последнего больше/меньше - мы понимаем, что вызывать siftUp/Down)
Пример (удаление `[3]` и замена его на 5, здесь для восстановления требуется всплытие вверх):
```c++
/*
          9
      /        \
     4          8
    /  \       /    \
   [3]  2      7     6
 / \   / \     /\   / \
1  0  1   0   6  5  5  5
  */
```
### Сортировка кучей
В лекции Pashka "АиСД S01E02. Структуры данных. Куча. Сортировка кучей"
[ITMO/pashka/algos_2019_semester1](../ITMO/pashka/algos_2019_semester1/README.md)
Наблюдение как делать сортировку без использования доп памяти:
Заметим, что когда мы убираем элемент из кучи, освобождается место в конце массива:
`|vvvvvvvvvv| |`
Поэтому мы хотели бы из кучи элемент добавлять в конец, тогда там должен быть max элемент,
поэтому мы строим кучу на максимум

### Build in linear time
[heapify](../intuit/BaseAlgorithmsForPupil/lec2_sorting_and_search/include/heapify.hpp)
Heapify - to get linear time go from the end (leaves are ignored, as they can't sink further) and sink
Так же рассуждения, почему выгодно делать просеивание вниз (так как на нижних уровнях у нас больше элементов),
чтобы минимизировать кол-во операций и оценка в лекции Pashka АиСД 2019 семестр 1
АиСД S01E02. Структуры данных. Куча. Сортировка кучей
[ITMO/pashka/algos_2019_semester1](../ITMO/pashka/algos_2019_semester1/README.md)
```c++
#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2 {
/** Создание кучи
 *
 * @param a
 * Два варианта
 * 1. Идем с начала и каждый элемент просеиваем вверх (swim) - n log n
 * 2. Идем с конца и каждый элемент просеиваем вниз (sink) - n
 *
 * https://neerc.ifmo.ru/wiki/index.php?title=%D0%94%D0%B2%D0%BE%D0%B8%D1%87%D0%BD%D0%B0%D1%8F_%D0%BA%D1%83%D1%87%D0%B0
 *
 * Доказательство 2. - O(n)
 * Число вершин на высоте h в куче из n элементов не превосходит  ceil(n / 2^h)
 * Высота кучи не превосходит log(n)
 * Обозначим за H высоту дерева, тогда время построения не превосходит:
 *  n = 16
 *                                                               h
 *                        1                                      4
 *                2                       3                      3
 *         4          5              6          7                2
 *    8      9   10    11       12     13    14    15            1
 *                                                               0
 *  На высоте 1 - число вершин == числу листьев, что есть n / 2
 *  На высоте 2 - число вершин в 2 раза меньше чем на высоте 1
 *  На высоте K+1 число вершин в 2 раза меньше чем на высоте k
 *
 *  Тогда время построения не превосходит:
 * SUM{h=1...H}(n/2^h * 2*h) = n*2 * SUM{h=1...H}(h/2^h)
 * Пояснение n/2^h - число вершин на данном уровне, для каждой из вершин мы вызываем sink, что займет h
 * Докажем вспомогательную лемму о сумме ряда:
 * SUM{h=1...INF}(h/2^h) = 2
 * Обозначим за S сумму ряда, заметим, что :
 *  n    =  1  *  n-1     +   1
 *  2^n     2     2^{n-1}     2^n
 *
 * SUM{n=1...INF}(1/2^n) - сумма бесконечной убывающей геометрической прогрессии
 * и она равна:  (1/2) /(1 - 1/2) = 1
 *  Получаем S = 1 /2 * S + 1 / 1 => S = 2 / (2-1)^2
 *
 *  Подставляем в нашу формулу результат лемммы:
 *  n*2 * 2 <= 4n = O(n)
 */
  template<typename Compare>
  void sink(vector<int> &a, size_t i) {
    const size_t n = a.size();
    Compare cmp;
    // sink function, for 0-indexed array:
    while (2 * i + 1 < n) { // left child exist
      size_t j = i;            // find min of 3
      if (cmp(a[i * 2 + 1], a[i]))
        j = 2 * i + 1;
      if (2 * i + 2 < n && cmp(a[2 * i + 2], a[j]))
        j = 2 * i + 2;
      if (j == i)
        break;
      swap(a[i], a[j]);
      i = j;
    }
  }

  template<typename Compare>
  void heapify(vector<int> &a) {
    const int n = a.size();
    // Делаем sink для вершин имеющих хотябы одного потомка, так как поддеревья состоящие из одной вершины без
    // потомков, уже упорядочены
    for (int k = (n - 1) / 2; k >= 0; --k) { // last n/2 elements - are leafs
      sink<Compare>(a, k);
    }
  }

  //! [28/08/2023]
  //! Идея: даже для вектора с индексацией от нуля, можно применить heapify с индексацией от 1
  //! Разница будет только во время доступа к элементам массива
  //! В каждом из таких доступов по индексу, нужно этот индекс уменьшать на единицу
  namespace once_based {
    template<typename Compare>
    void sink(vector<int>& a, int i) {
      Compare cmp;
      const size_t n{a.size()};
      while(i*2 <= n) {
        int minIdx = i;
        if(cmp(a[i*2-1], a[i-1])) minIdx = i*2;
        if(i*2+1 <= n && cmp(a[i*2], a[minIdx-1])) minIdx = i*2+1;
        if(minIdx == i) break;
        swap(a[minIdx-1], a[i-1]);
        i = minIdx;
      }
    }

    template<typename Compare>
    void heapify(vector<int> &a) {
      for(int i = a.size(); i >= 1; --i)
        sink<Compare>(a,i);
    }
  }

}
```

### Stack
#### Implementation
based on array / linked list
[basedOnArray](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/StackArrayBased.hpp)
[basedOnLinkedList](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/StackLinkedListBased.hpp)
[MultiStackMemoryMgmt](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/MultiStackMemoryMgmt.hpp)

[codility/stacks&Queues/fish](../codility/stacks&Queues/fish.cpp)
#### Brackets validation
[right_brackets_multiple_types](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/right_brackets_multiple_types.hpp)
[right_brackets_one_type](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/right_brackets_one_type.hpp)

for multiple types - we use stack:  
[codility/stacks&Queues/brackets](../codility/stacks&Queues/brackets.cpp)  
[leetcode/data_structures/stack/valid-parentheses](../leetcode/data_structures/stack/valid-parentheses.hpp)

if there is only one type of brackets - simple counter (balance) is sufficient:    
[codility/stacks&Queues/nesting](../codility/stacks&Queues/nesting.cpp)    

#### tasks
[codility/stacks&Queues/fish](../codility/stacks&Queues/fish.cpp)  
[codility/stacks&Queues/stoneWall](../codility/stacks&Queues/stoneWall.cpp)

#### Monotonic stack
[data_structures/stack/dailyTemperatures](../leetcode/data_structures/stack/dailyTemperatures.hpp)

### Queue
[Queue](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/my_queue.hpp)
#### 

### Dequeue

### linked list
#### static linked lists (based on arrays)
[StaticSingleLinkedList](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/StaticSingleLinkedList.hpp)
[StaticDoubleLinkedList](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/StaticDoubleLinkedList.hpp)
[StaticMultiLists](../intuit/BaseAlgorithmsForPupil/lec1_complexity_of_algorithms/include/StaticMultiLists.hpp)

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

[graphs/tree/serializeAndDeserializeBinaryTree](../leetcode/graphs/tree/serializeAndDeserializeBinaryTree.hpp)  

"It turns out that if we include # or any other character for the null node while serializing, then we can uniquely identify a tree, that too with only one traversal (either preorder or postorder)":
https://leetcode.com/problems/subtree-of-another-tree/?envType=company&envId=ebay&favoriteSlug=ebay-thirty-days

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

#### tree hashing
https://leetcode.com/problems/subtree-of-another-tree/?envType=company&envId=ebay&favoriteSlug=ebay-thirty-days

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


### Segment tree
https://cp-algorithms.com/data_structures/segment_tree.html

#### Baseic types that can be used as a core for problem solving
[Codeforces/edu/segmentTree/segmentTreeMin](../Codeforces/edu/segmentTree/segmentTreeMin.cpp)   
[Codeforces/edu/segmentTree/segmentTreeSum](../Codeforces/edu/segmentTree/segmentTreeSum.cpp)  
[Codeforces/edu/segmentTree/segmentTreeMinCount](../Codeforces/edu/segmentTree/segmentTreeMinCount.cpp)  
[Codeforces/edu/segmentTree/segmentTreeMaxSegmentSum](../Codeforces/edu/segmentTree/segmentTreeMaxSegmentSum.cpp)  
[Codeforces/edu/segmentTree/segmentTreeKthOne](../Codeforces/edu/segmentTree/segmentTreeKthOne.cpp)  
[Codeforces/edu/segmentTree/segmentTreeFirstAbove](../Codeforces/edu/segmentTree/segmentTreeFirstAbove.cpp)  

#### Application of basic types to problem solving
##### Find inversions for the given permutation
Use SegmentTreeSum of zeros and once, go from left to right in `arr` and mark values of visited elements,
when you are at i-th position you have information in the segment tree by counting number of onces from `arr[i]` to `maxElem`
this will be the number of elements seen previously whith value > `arr[i]`  
[Codeforces/edu/segmentTree/segmentTreeAndInversions](../Codeforces/edu/segmentTree/segmentTreeAndInversions.cpp)

##### By given inversions restore the permutation
Use SegmentTreeSum + getKthEleme  
You visit the `arr` from right to left, `arr[i] = v` - number of remaining elements greater then it, so element has to be at `n-v` position  
after you figured out i-th element you remove it from the remaining by using the Segment tree operation`set(i,0)`  
[Codeforces/edu/segmentTree/usingSegmentTreeToRestorePermutationByInversions](../Codeforces/edu/segmentTree/usingSegmentTreeToRestorePermutationByInversions.cpp)  

##### Count number of nested segments
nested segment - segment which start and end is contained within another segment  
example: x y y x -> y is nested within x segment  
for each segment x, we need to find number of nested segments  
Idea:  use SegmentTreeSum with 0,1 elements and unordered_map  
lets visit the `arr` from left to right and store the position of left border of segments that have started already (using unordered_map)  
once we encounter the right boarder of a segment we use SegmentTree `set(posOfLeftBoarder,1)` and for the closed segment we estimate  
number of nested segments by `getSum(posOfLeftBoarder, posOfRightBoarder)`  
[Codeforces/edu/segmentTree/usingSegmentTreeForNestedSegments](../Codeforces/edu/segmentTree/usingSegmentTreeForNestedSegments.cpp)  

##### Count number of intersecting segments
Similar idea as in `Count number of nested segments`  
[Codeforces/edu/segmentTree/usingSegmentTreeForIntersectingSegments](../Codeforces/edu/segmentTree/usingSegmentTreeForIntersectingSegments.cpp)  

##### Addition of a number to a segment

[Codeforces/edu/segmentTree/usingSegmentTreeForAdditionToSegment](../Codeforces/edu/segmentTree/usingSegmentTreeForAdditionToSegment.cpp)

great lectures from Pavel Mavrin (Pashka):
`/run/media/oleg/TOSHIBA EXT/codeforces/segmentTree`

##### signAlternation
[Codeforces/edu/segmentTree/signAlternation.cpp](../Codeforces/edu/segmentTree/signAlternation.cpp)  
##### cryptography
[Codeforces/edu/segmentTree/cryptography](../Codeforces/edu/segmentTree/cryptography.cpp)
##### numberOfInversionsOnSegment
[Codeforces/edu/segmentTree/numberOfInversionsOnSegment](../Codeforces/edu/segmentTree/numberOfInversionsOnSegment.cpp)

## linked lists
### Find element in linked list in O(1), keep elements sorted
[leetcode/lists/design-a-leaderboard](../leetcode/lists/design-a-leaderboard.hpp)

## deque
This solution might be not optimal, due to removal from deuque might be expensive (size of batch???) 
[leetcode/data_structures/deque/design-most-recently-used-queue](../leetcode/data_structures/deque/design-most-recently-used-queue.hpp)
TODO: one more time look how deque is implemented wrt to removal and O(1) access by idx
For me looks like: when removing an element we must shift all elements from the batch
(the same complexity as remove element from vector)

## Strings
### Main facts about characters
26 letters in english alphabet    
'a' - 97    
'A' - 65  
switching case for the given letter upper/lower is about toggling one bit in the char - 32 (2^5)  
### Main definitions
[main definitions]`/run/media/oleg/TOSHIBA EXT/codeforces/itmoAcademy/stringsMainDefinitions.mp4`

### cpp
string_view usage example, remove redundant whitespaces, reverse words in a string:
[reverse-words-in-a-string](../leetcode/strings/reverse-words-in-a-string.hpp)

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

### Longest palindromic substring
#### Manacher's_algorithm O(n)
[e-maxx code](../e-maxx/strings/manaker.cpp)
[e-maxx pdf](../e-maxx/strings/Нахождение_всех_подпалиндромов.pdf)
[longestPalindromicSubstring](../leetcode/strings/longestPalindromicSubstring.hpp)



I googled( list requires refinement )
https://habr.com/ru/articles/653617/

### Pattern matching
#### Using DP
[leetcode/strings/wildcardMatching](../leetcode/strings/wildcardMatching.hpp)

## RMQ (Range Minimum/ Maximum Query)
### Sparse Table
#### Problems for practice
https://informatics.msk.ru/mod/statements/view.php?id=32990&chapterid=1663#1  
https://codeforces.com/blog/entry/70418
[SPOJ/RMQ/RMQSQ](../SPOJ/RMQ/RMQSQ.cpp)  
[SPOJ/RMQ/CatapultThatBall](../SPOJ/RMQ/CatapultThatBall.cpp)

Passes only with rewritten min function (so the for loop can be vectorized)
Plus the array is allocated only once
[SPOJ/RMQ/NegativeScore](../SPOJ/RMQ/NegativeScore.cpp)

### Disjoint Sparse Table
https://www.youtube.com/@peltorator
https://codeforces.com/blog/entry/87940
https://youtu.be/NbAtm1j5gVA?si=4jyJnMJWfcoeJX5H



#### Implementation:
https://codeforces.com/blog/entry/101083
#### Optimizations:
В лекции Степанова `Введение в программирование 7. Амортизационный анализ метод монет, потенциалов. Sparse table`
предлагается идея с предподсчетом logn,
но у него реализация с ошибкой (не проверяется выход за пределы массива),
в этом блоге Слотина, говорится, что встроенный `__lg()` работает быстрее, чем вариант с предподсчетом:
https://codeforces.com/blog/entry/75611

### O(1)
TODO
https://codeforces.com/blog/entry/78931

## Graphs

### Trees
#### Trees characters
##### Diameter
[MFTI_FPMI/Stepanov/spring_2023_advancedAlgs/Lec13_Trees_Centroids_LCA/practice/treeDiameter](../MFTI_FPMI/Stepanov/spring_2023_advancedAlgs/Lec13_Trees_Centroids_LCA/practice/treeDiameter.cpp)
##### Center
##### Centroid

#### Isomorphism
##### For rooted trees
Особенность решения из лекции МФТИ - это то, что они не считают hash для массива детей вершины,
а хранят его так std::map.
[MFTI_FPMI/Stepanov/spring_2023_advancedAlgs/Lec13_Trees_Centroids_LCA/practice/treeIsomorphism](/../MFTI_FPMI/Stepanov/spring_2023_advancedAlgs/Lec13_Trees_Centroids_LCA/practice/treeIsomorphism.cpp)

Возможные варианты оптимизации рассматривает Сергея Копелиович в сборнике
«Зимняя школа по программированию 2013», страница 264
/home/oleg/github/algorithmsAndDataStructures/WinterSchool/lectures/WPS2013.pdf
Так же см видео на диске Kotyamba, там он про это рассказывает
(По состоянию на 09/12/2023 - мне показалось сложным для понимания)

##### For non rooted
Solved via rooted by rooting at centroid/ center

#### LCA

**Linked lists intersection approach when parent info is available**
https://leetcode.com/problems/intersection-of-two-linked-lists/editorial/
[lowest-common-ancestor-of-a-binary-tree-iii](../leetcode/graphs/tree/lowest-common-ancestor-of-a-binary-tree-iii.cpp)

**On Binary Search Tree**
The idea is if nodes are in different subtrees of the root - root is LCA.
Otherwise they are in the same subtree, determine whether to go to the left or right subtree,
this is done by examining the value of leftmost node from p,q.
The LCA is found when p,q are in different subtrees.
[lowestCommonAncestorOfBinarySearchTree](../leetcode/graphs/tree/lowestCommonAncestorOfBinarySearchTree.hpp)

**On Binary Tree**
TODO: (failed to implement and looked up the solution)
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/submissions/1437516464/

##### Решение через бинарные подъемы (предпроцессинг O(n*logn), ответ на запрос O(n))
Идея:
Запустить DFS из корня дерева:
    - записать время входа и выхода для ответа на запрос `isAncestor(u,v)` за `O(1)`
    - Заполнить табличку `ancestor[k][u]` через динамическое программирование
      где `ancestor[k][u]` - `2^k` предок вершины `u`
      База `ancestor[0][u] = parent[u]`
      Переход: `ancestor[k][u] = ancestor[k-1][ancestor[k-1][u]]`
Заполнения таблички для одного узла - `log(n)`, так как их всего `n` то предпроцессинг за `O(nlogn)`

Для ответа на запрос `lca(u,v)`:
Проверка, что одна из вершин не является родителем другой.
Далее ищем самый дальнюю вершину от `u` которая не является предком вершины `v`
Для этого используем технику двоичных подъемов (пробуем максимальное, на каждом шаге прыжок сокращаем в два раза)  
Что-то похоже на запись числа в виде суммы степеней двойки (в двоичной системе)

Код я реализовал по описанию: (e-maxx/graphs/LCA/LCA_binaryLifts)[../e-maxx/graphs/LCA/LCA_binaryLifts.pdf]   
Хорошее объяснение, по которому все понятно в лекции MFTI_FPMI/Stepanov/spring_2023_advancedAlgs
[Алгоритмы и структуры данных 13. Центры и центроиды.mp4](..%2F..%2F..%2F..%2F..%2Frun%2Fmedia%2Foleg%2FKotyamba2%2FFPMI%2Ffirst_course_spring_2023%2FAlgsDataStructures_StepanovID_1course_spring2023%2F%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D1%8B%20%D0%B8%20%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B%20%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D1%85%2013.%20%D0%A6%D0%B5%D0%BD%D1%82%D1%80%D1%8B%20%D0%B8%20%D1%86%D0%B5%D0%BD%D1%82%D1%80%D0%BE%D0%B8%D0%B4%D1%8B.mp4)

Задачи для практики:
https://kuvaev.me/%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B8/lca/

//! https://informatics.msk.ru/mod/statements/view.php?id=26138#1
//! https://www.eolymp.com/ru/problems/2318

[e-maxx/graphs/LCA/LCA](../e-maxx/graphs/LCA/LCA.cpp)

Применение LCA
https://algocode.ru/files/course_bp2021/contest-25749-ru.pdf

## Probobalistic data structures
### skip list (Слоёные списки)
https://github.com/spineight/Skiplist-CPP
[skip_list](../leetcode/data_structures/skip_list/README.md)
http://algolist.ru/ds/s_skl.php
http://algolist.ru/ds/skiplist.c
https://github.com/wangshusen/AdvancedAlgorithms
https://youtu.be/4ux-jzg9lkE?si=wJCG-V5gNk_1JJHg

@TODO search for "Skip list language:C++" on github a lot of interesting repos
https://github.com/DKU-StarLab/SkipList-Research
https://github.com/youngyangyang04/Skiplist-CPP/blob/master/skiplist.h
https://github.com/Naplesoul/LSM-KV
https://github.com/LongyuYang/Concurrent-Lock-free-Skip-List


## Cache
https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU

# Implementation techniques
## using array of offsets for a matrix exploration
TODO include here leetcode problems that I solved using this technique:
arrays/spiralMatrix.hpp    
and one of for DFS/BFS: DFS_BFS/maxAreaOfIsland.hpp  

## using arrays to store initially given separate but related values
[leetcode/tricks/designParkingSystem](../leetcode/tricks/designParkingSystem.hpp)

## Using recursion to implement k loops
When number of nested loops is not known in compile time use recursion
for example in this algo for ksum:
(leetcode/arrays/ksum)[../leetcode/arrays/4sum.hpp]

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

### count non divisors
[codility/sieveOfEratosthenes/countNonDivisible](../codility/sieveOfEratosthenes/countNonDivisible.cpp)

### find divisors
`/run/media/oleg/TOSHIBA EXT/ITMO/pashka/Паша_и_алгосы/Быстрое_нахождение_делителей_пилотный_выпуск.mp4`
Как искать делители числа, а также как раскладывать его на простые множители
0:00 - small n, naive approach
0:59 - n is big (n <= 10^10)
1:10 - трюк (ищем числа <= sqrt(n)
2:05 - проблема делители выводятся не в порядке возрастания
2:10 - решение добавить в вектор и отсортировать
3:01 - объединение двух циклов в один
3:20 - разложение на простые множетели
3:30 - факт: если A min делитель числа n - то A обязательно простое
3:50 - алгоритм разложения на простые множители
```text
n = p1 * p2 * p3 * ... * pk
p1 - min делитель числа n, тогда p2 * p3 * ... * pk - разложение n / p1
```
4:50 - задача разложения числа на простые множители, но с большими ограничениями (n<=10^10)
Перебираем делители не больше `sqrt(n)`, если есть простой делитель который больше корня из n, то он может быть только 1
Выведем его в конце
5:50 - пример задачи (задача про бобра и камни)
## factorization

## Euclidean algorithm (gcd)
[codility/euclideanAlgorithm/chocolatesByNumbers](../codility/euclideanAlgorithm/chocolatesByNumbers.cpp)

## Modulo operations
[codility/fibonacciNumbers/ladders](../codility/fibonacciNumbers/ladders.cpp)

# Long arithmetics
[leetcode/strings/addStrings](../leetcode/strings/addStrings.hpp)  
[leetcode/strings/multiplyString](../leetcode/strings/multiplyStrings.hpp)  