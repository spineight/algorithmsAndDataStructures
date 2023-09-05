#include <bits/stdc++.h>
using namespace std;

//! canConstruct(target, wordBank)
//! Accepts a target string and array of strings
//! Should return boolean indicating whether target can be constructed by concatenating elements of the wordBank array

struct CanConstruct {
  map<string, bool> memo;
  bool calculate(string s, const vector<string>& words) {
    if(s.empty()) return true;
    if(auto it = memo.find(s); it != end(memo)) {
      return it->second;
    }

    for(const auto& w : words) {
      if(s.starts_with(w)) {
        if( calculate(s.substr(w.size()), words) )
          // no need to store this to memo, as we stop once true
          return true;
      }
    }

    // tried all and nothing worked
    memo[s] = false;
    return false;
  }
};

struct CanConstructDP {
  bool solve(const string &target, const vector<string> wordBank) {
    vector<char> dp(target.size()+1); // dp[i] - can construct the target's prefix of size i using wordBank
    dp[0] = true; // can construct prefix of length 0 using zero words from the bank
    for(int prefixLen = 1; prefixLen <= target.size(); ++prefixLen) {
      for(const auto& w : wordBank) {
        if(w.size() <= prefixLen) {
          string_view subStr(target.data() + prefixLen - w.size());
          if (subStr.starts_with(w) && dp[prefixLen - w.size()] ) {
              dp[prefixLen ] = 1;
          }
        }
      }
    }
    return dp[target.size()];
  }
};

int main() {
  CanConstructRecur solveRecur;
  cout << solveRecur.solve("abcdef", {"ab", "abc", "cd", "def", "abcd"}) << '\n'; // 1
  cout << solveRecur.solve("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) << '\n'; // 0
  cout << solveRecur.solve("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) << '\n'; // 1
  cout << solveRecur.solve("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"}) << '\n'; // 0

  cout << '\n';
  cout << '\n';

  CanConstructDP solveDP;
  cout << solveDP.solve("abcdef", {"ab", "abc", "cd", "def", "abcd"}) << '\n'; // 1
  cout << solveDP.solve("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) << '\n'; // 0
  cout << solveDP.solve("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) << '\n'; // 1
  cout << solveDP.solve("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef", {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"}) << '\n'; // 0
  return 0;
}