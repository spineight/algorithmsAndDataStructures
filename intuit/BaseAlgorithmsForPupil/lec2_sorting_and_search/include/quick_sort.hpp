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
