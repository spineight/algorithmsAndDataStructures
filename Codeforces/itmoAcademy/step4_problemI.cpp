//! https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/I
#include <bits/stdc++.h>
using namespace std;

// abacabadabacaba
// baxayad
// k = 3
//
//  abacabadabacaba
//z 001030106010301

vector<int> zFn(const string& s) {
  vector<int> z(s.size(),0);
  int l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r>=i) z[i] = min(z[i-l], r-i+1);
    while(i+z[i] < s.size() && s[i+z[i]] == s[z[i]]) ++z[i];
    if(r < i + z[i] - 1) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}


//! Based on this: https://github.com/ksaveljev/codeforces-edu/blob/main/Z-algorithm/step4/I.cpp
//
// p = baxayad t = abacabadabacaba
// baxayad$abacabadabacaba
// 00000000020002000200020
//
// dayaxab$abacabadabacaba
// 00000000000000020000000
//
// Разбираемся почему мы разварачиваем p и t
// p = abcd t = uabzd
// abcd$uabzd - prefix match
// 0000002000 - pos i - p.size() - 1
// dcba$dzbau - suffix match
// 0000010000 - idx = pos i - p.size() - 1;  idx + (t.size()-idx-1)
vector<int> solve(const string& tc, const string& pc, int k) {
  string t(tc), p(pc);
  const int n = p.size()+1+t.size();
  const auto z = zFn(p+'$'+t);
  reverse(begin(p), end(p));
  reverse(begin(t), end(t));
  const auto zr = zFn(p+'$'+t);

  vector<int> pos;
  for(int i = p.size()+1; i <=  n - p.size(); ++i) {
    if(z[i] + k >= p.size()) pos.push_back(i-p.size());
    else if( z[i] + k + zr[n-i+1] >= p.size()) pos.push_back(i-p.size());
  }
  return pos;
}

using namespace std;
int main() {
  string t,p;
  int k;
  cin >> t >> p >> k;
  auto res = solve(t,p,k);
  cout << res.size() << '\n';
  for(auto r : res) cout << r << ' ';
  cout << '\n';
  return 0;
}