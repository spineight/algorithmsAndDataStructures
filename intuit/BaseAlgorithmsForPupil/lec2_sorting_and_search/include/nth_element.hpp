#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2 {
  // Мы используем модифицированную версию быстрой сортировки для поиска n-ого порядкого элемента за O(n)

int kth(vector<int>& a, int l, int r, int k) {
  if(l==r) return a[l];

  const int pivot = a[r];

  int cl{l}, cr{r};
  while(cl <= cr) {
    while(a[cl] < pivot) ++cl;
    while(a[cr] > pivot) --cr;

    if(cl <= cr) {
      swap(a[cl], a[cr]);
      ++cl;
      --cr;
    }
  }

  if(l <= k && k <= cr) return kth(a,l,cr,k); // [l, cr] -> elements <= pivot (0)
  if(cl <= k && k <= r) return kth(a,cl,r,k); // [cl,r ] -> elements >= pivot (1)
  // if k is not within any of intervals (0) or (1) then k is on its place
  return a[k];
}

int kth(vector<int>& a, int k) {
  return kth(a,0,(int)a.size()-1,k);
}
  
}
