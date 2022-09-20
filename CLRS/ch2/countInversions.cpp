#include <bits/stdc++.h>
using namespace std;

int merge(vector<int>& a, int l, int m, int r) {
  const int n0 = m-l+1;
  const int n1 = r-m;
  vector<int> left(n0), right(n1);
  for(int i = 0; i < n0; ++i)
    left[i] = a[l+i];
  for(int i = 0; i < n1; ++i)
    right[i] = a[m+1+i];
  int i{0}, j{0}, p{l};
  int inversions{0};

  while(i < n0 && j < n1) {
    if(left[i] <= right[j]) {
      a[p] = left[i];
      ++i;
    } else {
      a[p] = right[j];
      ++j;
      ++inversions;
    }
    ++p;
  }
  while(i < n0) {
    a[p] = left[i];
    ++i;
    ++p;
    ++inversions;
  }
  while(j < n1) {
    a[p] = right[j];
    ++j;
    ++p;
  }
  return inversions;
}

int mergeSort(vector<int>&a, int l, int r) {
  if(l>=r) return 0;

  const int m = l + (r-l) / 2;
  int cnt{0};;
  cnt += mergeSort(a,l,m);
  cnt += mergeSort(a,m+1,r);

  cnt += merge(a,l,m,r);
  return cnt;
}

int mergeSort(vector<int>& a) {
  if(a.empty()) return 0;
  return mergeSort(a,0,a.size()-1);
}

int main() {
  vector<int> a = {2,3,8,6,1};
  cout << mergeSort(a); // expected 5 : 2,1; 3,1; 8,6; 8,1; 6,1
  assert(is_sorted(begin(a), end(a)));
  return 0;
}