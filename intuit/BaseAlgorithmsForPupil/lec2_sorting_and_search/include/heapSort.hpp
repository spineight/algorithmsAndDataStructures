#pragma once
#include <bits/stdc++.h>
#include <include/heapify.hpp>
using namespace std;

namespace lec2 {
  template <typename Compare>
//! @param n - number of elements in the heap
//! @param i - idx of element to sink
//! aux for heap sort (as number of elements n decreases, number of elements in sorted array grows)
  void sink(vector<int> &a, size_t i, size_t n) {
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

/** Heap sort
 * inplace sort (на месте, без использования дополнительной памяти)
 * Идея - в начале массива куча, в конце отсортированный массив
 * Из кучи извлекаем элемент и добавляем его в конец кучи
 * (куча уменьшается, массив растет)
 * В конце куча - пустая, массив отсортирован
 */
  void heap_sort(vector<int> &a) {
    heapify<std::greater<> >(a);
    const int n = a.size();
    for (int i = 0; i < n; ++i) {
      int max = a.front();
      int tmp = a[n - 1 - i];
      a[n - 1 - i] = max;
      a.front() = tmp;
      sink<std::greater<> >(a, 0, n - i - 1);
    }
  }
}