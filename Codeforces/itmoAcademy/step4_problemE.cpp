//! https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/E
#include <bits/stdc++.h>
using namespace std;

// wpwdwpw -> wdwpwwp
// wdwpwpw
//
// codeforces
// forcesedoc
//
// forcesedoc$codeforces  -- forces

vector<int> zFn(const string& s) {
  vector<int> z(s.size(),0);
  int l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r >= i) z[i] = min(z[i-l], r-i+1);
    while(i + z[i] < s.size() && s[i+z[i]] == s[z[i]]) ++z[i];
    if(r < i + z[i] - 1) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

optional<int> solve(const string& s, const string& t) {
  if(s.size() != t.size()) return {};
  auto ts = t + '$' + s;
  const auto z = zFn(ts);
  for(int i = s.size()+1; i < ts.size(); ++i) {
    if(i + z[i] == ts.size()) {
      const unsigned long prefixLen = s.size() - z[i];
      if(prefixLen == 0) return 0;
      string_view prefixS{s.data(), prefixLen};
      string_view suffixT{t.data() + z[i], prefixLen};
      // check if reversed prefixS matches suffix t

      for(int j = 0; j < prefixLen; ++j) {
        if(prefixS[prefixLen - 1 - j] != suffixT[j]) return {};
      }
      return prefixS.size();
    }
  }
  return {};
}

int main() {
  string s,t;
  cin >> s >> t;
  auto res = solve(s, t);
  if(res.has_value()) {
    cout << "Yes\n";
    cout << res.value() << '\n';
  } else cout << "No\n";
  return 0;
}