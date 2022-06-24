#include <bits/stdc++.h>
using namespace std;

//! howSum(targetSum, numbers)
//! takes targetSum and array of numbers as arguments
//! Should return an array containing any combination of elements that add up exactly to the targetSum
//! If there is no combination - return null
//! If there are multiple combinations possible you may return any single one

struct HowSumRecur {
  optional<vector<int>> solve(int targetSum, const vector<int>& numbers) {
    _res.clear();
    _memo.clear();
    if(solveImpl(targetSum, numbers) ) return _res;
    return {};
  }
  bool solveImpl(int targetSum, const vector<int>& numbers) {
    if(targetSum == 0) return true;

    if(_memo.contains(targetSum)) {
      auto r = _memo[targetSum];
      if(!r) return false;
      _res = r.value();
      return true;
    }

    for(auto v : numbers) {
      if(v <= targetSum) {
        _res.push_back(v);
        if (solveImpl(targetSum - v, numbers)) {
          _memo[targetSum-v] = _res;
          return true;
        }
        _res.pop_back();
      }
    }
    _memo[targetSum] = {};
    return false;
  }
  vector<int> _res;
  unordered_map<int, optional<vector<int>>> _memo;
};

struct HowSumDP {
  optional<vector<int>> solve(int targetSum, const vector<int>& numbers) {
    vector<optional<vector<int>>> dp(targetSum+1);
    dp[0] = vector<int>();
    for(int curSum = 1; curSum <= targetSum; ++curSum) {
      for(auto num : numbers) {
        if(num <= curSum && dp[curSum - num]) {
          auto r = dp[curSum-num].value();
          r.push_back(num);
          dp[curSum] = r;
        }
      }
    }
    return dp[targetSum];
  }

};

int main() {
  HowSumRecur solveRecur;
  auto res = solveRecur.solve(7, {2,3});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  res = solveRecur.solve(7, {5,3,4,7});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  res = solveRecur.solve(7, {2,4});
  cout << res.has_value() << '\n';

  res = solveRecur.solve(8, {2,3,5});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  res = solveRecur.solve(300, {7,14});
  cout << res.has_value() << '\n';

  res = solveRecur.solve(300, {3,2,1});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  cout << '\n';
  cout << '\n';


  HowSumDP solveDP;
  res = solveDP.solve(7, {2,3});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  res = solveDP.solve(7, {5,3,4,7});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  res = solveDP.solve(7, {2,4});
  cout << res.has_value() << '\n';

  res = solveDP.solve(8, {2,3,5});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  res = solveDP.solve(300, {7,14});
  cout << res.has_value() << '\n';

  res = solveDP.solve(300, {3,2,1});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';
  return 0;
}