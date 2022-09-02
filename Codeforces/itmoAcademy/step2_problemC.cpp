//! https://codeforces.com/edu/course/2/lesson/3/2/practice/contest/272261/problem/C
#include <bits/stdc++.h>
using namespace std;


//https://neerc.ifmo.ru/wiki/index.php?title=Z-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F
//! /home/oleg/github/algorithmsAndDataStructures/ITMO/wikiConspects/Zfunction.pdf

vector<int> zFunction(const string& s) {
  vector<int> z(s.size(),0);
  for(int i = 1; i < s.size(); ++i) {
    while(s[z[i]] == s[z[i] + i]) ++z[i];
  }
  return z;
}

string solve(const vector<int>& z) {
  if(z[0] != 0) return "!";

  string s(z.size(),' ');
  s.front() = 'a';
  char ch{'b'};

  int curPrefixLen{0};
  int j{0};
  for(int i = 1; i < z.size(); ++i) {
    if(z[i] == 0 && curPrefixLen == 0) {
      s[i] = ch++;
      if(ch == 'z' + 1) ch = 'A';
    }

    if(z[i] > curPrefixLen) {
      curPrefixLen = z[i];
      j = 0;
    }

    if(curPrefixLen > 0) {
      s[i] = s[j];
      ++j;
      --curPrefixLen;
    }
  }
  auto zCur = zFunction(s);
  if(zCur != z) return "!";

  return s;
}



int main() {
  int t;
  cin >> t;
  while(t--) {
    int n;
    cin >> n;
    vector<int> z(n);
    for(auto& v : z) cin >>v;
    cout << solve(z) << '\n';
  }
//  cout << solve({0,5,4,3,0,0}) << '\n';
  return 0;
}