#include <bits/stdc++.h>
using namespace std;

//! canSum(targetSum, numbers)
//! takes in the targetSum and array of numbers as arguments.
//! return a boolean indicating whether or not it is possible to generate the targetSum using numbers from the array
//! You may use an element from the array as many times as needed
//! You may assume that all input numbers are nonnegative

//! [04/09/2023]
struct CanSum {
  bool calculate(int num, const vector<int>& nums, auto& memo) {
    if(0 == num) return true; // base case
    if(auto it = memo.find(num); it != end(memo)) { // memoization
      return it->second;
    }

    for(auto v : nums) {
      if(v <= num) {
        auto res = calculate(num-v,nums,memo);
        memo[num-v] = res;
        if(res) return true; // return immediately without trying any further options
      }
    }

    // tried all options and nothing worked
    return false;
  }
  bool calculate(int num, const vector<int>& nums) {
    assert(num >= 0); // works only for positive numbers
    unordered_map<int, bool> memo;
    //! We can optimize if sort elements of the vector
    //!     in this case we can exit from the loop earlier once we at element > target
    //!     because all further elements will be also greater
    return calculate(num, nums, memo);
  }
};

bool canSumIterative(int num, const vector<int>& nums) {
  vector<char> dp(num+1,0);
  dp[0] = 1;
  for(int i = 0; i <= num; ++i) {
    for(auto v: nums) {
      if(num - v >= 0 && dp[i-v])
        dp[i] = 1;
    }
  }
  return dp[num];
}

int main() {

  return 0;
}