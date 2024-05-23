#include <bits/stdc++.h>

using namespace std;

//! [l,r)
//! Combine two sorted arrays
void combine(vector<int>& a, int l, int m, int r) {
  assert(is_sorted(begin(a)+l, begin(a)+m));
  assert(is_sorted(begin(a)+m, begin(a)+r));
  vector<int> tmp(r-l);
  int i = l;
  int j = m;
  int k{0};
  while(i < m && j < r) {
    if(a[i] < a[j]) {
      tmp[k++] = a[i++];
    } else {
      tmp[k++] = a[j++];
    }
  }
  // remainders
  while(i < m) tmp[k++] = a[i++];
  while(j < r) tmp[k++] = a[j++];

  copy(begin(tmp), end(tmp), begin(a) +l);
}

//! Полуинтервал: [l,r)
void mergeSortImpl(vector<int>& a, int l, int r) {
  if(r-l <= 1) return; // base
  const int m = l + (r-l) / 2;
  mergeSortImpl(a,l,m);
  mergeSortImpl(a,m,r);
  combine(a,l,m,r);
}

void mergeSort(vector<int>& a) {
  mergeSortImpl(a, 0, a.size());
}

int main() {
  const int n = 10'000;
  vector<int> a0(n);
  iota(begin(a0), end(a0), 0);
  mergeSort(a0);
  assert(is_sorted(begin(a0), end(a0)));

  vector<int> a1(n);
  iota(begin(a1), end(a1),0);
  reverse(begin(a1), end(a1));
  vector<int> a2(a1);
  sort(begin(a2), end(a2));
  mergeSort(a1);
  assert(a1 == a2);

  //! Random test
  random_device rd;
  mt19937 engine(rd());
  uniform_int_distribution<int> dist(0,n);
  vector<int> a3(n);
  generate(begin(a3), end(a3), [&](){return dist(engine);});
  vector<int> a4(a3);
  sort(begin(a3), end(a3));
  mergeSort(a4);
  assert(a4 == a3);

  //! all elements equal
  vector<int> a5 = {5,5,5,5,5,5};
  vector<int> a6(a5);
  mergeSort(a5);
  sort(begin(a6), end(a6));
  assert(a5 == a6);
  return 0;
}