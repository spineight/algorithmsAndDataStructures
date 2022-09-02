//! https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/A

#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(const string& s) {
  int n = s.size();
  int l{0}, r{n-1};
  while(l < r) {
    if(s[l] != s[r]) return false;
    ++l;
    --r;
  }
  return true;
}

//! wowwow
int longestPalindromePrefix(const string& s) {
  int best{0};
  for(int i = 1; i <= s.size(); ++i) {
    if(isPalindrome(s.substr(0,i))) best = i;
  }
  return best;
}

int main() {
//  vector<string> task = {"woweffect", // 3
//                         "abccbaabc", // 6
//                         "testme",  // 1
//                         "strstr",  //1
//                         "ababab", // 5
//                         "abcdefg", // 1
//                         "tetatet", // 7
//                         "aaaaaaaaaaaaa"}; // 13

//  for(const auto& t : task) cout << longestPalindromePrefix(t) << '\n';
  int t;
  cin >> t;
  while(t--) {
    string s;
    cin >> s;
    cout << longestPalindromePrefix(s) << '\n';
  }
  return 0;
}