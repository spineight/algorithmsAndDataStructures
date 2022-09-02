//! https://codeforces.com/group/yg7WhsFsAp/contest/355490/problem/P02
#include <bits/stdc++.h>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  int n;
  cin >> n;
  vector<int> a(n);
  for(auto& v : a) cin >> v;
  int l,r;
  cin >> l >> r;
  // prefixSum[i] - sum of the first i elements
  vector<int> prefixSum(n+1,0);
  for(int i = 1; i <= n; ++i)
    prefixSum[i] = prefixSum[i-1] + a[i-1];
  // [l,r] = prefixSum[r+1] - prefixSum[l]
  cout << prefixSum[r+1] - prefixSum[l] << '\n';

  return 0;
}