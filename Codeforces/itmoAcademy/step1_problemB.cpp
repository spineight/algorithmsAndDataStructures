//! https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/B

#include <bits/stdc++.h>
using namespace std;

bool isPrefix(const string& s, const string& t ) {
  int i = 0;
  while(i < s.size() && s[i] == t[i]) ++i;
  return i == s.size();
}

bool isSuffix(const string& s, const string& t ) {
  int i = 0;
  while(i < s.size() && s[i] == t[t.size() - s.size() + i]) ++i;
  return i == s.size();
}
int countSubstringsEqualPrefixOrSuffix(const string& s) {
  int cnt{0};
  for(int i = 0; i < s.size(); ++i) {
    for(int j = i; j < s.size(); ++j) {
      int length = j-i+1;
      if(isPrefix(s.substr(i, length), s)) {
        ++cnt;
        if(isSuffix(s.substr(i, length), s)) --cnt;
      } else if (isSuffix(s.substr(i, length), s)) ++cnt;
    }
  }
  return cnt;
}

int main() {
//  vector<string> task = {
//          "abacaba",
//          "aaaa",
//          "barbarmiakirkudu",
//          "abaabaababaab"
//  };
//  for(const auto& t : task) cout << countSubstringsEqualPrefixOrSuffix(t) << '\n';
  int t;
  cin >> t;
  while(t--) {
    string s;
    cin >> s;
    cout << countSubstringsEqualPrefixOrSuffix(s) << '\n';
  }
  return 0;
}