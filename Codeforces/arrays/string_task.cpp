//! https://codeforces.com/group/yg7WhsFsAp/contest/355490/problem/P07

#include <bits/stdc++.h>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  string s;
  cin >> s;
  unordered_set<char> vowels {'A', 'O', 'Y', 'E', 'U', 'I'};
  s.erase(remove_if(begin(s), end(s), [&vowels](char ch) {
    return vowels.count(ch & ~32) > 0;
  }), end(s));
  string res;
  for(auto ch : s) {
    res += '.';
    res += ch | 32;
  }
  cout << res << '\n';
  return 0;
}