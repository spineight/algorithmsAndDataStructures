#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2::practice {
  template<typename Compare>
  //! sink function, for 0-indexed array
  void sink(vector<int> &a, size_t i) {
    Compare cmp;
    const size_t n = a.size();
    while(i*2+1<n) {
      size_t j = i;
      if(cmp(a[i*2+1],a[j]))
        j = i*2+1;
      if(i*2+2<n && cmp(a[i*2+2], a[j]))
        j = i*2+2;
      if(i == j) break;
      swap(a[i],a[j]);
      i = j;
    }
  }

  template<typename Compare>
  void heapify(vector<int> &a) {
    if(a.empty()) return;
    const size_t n = a.size();
    for(int i = (n-1)/2; i >= 0; --i) {
      sink<Compare>(a, i);
    }
  }
}