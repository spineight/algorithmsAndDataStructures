//! https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/B
#include <bits/stdc++.h>
using namespace std;

vector<int> zFn(const string& s) {
  vector<int> z(s.size(),0);
  int l{0}, r{0};
  for(int i = 1;i < s.size(); ++i) {
    if(r >= i) z[i] = min(z[i-l], r-i+1);
    while(i+z[i] < s.size() && s[z[i] + i] == s[z[i]]) ++z[i];
    if(r < i+z[i]-1) {
      r = i+z[i]-1;
      l = i;
    }
  }
  return z;
}

//! aaaabc
//! aaabca
//  aaabca|$|aaaabc|aaaabc
int solve(const string& s, const string& t) {
  const string tss = t + '$' + s + s;
  auto z= zFn(tss);
  for(int i = t.size()+1; i < tss.size()-s.size(); ++i) {
    if(z[i] == s.size()) return i - t.size()-1;
  }
  return -1;
}

int main() {
  int t;
  cin >> t;
  while(t--) {
    string s,t;
    cin >> s >> t;
    cout << solve(s,t) << '\n';
  }
  return 0;
}