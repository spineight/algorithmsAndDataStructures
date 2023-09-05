#include <bits/stdc++.h>

using namespace std;

struct AllConstruct {

  vector<vector<string_view>> calculateImpl(string_view s, const vector<string>& words) {
    if(s.empty()) {
      return vector<vector<string_view>>(1);
    }
    if(auto it = memo.find(s); it != end(memo)) {
      return it->second;
    }

    vector<vector<string_view>> res;

    for(const auto& w : words) {
      if(s.size() >= w.size() && s.starts_with(w)) {
        auto subRes = calculateImpl(s.substr(w.size()), words);
        for(auto& sr : subRes) {
          sr.push_back(w);
        }
        copy(begin(subRes), end(subRes), back_inserter(res));
      }
    }
    memo[s] = res;
    return res;
  }
  map<string_view, vector<vector<string_view>>> memo;
  vector<vector<string_view>> calculate(string s, const vector<string>& words) {
    memo.clear();
    return calculateImpl(s,words);
  }
};

void testAllConstructRecur(string s, const vector<string>& words) {
  AllConstruct ac;
  auto res = ac.calculate(s,words);
  for(const auto& vec : res) {
    cout << "[";
    for(const auto& v : vec) {
      cout << v << ",";
    }
    cout << "]";
  }
  cout << '\n';
}

vector<vector<string>> allConstruct(string s, const vector<string>& words) {
  vector<vector<vector<string>>> dp(s.size()+1);
  dp[0] = vector<vector<string>>(1);
  for(int i = 1; i <= s.size(); ++i) {
    for(const auto& w : words) {
      if(i >= w.size() && s.substr(i-w.size()).starts_with(w) && !dp[i-w.size()].empty()) {
        auto prevRes = dp[i-w.size()];
        for(auto& v : prevRes) {
          v.push_back(w);
        }
        copy(begin(prevRes), end(prevRes), back_inserter(dp[i]));
      }
    }
  }
  return dp[s.size()];
}

void testAllConstructIter(string s, const vector<string>& words) {
  auto res = allConstruct(s,words);
  for(const auto& vec : res) {
    cout << "[";
    for(const auto& v : vec) {
      cout << v << ",";
    }
    cout << "]";
  }
  cout << '\n';
}

int main() {
//  testAllConstructRecur("abc", {"abc", "ab", "bc", "ac", "a", "b", "c"});
//  cout << '\n';
  testAllConstructIter("abc", {"abc", "ab", "bc", "ac", "a", "b", "c"});

}