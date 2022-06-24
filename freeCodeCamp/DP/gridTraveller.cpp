#include <bits/stdc++.h>
using namespace std;

//! You start from the top left corner of a 2D grid
//! You can move down or right
//! How many ways to get to the bottom right corner

struct SolutionGridTravellerRecur {
  size_t solve(int rowsCnt, int colsCnt) {
    _memo.clear();
    return solveImpl(rowsCnt-1, colsCnt-1);
  }
  size_t solveImpl(int r, int c) {
    if (r < 0 || c < 0) return 0; // out of bounds (not possible state)
    if (r == 0 && c == 0) return 1; // number of ways to get to the top left corner (starting state)
    if(_memo.contains({r,c})) return _memo[{r,c}];

    const auto res = solve(r - 1, c) + solve(r, c - 1);
    _memo[{r,c}] = res;
    return res;
  }
  map<pair<int,int>, size_t> _memo;
};

struct SolutionGridTravellerDP {
  size_t solve(int r, int c) {
    vector<vector<size_t>> dp(r+1, vector<size_t>(c+1,0));
    dp[0][0] = 1;
    for(int cr = 0; cr <= r; ++cr) {
      for(int cc = 0; cc <= c; ++cc) {
        if(cr > 0 ) dp[cr][cc] += dp[cr-1][cc];
        if(cc > 0) dp[cr][cc] += dp[cr][cc-1];
      }
    }
    return dp[r][c];
  }
};


int main() {
  SolutionGridTravellerRecur sRecur;
  cout << sRecur.solve(2,2) << '\n';

  SolutionGridTravellerDP sDP;
  cout << sDP.solve(2,2) << '\n';
  return 0;
}