#pragma once

#include <bits/stdc++.h>
using namespace std;

namespace lec1::practice {

/**
*  Алгоритм сортировки как пример для анализа времени работы.
*
*/
  void bubble_sort(vector<int> &a) {
    for(size_t i = 0; i < size(a); ++i) {
      for(size_t j = 0; j < size(a) - 1; ++j) {
        if(a[j] >a[j+1]) swap(a[j],a[j+1]);
      }
    }
  }

/**
*  Алгоритм сортировки как пример для анализа времени работы.
*  Оптимизированный, но с той же сложностью работы что
*  @see bubble_sort
*/
  void bubble_sort_ver2(vector<int> &a) {
    for(size_t i = 0; i < size(a); ++i) {
      bool isSorted{true};
      for(size_t j = 0; j < size(a) - 1; ++j) {
        if(a[j] >a[j+1]) {
          swap(a[j],a[j+1]);
          isSorted = false;
        }
      }
      if(isSorted) break;
    }
  }
}
