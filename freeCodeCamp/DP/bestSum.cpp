#include <bits/stdc++.h>
using namespace std;

//! bestSum(targetSum, numbers)
//! takes targetSum and array of numbers as arguments
//! Should return an array containing the shortest combination of elements that add up exactly to the targetSum
//! If there is no combination - return null


struct BestSumRecur {
  optional<vector<int>> solve(int targetSum, const vector<int> &numbers) {
    _res.clear();
    _shortesRes.reset();
    _memo.clear();
    solveImpl(targetSum, numbers);
    return _shortesRes;
  }
  void solveImpl(int targetSum, const vector<int> &numbers) {
    if(targetSum == 0) {
      if(!_shortesRes.has_value() || _res.size() < _shortesRes->size())
        _shortesRes = _res;
    }
    if(_memo.contains(targetSum)) {
      auto r = _memo[targetSum];
      if(r) _res = r.value();
      return;
    }

    for(auto num : numbers) {
      if(num <= targetSum) {
        _res.push_back(num);
        solveImpl(targetSum-num, numbers);

        auto subSum = accumulate(begin(_res), end(_res), 0);
        if(subSum == targetSum) {
          _memo[targetSum] = _res;
        } else _memo[targetSum].reset();

        _res.pop_back();
      }
    }

  }
  vector<int> _res;
  optional<vector<int>> _shortesRes;
  unordered_map<int, optional<vector<int>>> _memo;
};

struct BestSumDP {
  optional<vector<int>> solve(int targetSum, const vector<int> &numbers) {
    vector<optional<vector<int>>> dp(targetSum+1);
    dp[0] = vector<int>();
    for(int curSum = 0; curSum <= targetSum; ++curSum) {
      for(auto num : numbers) {
        if(num <= curSum && dp[curSum - num]) {
          auto subTaskSol = dp[curSum - num].value();
          subTaskSol.push_back(num);
          if(!dp[curSum] || dp[curSum]->size() > subTaskSol.size())
            dp[curSum] = subTaskSol;
        }
      }
    }
    return dp[targetSum];
  }
};


int main() {
  BestSumRecur solveRecur;

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

  res = solveRecur.solve(8, {1,4,5});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  res = solveRecur.solve(300, {7,14});
  cout << res.has_value() << '\n';

  res = solveRecur.solve(300, {3,2,1});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  cout << '\n';
  cout << '\n';

  BestSumDP solveDP;
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

  res = solveDP.solve(8, {1,4,5});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  res = solveDP.solve(300, {7,14});
  cout << res.has_value() << '\n';

  res = solveDP.solve(300, {3,2,1});
  for(auto v : res.value()) cout << v << " ";
  cout << '\n';

  cout << '\n';
  cout << '\n';
  return 0;
}