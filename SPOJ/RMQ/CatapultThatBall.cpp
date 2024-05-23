#include <bits/stdc++.h>

using namespace std;

//! https://www.spoj.com/problems/THRBL/

struct SparseTableMax {
  vector<vector<int>> st;
  SparseTableMax(const vector<int>& a) {
    const auto n = a.size();
    const auto maxK = __lg(n);
    st.assign(maxK+1, vector<int>(n));

    //! base
    for(size_t i = 0; i < n; ++i) {
      st[0][i] = a[i];
    }

    //! transition
    for(size_t k = 1; k <= maxK; ++k) {
      for(size_t i = 0; i + (1 <<(k-1)) < n; ++i) {
        st[k][i] = max(st[k-1][i], st[k-1][i + (1 <<(k-1))]);
      }
    }
  }
  //! [l,r)
  int query(int l, int r) {
    auto k = __lg(r-l);
    return max(st[k][l], st[k][r-(1 << k)]);
  }
};

int main() {
  int n,m;
  cin >> n >> m;
  vector<int> a(n);
  for(auto& v : a) cin >> v;
  SparseTableMax stm(a);
  int cnt{0};
  while(m--) {
    int l,r;
    cin >> l >> r;
    if(l > r) swap(l,r);
    auto maxH = stm.query(l-1,r-1);
    if(a[l-1] == maxH) ++cnt;
  }
  cout << cnt << '\n';
  return 0;
}