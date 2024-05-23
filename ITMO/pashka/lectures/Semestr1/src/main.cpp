#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while(t--) {
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> prefixPlus(n+1,0);
    vector<int> prefixMinus(n+1,0);
    for(int i = 1; i <= n; ++i) {
      prefixPlus[i] = prefixPlus[i-1];
      prefixMinus[i] = prefixMinus[i-1];
      if( (s[i-1] == '+' && i % 2 == 1) || s[i-1] == '-' && i % 2 == 0) ++prefixPlus[i];
      else ++prefixMinus[i];
    }
    while(q--) {
      int l,r;
      cin >> l >> r;
      int plus = prefixPlus[r] - prefixPlus[l];
      int minus = prefixMinus[r] - prefixMinus[l];
      cout << abs(prefixPlus[r] - prefixPlus[l-1]  - (prefixMinus[r] - prefixMinus[l-1]))<< '\n';
    }
  }
  return 0;
}


