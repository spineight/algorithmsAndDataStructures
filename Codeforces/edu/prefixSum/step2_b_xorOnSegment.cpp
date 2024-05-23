#include <bits/stdc++.h>

using namespace std;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  int n;
  cin >> n;
  vector<long long> a(n);
  for(auto& v : a) cin >> v;

  vector<long long> prefixSum(n+1,0);
  for(size_t i = 1; i <= n; ++i) {
    prefixSum[i] = prefixSum[i-1] ^ a[i-1];
  }

  int q;
  cin >> q;
  while(q--) {
    int l,r;
    cin >> l >> r;
    cout << (prefixSum[r] ^ prefixSum[l-1]) << '\n';
  }
  return 0;
}