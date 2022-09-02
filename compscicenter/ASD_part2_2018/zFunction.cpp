#include <bits/stdc++.h>
using namespace std;

//! Find all match positions of p in t
//! Requires O(p.size()) memory in comparision to standard ZFunc implementation which requires O(p.size() + t.size())
//! I have implemented it, TODO: testing
vector<int> findUsingZfn(const string& p, const string& t) {
  vector<int> z(p.size(),0);
  string s = p + '$';
  int l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r >= i) z[i] = min(z[i-l], r-i+1);
    while(z[i] + i < s.size() && s[z[i]] == s[z[i]+i]) ++z[i];
    if(r < i + z[i] - 1) {
      r = i + z[i] - 1;
      l = i;
    }
  }

  //   0123
  //   aba$  l = 2 r = 2
  // z 0010
  //        0123456789ABCDE
  //        abacabadabacaba  i  l  r  zVal
  //                         0  0  2  3
  //                         1  0  2  0
  //                         2  0  2  1
  //                         3  0  2  0
  //                         4  4  6  3
  //                         5  4  6  0
  //                         6  4  6  1
  //                         7  4  6  0
  //                         8  8  10 3
  vector<int> pos;
  int zVal{0};
  l = 0;
  r = 0;
  for(int i = 0; i < t.size(); ++i) {
    zVal = 0;
    if(r >=i) zVal = min(z[i-l], r-i+1);
    while(i + zVal < t.size() && p[zVal] == t[zVal + i]) ++zVal;
    if(zVal == p.size()) pos.push_back(i);
    if(r < i + zVal - 1) {
      r = i + zVal - 1;
      l = i;
    }
  }
  return pos;
}

int main() {
  auto res = findUsingZfn("aba", "abacabadabacaba");
  for(auto r : res) cout << r << " "; // 0 4 8 12
  cout << '\n';
  return 0;
}