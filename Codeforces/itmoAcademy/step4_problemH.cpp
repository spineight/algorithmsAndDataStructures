//! https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/H
#include <bits/stdc++.h>
using namespace std;

vector<size_t> zFn(const string& s) {
  vector<size_t> z(s.size(),0);
  size_t l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r >= i) z[i] = min(z[i-l], r-i+1);
    while(i+z[i] < s.size() && s[i+z[i]] == s[z[i]]) ++z[i];
    if(r < i + z[i]-1) {
      r = i + z[i]-1;
      l = i;
    }
  }
  return z;
}

//! I looked up (1) in https://github.com/ksaveljev/codeforces-edu/blob/main/Z-algorithm/step4/H.cpp
//! Important: I got WA, because used size_t, after changed to long long got AC
//! Looks like they are using 32 bit system, on which size_t is 32 bits which is not sufficient for this task
//! Похожая задача, но там нужно было подсчитать количество разных продстрок разбиралась в видео
long long solve(const string& s) {
  if(s.empty()) return 0;

  long long res{0};
  const int n = s.size();
  for(int i = n-1; i >= 0; --i) {
    const string suffix = s.substr(i);
    const auto z = zFn(suffix);
    const size_t maxSeenPrefixLen = *max_element(begin(z), end(z));
    for(size_t j = maxSeenPrefixLen+1; j <= suffix.size(); ++j) // (1)
      res += j;
  }
  return res;
}

int main() {
  string s;
  cin >> s;
  cout << solve(s) << '\n';
  return 0;
}