//! https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/C
#include <bits/stdc++.h>
using namespace std;

pair<int, vector<int>> solve(const string& p, const string& t) {
  if(p.size() > t.size()) return {0,{}};
  vector<int> positions;
  for(int i = 0; i < t.size()-p.size()+1; ++i) {
    int soFar{0};
    while(soFar < p.size() && (p[soFar] == t[i+soFar] || p[soFar] == '?')) ++soFar;
    if(soFar == p.size()) positions.push_back(i);
  }
  return {positions.size(), positions};
}

int main() {
//  vector<string> tasks = {
//          "abacaba",
//          "a?a",
//          "test",
//          "?????",
//          "abaabaaab",
//          "a??a",
//          "ok",
//          "?",
//          "test",
//          "me"
//  };
  int  t;
  cin >> t;
  vector<string> tasks(t*2);
  for(auto& t : tasks) cin >> t;
  for(int i = 0; i < tasks.size(); i+=2) {
    auto res = solve(tasks[i+1], tasks[i]);
    cout << res.first << '\n';
    for(auto v : res.second) cout << v << " ";
    cout << '\n';
  }
  return 0;
}