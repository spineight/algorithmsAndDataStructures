#include <bits/stdc++.h>

using namespace std;

struct BestSum {

  /*! This funtion should return an array containing the shortest combination of numbers
      that add up exactly to the target sum
  */
  optional<vector<int>> calculate(int num, const vector<int>& nums, auto& memo) {
    if(0 == num) return vector<int>{};

    if(auto it = memo.find(num); it != end(memo))
      return it->second;

    for(auto v : nums) {
      if(v <= num) {
        auto suffixSol = calculate(num-v,nums,memo);
        if(suffixSol) {
          suffixSol->push_back(v);
          if(!memo[num] || memo[num]->size() > suffixSol->size())
            memo[num] = suffixSol;
        }
      }
    }
    return memo[num];
  }
  optional<vector<int>> calculate(int num, const vector<int>& nums) {
    unordered_map<int, optional<vector<int>>> memo;
    return calculate(num,nums,memo);
  }
};

void testRecur(int num, const vector<int>& nums) {
  BestSum bs;
  auto res = bs.calculate(num, nums);
  if(res) {
    for(auto v : *res) cout << v << " ";
  }
  else
    cout << "No solution";
  cout << '\n';
}

optional<vector<int>> bestSumIter(int num, const vector<int>& nums) {
  constexpr int INF = 2e9;
  vector<pair<int/*parent*/,int/*len*/>> dp(num+1, {-1,INF});
  dp[0] = {0,0};;
  for(int i = 1; i <= num; ++i) {
    for(auto v : nums) {
      if(v <= i) {
        pair<int,int> candidate = {i-v, dp[i-v].second+1};
        if(dp[i].second > candidate.second)
          dp[i] = candidate;
      }
    }
  }
  if(dp[num].first == -1) return nullopt;

  vector<int> res;
  while(num > 0) {
    int val = num - dp[num].first;
    res.push_back(val);
    num -= val;
  }
  return res;
}

void testIter(int num, const vector<int>& nums) {
  auto res = bestSumIter(num, nums);
  if(res) {
    for(auto v : *res) cout << v << " ";
  } else cout << "No solution";
  cout << '\n';
}

int main() {
  testRecur(5,{3});
  testRecur(5,{5});
  testRecur(5,{1,2,3,5});
  testRecur(5,{1,2,3});
  testRecur(10,{1,2,3,4,5});
  testRecur(50,{1,2,3,5,25});

  testIter(5,{3});
  testIter(5,{5});
  testIter(5,{1,2,3,5});
  testIter(5,{1,2,3});
  testIter(10,{1,2,3,4,5});
  testIter(50,{1,2,3,5,25});
}