#include <bits/stdc++.h>

using namespace std;

//! money[i] - amount at i-th pos
//! grashopper can do jumps of length 1,2
//! start at 0-th pos, should end at (n-1)-th pos
//! Task: maximize amount of money it can collect
int grashopperCollectMax(const vector<int>& money) {
  if(money.empty()) return 0;
  if(money.size() == 1) return money[0];

  //! If we reached this point, money.size() is garanteed >= 2
  //! Important improvement over my previous implementation with 3 variables (prev_prev, prev, res)
  //! NB!!! only 2 variables are sufficient !!! --> this is my idea
  int prev = money[0]; // prev_prev
  int res = money[0]+money[1]; // prev

  for(int i = 2; i < money.size(); ++i) {
    res = max(prev , res) + money[i];
    prev = res;
  }
  return res;
}

int main() {
  cout << grashopperCollectMax({1}) << '\n';
  cout << grashopperCollectMax({1,-1}) << '\n';
  cout << grashopperCollectMax({1,2}) << '\n';
  cout << grashopperCollectMax({1,2,3}) << '\n';
  cout << grashopperCollectMax({-1,-2,-3}) << '\n';
  cout << grashopperCollectMax({-1,2,-3}) << '\n';
  return 0;
}