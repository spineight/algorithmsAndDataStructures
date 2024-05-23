#include <bits/stdc++.h>

using namespace std;


//! NB!!! Нерабочая версия, так как предложенная Павлом quick_sort не работает!!!
//! [l,r)
int kth_elem(auto& engine, vector<int>& a, int k, int l, int r) {
  if(r-l <= 1) return a[l];
    const int n = a.size();
    assert(r <= n);
    uniform_int_distribution<int> dist(l, r - 1);
    const int x = a[dist(engine)];
    int m{0};
    //! инвариант - все элементы с индексами < m : < X
    for (int i = l; i < r; ++i) {
      if (a[i] < x) swap(a[i], a[m++]);
    }
    if(k < m) return kth_elem(engine, a, k, l, m);
    else return kth_elem(engine, a, k, m, r);
}

int kth_elem(vector<int>& a, int k) {
  random_device rd;
  mt19937 engine(rd());
  return kth_elem(engine, a, k,0, a.size());
}

int main() {
  random_device rd;
  mt19937 engine(rd());
  uniform_int_distribution sz_dist(1,1000);
  uniform_int_distribution val_dist(0,10000);
  const int iter_cnt{1000};
  for(int i = 0; i < iter_cnt; ++i) {
    const int n = sz_dist(engine);
    vector<int> a(n);
    generate(begin(a), end(a), [&](){return val_dist(engine);});
    vector<int> b(a);
    uniform_int_distribution pos_dist(0,n-1);
    int k = n == 1 ? 0 : pos_dist(engine);
    auto it = begin(a) + k;
    nth_element(begin(a), it, end(a));
    const int res = kth_elem(a,k);
    assert(*it == res);
  }
  return 0;
}