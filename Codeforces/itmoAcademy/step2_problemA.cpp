//! https://codeforces.com/edu/course/2/lesson/3/2/practice/contest/272261/problem/A
#include <bits/stdc++.h>
using namespace std;


vector<int> zFunctionNaive(const string& s) {
  vector<int> res(s.size());
  res[0] = 0;
  for(int i = 1; i < s.size(); ++i) {
    int cnt{0};
    while(i+cnt < s.size() && s[cnt] == s[i+cnt]) ++cnt;
    res[i] = cnt;
  }
  return res;
}

int main() {
  string s;
  cin >> s;
  auto z = zFunctionNaive(s);
  for(auto v : z) cout << v << " ";
  cout << '\n';
  return 0;
}