//! https://codeforces.com/group/yg7WhsFsAp/contest/355490/problem/P05

#include <bits/stdc++.h>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  string s;
  cin >> s;
  int l{0}, r{0};
  int maxCnt{0};
  while(r < s.size()) {
    while(r < s.size() && s[l] == s[r]) ++r;
    maxCnt = max(maxCnt, r-l);
    l = r;
  }
  if(maxCnt >= 7) cout << "YES\n";
  else cout << "NO\n";
  return 0;
}