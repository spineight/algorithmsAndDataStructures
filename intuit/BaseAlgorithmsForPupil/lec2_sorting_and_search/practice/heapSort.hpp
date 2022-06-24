#pragma once
#include <bits/stdc++.h>
#include <include/heapify.hpp>
using namespace std;

namespace lec2::practice {
  template <typename Compare>
  void sink(vector<int> &a, size_t i, size_t heapSize) {
    Compare cmp;
    while(i*2+1<heapSize) {
      size_t j = i;
      if(cmp(a[2*i+1],a[j]))
        j=2*i+1;
      if(i*2+2<heapSize && cmp(a[i*2+2],a[j]))
        j=2*i+2;
      if(i == j) break;
      swap(a[i],a[j]);
      i = j;
    }
  }

  void heap_sort(vector<int> &a) {
    heapify<greater<>>(a);
    const int n = a.size();
    for(int i = 0; i < n; ++i) {
      int max = a.front();
      int tmp = a[n - 1 - i];
      a[n - 1 - i] = max;
      a.front() = tmp;
      sink<std::greater<> >(a, 0, n - i - 1);
    }
  }
}