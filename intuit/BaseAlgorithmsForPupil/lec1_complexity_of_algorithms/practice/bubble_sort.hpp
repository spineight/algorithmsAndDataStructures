#pragma once

#include <bits/stdc++.h>
using namespace std;

namespace lec1::practice {

/**
*  Алгоритм сортировки как пример для анализа времени работы.
*
*/
  void bubble_sort(vector<int> &a) {
    // we do n - 1 iterations
    // after each iteration largest element from unsorted subarray will be on it's place
    for (size_t i = 0; i + 1 < std::size(a); ++i) {
      // iterate over elements of unsorted subarray
      for(size_t j = 0; i + 1 + j  < std::size(a); ++j) {
        if(a[j] > a[j+1]) {
          std::swap(a[j], a[j+1]);
        }
      }
    }
  }

/**
*  Алгоритм сортировки как пример для анализа времени работы.
*  Оптимизированный, но с той же сложностью работы что
*  @see bubble_sort
*/
  void bubble_sort_ver2(vector<int> &a) {
   bool is_sorted = false;
   for (size_t i = 0; i + 1 < std::size(a) && !is_sorted; ++i) {
      is_sorted = true;
      // optimization: subarray - early exit when subarray already sorted
      for(size_t j = 0; i + 1 + j  < std::size(a); ++j) {
        if(a[j] > a[j+1]) {
          std::swap(a[j], a[j+1]);
          is_sorted = false;
        }
      }
    }
  }
}
