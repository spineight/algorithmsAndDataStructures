#pragma once
#include <bits/stdc++.h>
using namespace std;


namespace lec2::practice {

/** Find index of first element in the sorted array == x, if no such element
 *returns -1.
 *
 *  @param a - array sorted in nondescending order
 *  @param x - element for search
 *  Задача поиска элемента в массиве
 *   Для задачи поиска элемента в массиве мы в качестве функции A выбрали:
 *   A(a[m]) = [ a[m] >= x ]
 */
int findFirstStankevich(const vector<int> &a, int x) {
  assert(is_sorted(begin(a), end(a)) &&
         "array should be sorted (non decreasing order)");
  const int n = a.size();
  int L = -1, R = n;

  while(R-L > 1) {
    int m = L + (R-L)/2;
    if(a[m] < x) {
      L = m;
    }
    else {
      R = m;
    }
  }
  if(R < n) {
    if(a[R] == x) return R;
  }
  return -1;
}

/** Find index of last element in the sorted array < x, if no such element
 *returns -1.
 *
 *  @param a - array sorted in nondescending order
 *  @param x - element to compare with
 */
int binary_search_find_last_less(const vector<int> & a, int x) {
  // [L,R)
  const int n = a.size();
  int L = -1, R = n;
  while(R-L>1) {
    int m = L + (R-L)/2;
    if(a[m] < x)
      L = m;
    else
      R = m;
  }
  return L;
}

}