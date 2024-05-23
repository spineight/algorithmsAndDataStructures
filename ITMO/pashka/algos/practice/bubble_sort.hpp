#pragma once

#include <bits/stdc++.h>
using namespace std;

namespace algos::practice {

/**
*  Алгоритм сортировки как пример для анализа времени работы.
*
*/
  void bubble_sort(vector<int> &a) {
    const int n = a.size();
    for(int i = 0; i < n - 1; ++i) {
      for(int j = 0; j + 1 < n; ++j) {
        if(a[j] > a[j+1])
          swap(a[j],a[j+1]);
      }
    }
  }

/**
*  Алгоритм сортировки как пример для анализа времени работы.
*  Оптимизированный, но с той же сложностью работы что
*  @see bubble_sort
*/
  void bubble_sort_ver2(vector<int> &a) {
    const int n = a.size();
    for(int i = 0; i < n - 1; ++i) {
      for(int j = 0; j+1 < n - i; ++j) {
        if(a[j] > a[j+1])
          swap(a[j],a[j+1]);
      }
    }
  }
}
