#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int>& a, int l, int r) {
  for(int i = l+1; i <= r; ++i) {
    int val = a[i];
    int j = i;
    while (j > l && a[j-1] > val) {
      a[j] = a[j - 1];
      --j;
    }
    a[j] = val;
  }
}

void merge(vector<int>& a, int l, int m, int r) {
  const int n0 = m-l+1;
  const int n1 = r-m;
  vector<int> left(n0), right(n1);
  for(int i = 0; i < n0; ++i)
    left[i] = a[l+i];
  for(int j = 0; j < n1; ++j)
    right[j] = a[m+1+j];

  int i{0}, j{0}, p{l};
  while(i < n0 && j < n1) {
    if(left[i] <= right[j]) {
      a[p] = left[i];
      ++i;
    } else {
      a[p] = right[j];
      ++j;
    }
    ++p;
  }
  while(i < n0) {
    a[p] = left[i];
    ++i;
    ++p;
  }
  while(j < n1) {
    a[p] = right[j];
    ++j;
    ++p;
  }
}

template<int k>
void mergeSort(vector<int>&a, int l, int r) {
  if(l >= r) return;
  if(r-l+1 <= k) {
    insertionSort(a,l,r);
  }

  const int m = l + (r-l) / 2;
  mergeSort<k>(a,l,m);;
  mergeSort<k>(a,m+1,r);

  merge(a,l,m,r);
}

template<int k>
void mergeSort(vector<int>& a) {
  if(!a.empty())
    mergeSort<k>(a,0,a.size()-1);
}

void show(vector<int>& a) {
  for(auto v : a) cout << v << ' ';
  cout << '\n';
}

int main() {
  vector<int> a = {5,4,3,2,1};
  show(a);
//  insertionSort(a,0,size(a)-1);
//  show(a);
  mergeSort<5>(a);
  show(a);

  vector<int> a2 = {2,3,8,6,1};
  show(a2);
  mergeSort<1>(a2);
  show(a2);

  mt19937 engine;
  uniform_int_distribution<int> dist(-100,100);
  vector<int> a1(2000);
  int nOfRuns(10000);
  while(nOfRuns--) {
    for (auto &v : a1) v = dist(engine);
//    show(a1);
    mergeSort<20>(a1);
//    show(a1);
    assert(is_sorted(begin(a1), end(a1)));
    if( (nOfRuns % 100) == 0 ) cout << '#';
  }
}