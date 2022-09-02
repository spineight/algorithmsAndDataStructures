//! https://codeforces.com/edu/course/2/lesson/3/2/practice/contest/272261/problem/B
#include <bits/stdc++.h>
using namespace std;

// ki = 2^i-1
// a k1 = 1
// aba k2 = 3
// abacaba k3 = 7
// abacabadabacaba k4 = 15
string generateGrayString(int k) {
  string res{"a"};

  char ch = 'b';

  for(int i = 2; i <= k; ++i) {
//    string tmp = res + ch + res;
    string tmp = res;
    tmp.push_back(ch);
    tmp += res;
    res = std::move(tmp);
    ++ch;
  }
  return res;
}

//! Timelimit exceeded
int solveSlow(int k, int j) {
  auto s = generateGrayString(k);
  vector<int> z(s.size(),0);
  for(int i = 1; i <= j; ++i) {
    while(i+z[i] < s.size() && s[z[i]] == s[i+z[i]]) ++z[i];
  }
  return z[j];
}

//! Idea is to precalculate max string as we know it in advance
int main() {
//  for(int i = 1; i <= 10; ++i)
//    cout << generateGrayString(i) << '\n';
//  const string maxGrayString = generateGrayString(26);

  const auto s = generateGrayString(26);

  int t;
  cin >> t;
  while(t--) {
    int k,j;
    cin >> k >> j;
    const int n = (1<<k)-1;
    int cnt{0};
    while(j > 0 && cnt + j < n && s[cnt] == s[cnt + j]) ++cnt;
    cout << cnt << '\n';
  }
  return 0;
}