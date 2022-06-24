#include <bits/stdc++.h>
using namespace std;

//! write a function countConstruct(target, wordBank)
//! that accepts a target string and an array of strings
//!
//! The function should return the number of ways that the target can be constructed by concatenating elements of wordBank
//!
//! You may reuse elements of wordBank as many times as needed


struct CountConstructsRecur {
  size_t solve(const string& target, const vector<string>& wordBank) {
    _memo.clear();
    return solveImpl(target, wordBank);
  }
  size_t solveImpl(const string& target, const vector<string>& wordBank) {
    if(target.empty()) return 1;
    if(_memo.contains(target)) return _memo[target];

    size_t cnt{0};

    for(const auto& w : wordBank) {
      if(target.starts_with(w)) {
        cnt += solveImpl(target.substr(w.size()), wordBank);
      }
    }
    _memo[target] = cnt;

    return cnt;
  }
  map<string, size_t> _memo;
};

struct CountConstructsDP {
  size_t solve(const string &target, const vector<string> &wordBank) {
    vector<size_t> dp(target.size()+1,0); // dp[k] = number of ways to construct prefix of size k
    dp[0] = 1;
    for(int prefixSize = 1; prefixSize <= target.size(); ++prefixSize) {
      for(const auto& w : wordBank) {
        if(w.size() <= prefixSize) {
          string_view subStr(target.data() + prefixSize - w.size());
          if(subStr.starts_with(w)) {
            dp[prefixSize] += dp[prefixSize - w.size()];
          }
        }
      }
    }
    return dp[target.size()];
  }
};

int main() {
  CountConstructsRecur solveRecur;
  cout << solveRecur.solve("abcdef", {"ab", "abc", "cd", "def", "abcd"}) << '\n'; // 1
  cout << solveRecur.solve("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) << '\n'; // 0
  cout << solveRecur.solve("purple", {"purp", "p", "ur", "le", "purpl"}) << '\n'; // 2
  cout << solveRecur.solve("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) << '\n'; // 4
  cout << solveRecur.solve("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
                           {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"}) << '\n'; // 0

  cout << '\n';
  cout << '\n';

  CountConstructsDP solveDP;
  cout << solveDP.solve("abcdef", {"ab", "abc", "cd", "def", "abcd"}) << '\n'; // 1
  cout << solveDP.solve("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) << '\n'; // 0
  cout << solveDP.solve("purple", {"purp", "p", "ur", "le", "purpl"}) << '\n'; // 2
  cout << solveDP.solve("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) << '\n'; // 4
  cout << solveDP.solve("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
                           {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"}) << '\n'; // 0
}