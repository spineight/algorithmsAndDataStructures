#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2::practice {

template<size_t sz>
  struct MinHeapStankevich {
  int a[sz+1];
  int n{0};
  MinHeapStankevich() {}

  void insert(int v) {
    ++n;
    a[n] = v;
    swim(n);
  }

  void swim(int i) {
    while(i > 1 && a[i/2] > a[i]) {
      swap(a[i/2], a[i]);
      i /= 2;
    }
  }
  void sink(int i) {
    while(2*i <= n) {
      int minIdx = i;
      if(a[2*i] < a[i]) minIdx = 2*i;
      if(2*i+1 <=n && a[2*i+1] < a[minIdx]) minIdx = 2*i+1;
      if(minIdx == i) break;
      swap(a[i], a[minIdx]);
      i = minIdx;
    }
  }

  int peek_min() const { return a[1];}


  int extract_min() {
    int res = a[1];
    swap(a[1], a[n]);
    --n;
    sink(1);
    return res;
  }
  bool empty() const {
    return 0 == n;
  }
};

}