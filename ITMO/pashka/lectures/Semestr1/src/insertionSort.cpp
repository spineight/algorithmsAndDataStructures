#include <bits/stdc++.h>

using namespace std;

//! invariant:
//! |vvvvvv|x______|
//!         k
//! On k-th iteration (when we work with k-th element) first k elements are sorted
void insertionSort(vector<int>& a) {
  const int n = a.size();
  for(int i = 1; i < n; ++i) {
    int j = i;
    while(j > 0 && a[j] < a[j-1]) {
      swap(a[j], a[j-1]);
      --j;
    }
  }
}

int main() {
  //! O(n)
  vector<int> a0(10'000);
  iota(begin(a0), end(a0), 0);
  insertionSort(a0);
  assert(is_sorted(begin(a0), end(a0)));
  //! O(n^2)
  vector<int> a1(10'000);
  iota(begin(a1), end(a1),0);
  reverse(begin(a1), end(a1));
  vector<int> a2(a1);
  sort(begin(a2), end(a2));
  insertionSort(a1);
  assert(a1 == a2);

  //! Random test
  random_device rd;
  mt19937 engine(rd());
  uniform_int_distribution<int> dist(0,10'000);
  vector<int> a3(10'000);
  generate(begin(a3), end(a3), [&](){return dist(engine);});
  vector<int> a4(a3);
  sort(begin(a3), end(a3));
  insertionSort(a4);
  assert(a4 == a3);

  //! all elements equal
  vector<int> a5 = {5,5,5,5,5,5};
  vector<int> a6(a5);
  insertionSort(a5);
  sort(begin(a6), end(a6));
  assert(a5 == a6);
  return 0;
}