#include <bits/stdc++.h>
using namespace std;

//! canSum(targetSum, numbers)
//! takes in the targetSum and array of numbers as arguments.
//! return a boolean indicating whether or not it is possible to generate the targetSum using numbers from the array
//! You may use an element from the array as many times as needed
//! You may assume that all input numbers are nonnegative

struct SolveCanSumRecur {
  bool solve(long long targetSum, const vector<size_t> &a) {
    _numbers = a;
    _memo.clear();
    return solveImpl(targetSum);
  }
  bool solveImpl(long long targetSum) {
    if(targetSum == 0) return true;
    if(_memo.contains(targetSum))
      return _memo[targetSum];

    for(auto num : _numbers) {
      if(targetSum >= num)
        if(solveImpl(targetSum - num)) {
          _memo[targetSum] = true;
          return true;
        }
    }
    _memo[targetSum] = false;
    return false;
  }
  vector<size_t> _numbers;
  unordered_map<long long, bool> _memo;
};

struct SolveCanSumDP {
  bool solve(long long targetSum, const vector<size_t> &a) {
    vector<char> dp(targetSum+1, false);
    dp[0] = 1;
    for(int curSum = 1; curSum <= targetSum; ++curSum) {
      for(int v : a) {
        if(curSum >= v && dp[curSum-v]) {
          dp[curSum] = 1;
        }
      }
    }
    return dp[targetSum];
  }
};


int main() {
  SolveCanSumRecur solveRecur;
  SolveCanSumDP solveDP;
  cout << solveRecur.solve(7, {5,3,4,7}) << '\n'; //  1
  cout << solveRecur.solve(7, {2,3}) << '\n'; // 1
  cout << solveRecur.solve(7, {2,4}) << '\n'; // 0
  cout << solveRecur.solve(8, {2,3,5}) << '\n'; // 1
  cout << solveRecur.solve(300, {7,14}) << '\n'; // 0

  cout << '\n';

  cout << solveDP.solve(7, {5,3,4,7}) << '\n'; //  1
  cout << solveDP.solve(7, {2,3}) << '\n'; // 1
  cout << solveDP.solve(7, {2,4}) << '\n'; // 0
  cout << solveDP.solve(8, {2,3,5}) << '\n'; // 1
  cout << solveDP.solve(300, {7,14}) << '\n'; // 0
  return 0;
}