#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec7 {
  // raise to power iterative formulation
  int raise(int base, int exp) {
    int result = 1;
    for(int i = 1; i <= exp; ++i)
      result *= base;
    return result;
  }

  int raiseRecur(int base, int exp) {
    if(exp == 0) return 1;
    return base * raiseRecur(base, exp-1);
  }

  int raiseRecurEfficient(int base, int exp) {
    if(exp == 0) return 1;

    int res = raiseRecurEfficient(base, exp/2);
    if(exp & 1) return res * res * base;
    return res * res;
  }

  bool isPalindrome(string s) {
    if(s.size() <= 1) return true;

    return s.front() == s.back() && isPalindrome(s.substr(1, s.size()-2));
  }

  int BSearch(const vector<int> a, int l, int r, int val) {
    if(l > r) return -1;

    const int m = l + (r-l) / 2;
    if(val == a[m]) return m;
    if(val < a[m]) return BSearch(a,l,m-1,val);
    else return BSearch(a,m+1,r,val);
  }

  //! choosing a subset C(n,k)
  int C(int n, int k) {
    if(k == 0 || k == n) return 1;
    return C(n-1,k) + C(n-1,k-1);
  }

}