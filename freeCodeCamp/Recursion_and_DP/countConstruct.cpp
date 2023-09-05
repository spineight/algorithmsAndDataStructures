#include <bits/stdc++.h>
using namespace std;

//! write a function countConstruct(target, wordBank)
//! that accepts a target string and an array of strings
//!
//! The function should return the number of ways that the target can be constructed by concatenating elements of wordBank
//!
//! You may reuse elements of wordBank as many times as needed


//! [05/09/2023]
struct CountConstruct {
  map<string_view , int> memo;
  int calculateImpl(string_view sw, const vector<string>& words) {
    if(sw.empty()) return 1;
    if(auto it = memo.find(sw); it != end(memo)) {
      return it->second;
    }
    int count{0};

    for(const auto& w : words) {
      if(sw.size() >= w.size() && sw.starts_with(w)) {
        count += calculateImpl(sw.substr(w.size()), words);
      }
    }
    memo[sw] = count;
    return count;
  }
public:
  int calculate(string s, const vector<string>& words) {
    memo.clear();
    return calculateImpl(string_view {s.data(), s.size()}, words);
  }
};

//! [05/09/2023]
int countConstructIter(string_view s, const vector<string>& words) {
  vector<int> dp(s.size()+1, 0);
  dp[0] = 1;
  for(int i = 1; i <= s.size(); ++i) {
    for(const auto& w: words) {
      if(i >= w.size() && s.substr(i-w.size()).starts_with(w))
        dp[i] += dp[i-w.size()];
    }
  }
  return dp[s.size()];
}

int main() {
//  CountConstructsRecur solveRecur;
//  cout << solveRecur.solve("abcdef", {"ab", "abc", "cd", "def", "abcd"}) << '\n'; // 1
//  cout << solveRecur.solve("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) << '\n'; // 0
//  cout << solveRecur.solve("purple", {"purp", "p", "ur", "le", "purpl"}) << '\n'; // 2
//  cout << solveRecur.solve("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) << '\n'; // 4
//  cout << solveRecur.solve("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
//                           {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"}) << '\n'; // 0
//
//  cout << '\n';
//  cout << '\n';
//
//  CountConstructsDP solveDP;
//  cout << solveDP.solve("abcdef", {"ab", "abc", "cd", "def", "abcd"}) << '\n'; // 1
//  cout << solveDP.solve("skateboard", {"bo", "rd", "ate", "t", "ska", "sk", "boar"}) << '\n'; // 0
//  cout << solveDP.solve("purple", {"purp", "p", "ur", "le", "purpl"}) << '\n'; // 2
//  cout << solveDP.solve("enterapotentpot", {"a", "p", "ent", "enter", "ot", "o", "t"}) << '\n'; // 4
//  cout << solveDP.solve("eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef",
//                           {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"}) << '\n'; // 0
}