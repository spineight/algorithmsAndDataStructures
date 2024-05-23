#include <bits/stdc++.h>
using namespace std;

bool isPow2(int val) {
  return val && !(val & (val-1));
}

//! NB!!! - ошибка в реализации, выход за пределы массива ST!!!
void solve() {
  int n,k;
  cin >> n >> k;
  vector<int> a(n);
  for(auto& v : a) cin >> v;

  //! predprocessing
  vector<int> logn(n+1,0);
  for(int i = 2; i <= n; ++i) {
    logn[i] = logn[i-1];
    if(isPow2(i)) ++logn[i];
  }

  //! DP
  //! ST - Sparse Table
  //! ST[j][i] - min on the interval [i, i+2^j]
  vector<vector<int>> ST(logn[n]+1, vector<int>(n,0));
  //! Base
  for(int i = 0; i < n; ++i)
    ST[0][i] = a[i];
  //! transition:
  //
  for(int j = 1; j <= logn[n]; ++j) {
    for(int i = 0; (i + (1<<(j-1))) < n; ++i) {
      const int len = n-i+1;
      ST[j][i] = min(ST[j-1][i], ST[j-1][i + (1<<(j-1))]);
    }
  }

  //! Answer queries O(1) on interval [l,r]
  int l = 0;
  int r = min(n-1,k);
  while(r < n) {
    const int len = r-l+1;
    const int res = min(ST[logn[len]][l], ST[logn[len]][l + ( 1<<(logn[len]-1) )]);
    cout << res << " ";
    ++l;
    ++r;
  }
  cout << '\n';
}


int main() {
  solve();
  return 0;
}