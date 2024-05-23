#include <bits/stdc++.h>

using namespace std;

//! We can precompute logn
//! (as described in Введение в программирование 7. Амортизационный анализ метод монет, потенциалов. Sparse table),
//! but according to: https://codeforces.com/blog/entry/75611 this is faster

//! __lg()
//! Implemented here: /home/oleg/GCC-12.2.0/include/c++/12.2.0/bits/stl_algobase.h
//inline _GLIBCXX_CONSTEXPR unsigned long long
//__lg(unsigned long long __n)
//{ return (int)sizeof(long long) * __CHAR_BIT__ - 1 - __builtin_clzll(__n); }

//size_t logn(uint64_t val) {
//  // cls - Count Leading Zeros
//  return 63 - __builtin_clz(val);
//}

struct SparseTable {
  vector<vector<long long>> st;
  SparseTable(const vector<long long>& a) {
    const unsigned long long n = a.size();
    const int maxK = __lg(n);
    st.assign(maxK+1, vector<long long>(n));

    //! base case
    for(size_t i = 0; i < n; ++i)
      st[0][i] = a[i];

    //! transition
    for(size_t k = 1; k <= maxK; ++k) {
      for(size_t i = 0; i + (1<<(k-1)) < n; ++i ) {
        //! min can be rewritten to enable vectorization:
        //! https://codeforces.com/blog/entry/75611
        st[k][i] = min(st[k-1][i], st[k-1][i + (1<<(k-1))]);
      }
    }
  }
  //! [l,r)
  long long query(unsigned long long l, unsigned long long r) {
    const auto k = __lg(r-l);
    //! min can be rewritten to enable vectorization:
    //! https://codeforces.com/blog/entry/75611
    return min(st[k][l], st[k][r-(1<<k)]);
  }
};

//! https://informatics.msk.ru/mod/statements/view.php?id=32990&chapterid=1663#1
void solve_task_1663() {
  unsigned long long n,k;
  cin >> n >> k;
  vector<long long> a(n);
  for(auto& v : a) cin >> v;
  SparseTable st(a);
  for(unsigned long long i = 0; i + k <= n; ++i)
    cout << st.query(i,i+k) << ' ';
  cout << '\n';
}

int main() {
  solve_task_1663();
  return 0;
}