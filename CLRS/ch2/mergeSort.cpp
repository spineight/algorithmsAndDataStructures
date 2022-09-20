#include <bits/stdc++.h>
using namespace std;

/*
 * Algorithm idea:
 * Divide problem in half into 2 subproblems and solve each of them recursively
 * then combine their solutions
 *
 * It is called mergeSort - because all work is performed by the merge routine,
 * which merges 2 sorted subarrays into one
 */

/*
 * Algorithm design:
 * Divide and conquer idea
 */

/* Algorithm correctness.
    ?????
 */

/*
 * Algorithm analysis
  T(n) = 2T(n/2) + n

          n/2                 n/2
    n/4       n/4         n/4   n/4
  n/8 n/8   n/8 n/8     n/8 n/8   n/8 n/8
  ...

  height lg(n) + 1
  on every level we have n elements, on every level work done by merge is O(n)

  total work O( n*lg(n) )
 */

/*
 * Algorithms properties:
  recursion depth = lg(n) + 1, this can be proved by induction:
  base case n = 1, depth = lg(1) + 1 = 1
  n > 1
 */

void merge(vector<int>&a, int l, int m, int r) {
  const int n0 = m - l + 1;
  const int n1 = r - m;
  vector<int> left(n0), right(n1);
  for(int i = 0; i < n0; ++i)
    left[i] = a[l+i];
  for(int j = 0; j < n1; ++j)
    right[j] = a[m+1+j];
  int i{0}, j{0}, p{l};

  while (i < n0 && j < n1) {
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

//! [l,r]
void mergeSort(vector<int>&a, int l, int r) {
  if(l >= r) return; // base case - array of size 1 is sorted

  const int m = l + (r-l)/2;
  // recursive step: divide the problem into 2 half and conquer each separately
  mergeSort(a, l, m);
  mergeSort(a,m+1,r);

  // combine solutions to the subproblems
  merge(a, l,m,r);
}

void mergeSort(vector<int>& a) {
  if(a.size() > 0)
    mergeSort(a,0,a.size()-1);
}

void show(vector<int>& a) {
  for(auto v : a) cout << v << ' ';
  cout << '\n';
}

int main() {
  vector<int> a = {5,4,3,2,1};
  mergeSort(a);
  show(a);

  vector<int> a2 = {2,3,8,6,1};
  mergeSort(a2);
  show(a2);

  mt19937 engine;
  uniform_int_distribution<int> dist(-100,100);
  vector<int> a1(2000);
  int nOfRuns(10000);
  while(nOfRuns--) {
    for (auto &v : a1) v = dist(engine);
//    show(a1);
    mergeSort(a1);
//    show(a1);
    assert(is_sorted(begin(a1), end(a1)));
    if( (nOfRuns % 100) == 0 ) cout << '#';
  }
}