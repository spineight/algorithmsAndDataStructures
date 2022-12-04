#include <bits/stdc++.h>
using namespace std;

/*
 * Algorithm idea:
 * On i-th step select the smallest element from i..n and swap it with i-th element
 */

/*
 * Algorithm design
 * We incrementally solve the problem
 */

/*
 * Proof of correctness
 * Invariant:
 * at i-th step i-1 elements are on their places in the sorted order
 * 1. Before the loop start
 *    0 elements are sorted
 * 2. After the loop iteration
 *    we found the smallest element from the remaining elements and put it on i-th position,
 * 3. After the loop finish
 *    n-1 elements are on their positions followed by the largest element - array is sorted
 */

/*
 * Algorithm analysis
 * Best Case O(n^2) - even if array sorted at ith step we still have to examine remaining n-i elements
 * to pick the smallest one from them
 * Worst Case O(n^2)
 */
void selectionSort(vector<int>& a) {
  const int n = a.size();

  for(int i = 0; i < n-1; ++i) {
    int minIdx = i;
    for(int j = i+1; j < n; ++j) {
      if(a[minIdx] > a[j])
        minIdx = j;
    }
    swap(a[minIdx], a[i]);
  }
}

void show(vector<int>& a) {
  for(auto v : a) cout << v << ' ';
  cout << '\n';
}

int main() {
  vector<int> a = {5,4,3,2,1};
  selectionSort(a);
  show(a);

  mt19937 engine;
  uniform_int_distribution<int> dist(-100,100);
  vector<int> a1(200);
  int nOfRuns(10000);
  while(nOfRuns--) {
    for (auto &v : a1) v = dist(engine);
//    show(a1);
    selectionSort(a1);
//    show(a1);
    assert(is_sorted(begin(a1), end(a1)));
    if( (nOfRuns % 100) == 0 ) cout << '#';
  }
}