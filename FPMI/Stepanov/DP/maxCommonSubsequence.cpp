#include <bits/stdc++.h>

using namespace std;

int lengthOfMaxCommonSubsequence(const string& a, const string& b) {
  const int m = a.size();
  const int n = b.size();
  if(m == 0 || n == 0) return 0;
  // Мы можем обрубить наши две строчки на каких-то начальных отрезках и сделать динамику
  vector<vector<int>> dp(m+1, vector<int>(n+1,0));
  // dp[i][j] - max len of Common subsequence of prefixes of strings a,b of length i,j
  for(int i = 1; i <= m; ++i) {
    for(int j = 1; j <= n; ++j) {
      if(a[i-1] == b[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
      else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
    }
  }
  return dp[m][n];
}

int lengthOfMaxCommonSubsequenceVer1(const string& a, const string& b) {
  const int m = a.size();
  const int n = b.size();
  if(m == 0 || n == 0) return 0;
  // Мы можем обрубить наши две строчки на каких-то начальных отрезках и сделать динамику
  vector<vector<int>> dp(2, vector<int>(n+1,0));
  int prevRowIdx = 0;
  int curRowIdx = 1;
  // dp[i][j] - max len of Common subsequence of prefixes of strings a,b of length i,j
  for(int i = 1; i <= m; ++i) {
    for(int j = 1; j <= n; ++j) {
      if(a[i-1] == b[j-1]) dp[curRowIdx][j] = dp[prevRowIdx][j-1] + 1;
      else dp[curRowIdx][j] = max(dp[prevRowIdx][j], dp[curRowIdx][j-1]);
    }
    prevRowIdx = (prevRowIdx + 1) % 2;
    curRowIdx = (curRowIdx+1) % 2;
  }
  return dp[prevRowIdx][n];
}

string getMaxCommonSubsequence(const string& a, const string& b) {
  const int m = a.size();
  const int n = b.size();
  if(m == 0 || n == 0) return 0;
  // Мы можем обрубить наши две строчки на каких-то начальных отрезках и сделать динамику
  vector<vector<int>> dp(m+1, vector<int>(n+1,0));
  vector<vector<int>> from(m+1, vector<int>(n+1,0));
  // dp[i][j] - max len of Common subsequence of prefixes of strings a,b of length i,j
  for(int i = 1; i <= m; ++i) {
    for(int j = 1; j <= n; ++j) {
      if(a[i-1] == b[j-1]) {
        dp[i][j] = dp[i-1][j-1] + 1;
        from[i][j] = 0;
      }
      else {
        if(dp[i-1][j] > dp[i][j-1]) from[i][j] = -1;
        else from[i][j] = 1;
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }

  int i = m;
  int j = n;
  string res;
  while(i > 0 && j > 0) {
    if(from[i][j] == 0) {
      res.push_back(a[i-1]);
      --i;
      --j;
    } else if (from[i][j] == -1) {
      --i;
    } else --j;
  }
  reverse(begin(res), end(res));
  return res;
}

//! Idea that we don't need aux matrix to restore the answer
//! By value in DP[i][j] we can understand where we came from to it
string getMaxCommonSubsequenceVer1(const string& a, const string& b) {
  const int m = a.size();
  const int n = b.size();
  if(m == 0 || n == 0) return 0;
  // Мы можем обрубить наши две строчки на каких-то начальных отрезках и сделать динамику
  vector<vector<int>> dp(m+1, vector<int>(n+1,0));
  // dp[i][j] - max len of Common subsequence of prefixes of strings a,b of length i,j
  for(int i = 1; i <= m; ++i) {
    for(int j = 1; j <= n; ++j) {
      if(a[i-1] == b[j-1]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      }
      else {
        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      }
    }
  }

  int i = m;
  int j = n;
  string res;
  while(i > 0 && j > 0) {
    //! it is sufficient to compare to only one prev cell (top or left)
    //! because we do increase only on match
    if(dp[i][j] > dp[i-1][j]) {
      res.push_back(a[i-1]);
      --i;
      --j;
    } else {
      if(dp[i-1][j] > dp[i][j-1]) --i;
      else --j;
    }

  }
  reverse(begin(res), end(res));
  return res;
}

int main() {
  cout << lengthOfMaxCommonSubsequence("aab","ab") << '\n';
  cout << lengthOfMaxCommonSubsequence("abacad","aaa") << '\n';
  cout << '\n';
  cout << lengthOfMaxCommonSubsequenceVer1("aab","ab") << '\n';
  cout << lengthOfMaxCommonSubsequenceVer1("abacad","aaa") << '\n';

  cout << '\n';
  cout << getMaxCommonSubsequence("aab","ab") << '\n';
  cout << getMaxCommonSubsequence("abacad","aaa") << '\n';

  cout << '\n';
  cout << getMaxCommonSubsequenceVer1("aab","ab") << '\n';
  cout << getMaxCommonSubsequenceVer1("abacad","aaa") << '\n';
  return 0;
}