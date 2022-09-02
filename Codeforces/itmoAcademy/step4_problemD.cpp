//! https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/D
#include <bits/stdc++.h>
using namespace std;


// aaab  3
// 0210
//
// abab  3
// 0020
//
// aaaa  4
// 0321
//
// aaabaaa 7
// 0210321
//
// abccba 6
// 000001
//
// abacdef
// abacdaf
//
//! https://www.cyberforum.ru/cpp-beginners/thread2882164.html
//! Fails on:
//! abccbaabc - returns 1, expected 6
int solveWrong(const string& s) {
  const int n = s.size();

  int l{0}, r{n-1};
  int soFar{0};
  while(l <= r) {
    if(s[l] == s[r]) {
      if(l == r) ++soFar;
      else soFar += 2;
      ++l;
    }
    else {
      soFar = 0;
      l = 0;
    }
    --r;
  }
  return soFar;
}

vector<int> zFn(const string& s) {
  vector<int> z(s.size(), 0);
  int l{0}, r{0};
  for(int i = 1 ; i < s.size(); ++i) {
    if(r >= i) z[i] = min(i+z[i-l], r-i+1);
    while(i+z[i] < s.size() && s[i+z[i]] == s[z[i]]) ++z[i];
    if(r < i + z[i]-1) {
      r = i + z[i]-1;
      l = i;
    }
  }
  return z;
}

// abacaba
// 0010301
//! Based on: https://www.cyberforum.ru/cpp-beginners/thread2882164.html
// abacaba$abacaba
//
// abacdef
// abacdef$fedcaba
//
//! Как я понял идея: если мы зеркально отобразим строку, то все вхождения паландромов не изменятся, а это значит
//! что они будут одинаковые в начальной и развернутой строке
int solve(const string& s) {
  string reversedS(s.rbegin(),s.rend());
  auto srs = s + '$' + reversedS;
  auto z = zFn(srs);
  return *max_element(begin(z),end(z));
}


int main() {
  string s;
  cin >> s;
  cout << solve(s) << '\n';
  return 0;
}