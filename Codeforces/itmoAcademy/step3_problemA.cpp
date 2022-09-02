//! https://codeforces.com/edu/course/2/lesson/3/3/practice/contest/272263/problem/A
#include <bits/stdc++.h>
using namespace std;

vector<int> solve(const string& s) {
  vector<int> z(s.size(),0);

  const int n = s.size();
  int l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r >= i) z[i] = min(z[i-l], r-i+1);
    while(z[i] + i < n && s[z[i]] == s[z[i]+i]) ++z[i];

    if(r < z[i] + i - 1) {
      l = i;
      r = z[i] + i - 1;
    }
  }

  return z;
}

int main() {
  string s;
  cin >> s;
  for (auto& v : solve(s)) cout << v << ' ';
  cout << '\n';
  return 0;
}