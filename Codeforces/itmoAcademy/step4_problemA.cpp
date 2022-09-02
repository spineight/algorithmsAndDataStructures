//! https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/A

#include <bits/stdc++.h>
using namespace std;

vector<int> zFn( const string& s) {
  vector<int> z(s.size(),0);
  int l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r >= i) {
      z[i] = min(z[i-l], r-i+1);
    }
    while(i + z[i] < s.size() && s[z[i] + i] == s[z[i]]) ++z[i];

    if(r < i + z[i]-1) {
      l = i;
      r = i + z[i]-1;
    }
  }
  return z;
}


string solve(const string& s) {
  auto z = zFn(s);
  for(int i = 1; i < s.size(); ++i) {
    if(i+z[i] == s.size()) {
      return s.substr(0,i);
    }
  }
  return s;
}

int main() {
  int t;
  cin >> t;
  while(t--) {
    string s;
    cin >> s;
    cout << solve(s) << '\n';
  }
  return 0;
}