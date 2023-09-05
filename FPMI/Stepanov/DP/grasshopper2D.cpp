#include <bits/stdc++.h>

using namespace std;

//! starts at [0,0], should end at [n-1,n-1]
//! can jump at length 1 to the left/down
int grassHopper2DCollectMaxVer0(const vector<vector<int>>& money) {
  if(money.empty()) return 0;
  const int rowsN = money.size();
  const int colsN = money.front().size();
  constexpr int NEG_INF = -2e9;
  vector<vector<int>> dp(rowsN, vector<int>(colsN, NEG_INF));
  dp[0][0] = money[0][0];

  for(int r = 0; r < rowsN; ++r) {
    for(int c = 0; c < colsN; ++c) {
      if(r > 0) dp[r][c] = dp[r-1][c] + money[r][c];
      if(c > 0) dp[r][c] = max(dp[r][c], dp[r][c-1] + money[r][c]);
    }
  }
  return dp[rowsN-1][colsN-1];
}

//! Optimized memory usage: we need only 2 rows
int grassHopper2DCollectMaxVer1(const vector<vector<int>>& money) {
  if(money.empty()) return 0;
  const int rowsN = money.size();
  const int colsN = money.front().size();
  constexpr int NEG_INF = -2e9;
  vector<vector<int>> dp(2, vector<int>(colsN, NEG_INF));
  dp[0][0] = money[0][0];

  //! separate processing of the top row
  for(int c = 1; c < colsN; ++c) {
    //! There is no max fn here, as we don't have a choice, we could come only from the left neighbour
    dp[0][c] = dp[0][c-1] + money[0][c];
  }

  int prevRowIdx = 0;
  int curRowIdx = 1;
  for(int r = 1; r < rowsN; ++r) {
    for(int c = 0; c < colsN; ++c) {
      dp[curRowIdx][c] = dp[prevRowIdx][c] + money[r][c]; // top
      if(c > 0) dp[curRowIdx][c] = max(dp[curRowIdx][c], dp[curRowIdx][c-1]/*left*/ + money[r][c]);
    }
    prevRowIdx = (prevRowIdx + 1) % 2;
    curRowIdx = (curRowIdx + 1) % 2;
  }
  return dp[prevRowIdx][colsN-1];
}

int main() {
  cout << grassHopper2DCollectMaxVer0({
    {-1,0,0},
    {-1,0,-1},
    {-1,0,0}}) << '\n';
  cout << grassHopper2DCollectMaxVer0({
                                              {-1,-2,4},
                                              {-1,1,1},
                                              {-1,0,0}}) << '\n';
  cout << "\n";
  cout << grassHopper2DCollectMaxVer1({
    {-1,0,0},
    {-1,0,-1},
    {-1,0,0}}) << '\n';
  cout << grassHopper2DCollectMaxVer1({
                                              {-1,-2,4},
                                              {-1,1,1},
                                              {-1,0,0}}) << '\n';
  return 0;
}