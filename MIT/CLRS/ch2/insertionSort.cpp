#include <bits/stdc++.h>
using namespace std;


/*
 * Algorithm idea:
 * It is called insertion sort because we look at element at the end, find the leftmost element > current
 * and shift elements (starting from the found element) one position to the right
 */

/*
 * Algorithm design
 * We incrementally solve the problem
 */

/* Algorithm correctness.
 * Outer loop invariant - subarray of the first ith elements is sorted
 *  Proof of algorithm correctness using the loop invariant (resembles induction)
 *  1. Before the loop start - i == 1 - subarray consists only of 1 element and it is sorted
 *  2. At the end of each iteration we put one more element on its place and increase i
 *  3. At the outer loop end we have i = n   -> we have n elements sorted
 */

/*
 * Algorithm analysis
 * Worst case scenario array is ordered in reverse order for ex. 5 4 3 2 1
 * O(n^2)
 * Best case array is ordered
 * O(n)
 */

/*
 * Algorithms properties: number of exchanges we do = number of inversions
 * Number of inversions can be calculated using modified Merge Sort
 */

/*
 * Usage used as subroutine for sorting small subarrays in Merge sort (we might benefit from cache hits ?)
 */

void insertionSort(vector<int>& a) {
  const int n = a.size();
  for(int i = 1; i < n; ++i) {
    int j = i;
    const int val = a[i];
    while(j > 0 && a[j-1] > val) {
      a[j] = a[j-1];
      --j;
    }
    a[j] = val;
  }
}

void show(vector<int>& a) {
  for(auto v : a) cout << v << ' ';
  cout << '\n';
}

int main() {
  vector<int> a = {5,4,3,2,1};
  insertionSort(a);
  show(a);

  mt19937 engine;
  uniform_int_distribution<int> dist(-100,100);
  vector<int> a1(200);
  int nOfRuns(10000);
  while(nOfRuns--) {
    for (auto &v : a1) v = dist(engine);
//    show(a1);
    insertionSort(a1);
//    show(a1);
    assert(is_sorted(begin(a1), end(a1)));
    if( (nOfRuns % 100) == 0 ) cout << '#';
  }
}