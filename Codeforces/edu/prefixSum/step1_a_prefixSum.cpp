#include <bits/stdc++.h>

using namespace std;



int main() {
  int n;
  cin >> n;
  vector<long long> a(n);
  for(auto& v : a) cin >> v;

  vector<long long> prefixSum(n+1,0);
  cout << 0 << " ";
  for(size_t i = 1; i <=n; ++i) {
    prefixSum[i] = prefixSum[i-1] + a[i-1];
    cout << prefixSum[i] << " ";
  }
  cout << '\n';
  return 0;
}