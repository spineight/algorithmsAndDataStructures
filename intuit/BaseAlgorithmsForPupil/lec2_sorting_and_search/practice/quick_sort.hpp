#pragma once

#include <bits/stdc++.h>
using namespace std;


namespace lec2::practice {

  void quick_sort(std::vector<int> &a, int l, int r) {
    static std::random_device rd;
    static std::mt19937 urng(rd());
    std::uniform_int_distribution<int> dist(l,r);
    int x = a[dist(urng)];
    int i = l;
    int j = r;
    while(i < j) {
      while(a[i] < x) ++i;
      while(a[j] > x) --j;
      if(i <= j) {
        swap(a[i],a[j]);
        ++i;
        --j;
      }
    }
    if(l < j)
      quick_sort(a,l,j);
    if(i < r)
      quick_sort(a,i,r);
  }
}
