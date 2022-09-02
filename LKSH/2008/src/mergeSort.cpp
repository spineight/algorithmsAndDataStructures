#include <bits/stdc++.h>
using namespace std;
void mergeSort(vector<int>& a, vector<int>& aux, int l, int r) {
  int m = l + (r - l) / 2;
  if(l < m) mergeSort(a, aux, l, m);
  if(m+1 < r) mergeSort(a, aux, m + 1, r);

  int i{l}, j{m+1};
  int k = l;
  while(k <= r) {
    while (i <= m && (j > r || a[i] <= a[j])) {
      aux[k] = a[i];
      ++k;
      ++i;
    }
    while (j <= r && (i > m || a[j] < a[i])) {
      aux[k] = a[j];
      ++k;
      ++j;
    }
  }
  copy(&aux[l], &aux[r+1], &a[l]);
}

void mergeSort(vector<int>& a) {
  if(a.size() > 1) {
    vector<int> aux(a.size());
    mergeSort(a, aux, 0, a.size() - 1);
  }
}

int numberOfInversions(vector<int>& a, vector<int>& aux, int l, int r) {
  int res{0};
  const int m = l + (r-l)/2;
  if(l<m) res += numberOfInversions(a,aux,l,m);
  if(m+1<r) res += numberOfInversions(a, aux, m+1,r);

  int i{l}, j{m+1};
  int k{l};
  while(i <= m && j <= r) {
    if(a[i] <= a[j]) {
      aux[k] = a[i];
      ++i;
    } else {
      res += m-i+1;
      aux[k] = a[j];
      ++j;
    }
    ++k;
  }
  while(i <= m) {
    aux[k] = a[i];
    ++k;
    ++i;
  }
  while(j <= r) {
    aux[k] = a[j];
    ++j;
    ++k;
  }
  copy(&aux[l], &aux[r+1], &a[l]);

  return res;
}
int numberOfInversions(const vector<int>& a) {
  if(a.size()<=1) return 0;

  vector<int> b{a}, aux{a};
  return numberOfInversions(b,aux, 0, a.size()-1);
}

int main() {
  cout << "merge sort\n";
  vector<int> a = {5,4,3,2,1};
  mergeSort(a);
  for(auto v : a) cout << v << ' ';
  cout << '\n';
  mt19937 engine(19937);
  uniform_int_distribution<int> dist(-100,100);
  int cnt = 10;
  while(cnt--) {
    vector<int> arr(10);
    generate(begin(arr), end(arr), [&](){return dist(engine);});
    cout << "before: ";
    for(auto v : arr) cout << v << ' ';
    cout << '\n';
    mergeSort(arr);
    cout << "after:";
    for(auto v : arr) cout << v << ' ';
    cout << '\n';
    cout << '\n';
    assert(is_sorted(begin(arr), end(arr)));

    cout << "merge sort. inversions counting\n";
    a={5,4,3,2,1}; // n * (n-1) / 2  = 10
    cout << numberOfInversions(a) << '\n'; // 10
  }
  return 0;
}