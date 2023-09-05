#include <bits/stdc++.h>
using namespace std;

//! howSum(targetSum, numbers)
//! takes targetSum and array of numbers as arguments
//! Should return an array containing any combination of elements that add up exactly to the targetSum
//! If there is no combination - return null
//! If there are multiple combinations possible you may return any single one

//! [04/09/2023]
//!
struct HowSum {
  optional<vector<int>> calculate(int num, const vector<int>& nums, auto& memo) {
    if(0 == num) return vector<int>{};
    if(auto it = memo.find(num); it!= end(memo)) {
      return it->second;
    }

    for(auto v : nums) {
      if(v <= num) {
        auto suffixCombo = calculate(num - v, nums, memo);
        if(suffixCombo) {
          suffixCombo->push_back(v);
          memo[num] = suffixCombo;
          return suffixCombo;
        }
      }
    }

    // tried all options and non worked out
    memo[num] = nullopt;
    return nullopt;
  }
  optional<vector<int>> calculate(int num, const vector<int>& nums) {
    unordered_map<int, optional<vector<int>>> memo;
    return calculate(num,nums,memo);
  }
};

//! [04/09/2023]
//! Idea of parent vector
optional<vector<int>> howSumIterative(int num, const vector<int>& nums) {
  vector<int> parent(num+1,-1);
  parent[0] = 0;
  for(int i = 1; i <= num; ++i) {
    if(parent[i] != -1) continue;
    for(auto v : nums) {
      if(v <= i && parent[i-v] != -1) {
        parent[i] = i-v;
        break;
      }
    }
  }
  if(parent[num] == -1) return nullopt;
  vector<int> res;
  while(num > 0) {
    int v = num-parent[num];
    res.push_back(v);
    num -= v;
  }
  return res;
}

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