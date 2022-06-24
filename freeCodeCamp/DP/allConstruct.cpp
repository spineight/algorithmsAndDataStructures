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