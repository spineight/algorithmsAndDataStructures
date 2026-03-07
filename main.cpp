#include <bits/stdc++.h>
using namespace std;

/*!

https://cses.fi/problemset/task/1746

You know that an array has n integers between 1 and  m, 
and the absolute difference between two adjacent values is at most 1.

Given a description of the array where some values may be unknown, 
your task is to count the number of arrays that match the description.
Input
The first input line has two integers n and m: the array size and the upper bound for each value.
The next line has n integers x_1,x_2,\dots,x_n: the contents of the array. Value 0 denotes an unknown value.
Output
Print one integer: the number of arrays modulo 10^9+7.
Constraints

1 <= n <= 10^5
1 <= m <= 100
0 <= x_i <= m

Example
Input:
3 5
2 0 2

Output:
3

Explanation: The arrays [2,1,2], [2,2,2] and [2,3,2] match the description.
*/

#include <bits/stdc++.h>
using namespace std;

int arrayDescription(vector<int> a, int m) {
    // 2 0 2
    // 0 0 0 
    // dp[k][i] - number of arrays for prefix of size k and the last element = i
    const int n = a.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    if(a.front() == 0) {
        for(int i = 1; i <= m; ++i) dp[1][i] = 1;
    } else {
        dp[1][a.front()] = 1;
    }
    const int MOD = 1e9+7;
    for(int i = 2; i <= n; ++i) {
        int val = a[i-1];
        if(val != 0) {
            dp[i][val] += dp[i-1][val];
            dp[i][val] %= MOD;
            if(val - 1 > 0) {
                dp[i][val] += dp[i-1][val-1];
                dp[i][val] %= MOD;
            }
            if(val + 1 <= m) {
                dp[i][val] += dp[i-1][val+1];
                dp[i][val] %= MOD;
            }
        } else {
            for(int j = 1; j <= m; ++j) {
                dp[i][j] += dp[i-1][j];
                dp[i][j] %= MOD;
                if(j - 1 > 0) {
                    dp[i][j] += dp[i-1][j-1];
                    dp[i][j] %= MOD;
                }
                if(j + 1 <= m) {
                    dp[i][j] += dp[i-1][j+1];
                    dp[i][j] %= MOD;
                }
            }
        }
    }
    if(a.back() == 0) {
        return accumulate(begin(dp.back()), end(dp.back()), 0, [](int lhs,int rhs){ return (rhs + lhs) % MOD;});
    }
    return dp.back()[a.back()];
}


int main() {
    // freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int n,m;
    cin >> n >> m;
    vector<int> arr(n);
    for(auto& v : arr) cin >> v;
    cout << arrayDescription(arr,m) << '\n';
    return 0;
}
