#include <bits/stdc++.h>

using namespace std;

//! https://www.spoj.com/problems/RMQSQ/

struct SparseTableMin {
  vector<vector<int>> st;
  SparseTableMin(const vector<int>& a) {
    size_t n = a.size();
    const size_t maxK = __lg(n);
    st.assign(maxK+1, vector<int>(n));

    //! base
    for(size_t i = 0; i < n; ++i)
      st[0][i] = a[i];
    //! transition
    for(size_t k = 1; k <= maxK; ++k) {
      for(size_t i = 0; i + (1 <<(k-1)) < n; ++i) {
        st[k][i] = min(st[k-1][i], st[k-1][i + (1 <<(k-1))]);
      }
    }
  }
  //! [l,r)
  int query(int l, int r) {
    auto k = __lg(r-l);
    return min(st[k][l], st[k][r-(1 << k)]);
  }
};


int main() {
  int n,q;
  cin >> n;
  vector<int> a(n);
  for(auto& v : a) cin >> v;
  cin >> q;
  SparseTableMin stm(a);
  while(q--) {
    int l,r;
    cin >> l >> r;
    cout << stm.query(l,r+1) << '\n';
  }
  return 0;
}