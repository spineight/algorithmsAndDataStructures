#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2::practice {

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