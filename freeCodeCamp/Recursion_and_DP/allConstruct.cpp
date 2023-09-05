#include <bits/stdc++.h>
using namespace std;

//! Write a function allConstruct(target, wordBank) that accepts a target string
//! and an array of strings
//!
//! The function should return a 2D array containing all of the ways that the target can be
//! constructed by concatenating elements of the wordBank array

struct AllConstructRecur {
  vector<vector<string>> solve(const string& target, const vector<string>& wordBank) {
    _soFar.clear();
    _res.clear();
    solveImpl(target, wordBank);
    return _res;
  }

  bool solveImpl(const string& target, const vector<string>& wordBank) {
    if(target.empty())  {
      _res.push_back(_soFar);
      string subStr;
      for(const auto& s : _soFar) subStr.append(s);
      _memo[subStr] = _soFar;
      return true;
    }
    else if (_memo.contains(target)) {
      if(_memo[target])
        _res.push_back(_memo[target].value());
    }
    else {
      for(const auto& w : wordBank) {
        if(target.starts_with(w)) {
          _soFar.push_back(w);
          const auto subStr = target.substr(w.size());
          if(!solveImpl(subStr, wordBank))
            _memo[subStr].reset();
          _soFar.pop_back();
        }
      }
    }
  }
  vector<vector<string>> _res;
  vector<string> _soFar;
  map<string, optional<vector<string>>> _memo;
};

//! [05/09/2023]
//! Maybe soFar is not utilized as in the previous solution
//!     but this solution is simpler to reason and hence it was easier to design a DP version from it
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
  AllConstructRecur solveRecur;
  auto res = solveRecur.solve("abcdef", {"ab", "abc", "cd", "def", "abcd"}); // 1
  for(auto& v : res) {
    for(auto& w : v) cout << w << " ";
    cout << ";";
  }
  cout << '\n';
  res = solveRecur.solve("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}); // 0
  for(auto& v : res) {
    for(auto& w : v) cout << w << " ";
    cout << ";";
  }
  cout << '\n';
  res = solveRecur.solve("purple", {"purp", "p", "ur", "le", "purpl"}); // 2
  for(auto& v : res) {
    for(auto& w : v) cout << w << " ";
    cout << ";";
  }
  cout << '\n';
  res = solveRecur.solve("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}); // 4
  for(auto& v : res) {
    for(auto& w : v) cout << w << " ";
    cout << ";";
  }
  cout << '\n';
  res = solveRecur.solve("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
                           {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"}); // 0
  for(auto& v : res) {
    for(auto& w : v) cout << w << " ";
    cout << ";";
  }
  cout << '\n';

  cout << '\n';
  cout << '\n';
}