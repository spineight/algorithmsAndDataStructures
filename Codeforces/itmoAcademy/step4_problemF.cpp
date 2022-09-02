//! https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/F
#include <bits/stdc++.h>
using namespace std;

vector<int> zFn(const string& s) {
  vector<int> z(s.size(),0);
  int l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r >= i) z[i] = min(z[i-l], r-i+1);
    while(i + z[i] < s.size() && s[i+z[i]] == s[z[i]]) ++z[i];
    if(r < i + z[i]-1) {
      r = i + z[i]-1;
      l = i;
    }
  }
  return z;
}

// 2.
// abacaba
// ababa
//
// aba|caba
// ab|aba
// ab|abacaba
//
// itmo
// university
//
// 1.
// for
// codeforces
//
// Какие возможны варианты:
// 1. Одна строка содержит в себе другую
// 2. строки пересекаются:   sssss
//                              ttttt
//
//                           sssss
//                        ttttt
//
// abcdef
// defghik
// expected: abcdefghik
string solve(string& s, string& t) {
  // для удобства более длинную строку будем хранить в s
  if(t.size() > s.size()) s.swap(t);
  auto ts = t+'$'+s;
  auto zTS = zFn(ts);

  //
  int prefixTlen{0};
  for(int i = t.size()+1; i < ts.size(); ++i) {
    // более длинная строка s содержит в себе короткую строку t
    if(zTS[i] == t.size()) return s;
    // 2.
    // ababa$abacaba
    // ищем суффикс строки s совпадающий с префиксом строки t
    if(i + zTS[i] == ts.size()) prefixTlen = max(prefixTlen,zTS[i]);
  }

  auto st = s+'$'+t;
  auto zST = zFn(st);
  int prefixSlen{0};
  for(int i = s.size()+1; i < st.size(); ++i) {
    // ищем суффикс строки t совпадающий с префиксом строки s
    if(i + zST[i] == st.size()) prefixSlen = max(prefixSlen,zST[i]);
  }
  if(prefixSlen == 0 && prefixTlen == 0) return s+t;

  // VVV
  // abacaba  s
  // ababa    t
  //   VVV
//  cout << t.substr(0,t.size()-prefixSlen) << ", " << s.substr(prefixSlen) << '\n';
//  cout << s.substr(0,s.size()-prefixTlen) << ", " <<  t.substr(prefixTlen) << '\n';
  if(prefixSlen > prefixTlen) return t.substr(0,t.size()-prefixSlen) + s.substr(0, prefixSlen) + s.substr(prefixSlen);
  else return s.substr(0,s.size()-prefixTlen) + t.substr(0,prefixTlen)+ t.substr(prefixTlen);

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