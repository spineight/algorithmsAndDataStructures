#include <bits/stdc++.h>
using namespace std;


//! NB!!! Looks like not working when all elements are equal!!!
//! [l,r)
void quickSortImpl(auto& engine, vector<int>& a, int l, int r) {
  if(r-l > 1) {
    uniform_int_distribution<int> dist(l, r - 1);
    //! NB!!! - если так получится, что dist нам все время дает мин элемент - то мы зациклимся
    //! так как одна из частей будет пустая, и поэтому размер входа не будет уменьшаться
    const int x = a[dist(engine)];
    int m = l;
    //! инвариант - все элементы с индексами < m : < X
    for (int i = l; i < r; ++i) {
      if (a[i] < x) swap(a[i], a[m++]);
    }
    quickSortImpl(engine, a, l, m);
    quickSortImpl(engine, a, m, r);
  }
}

void quickSort(vector<int>& a) {
  random_device rd;
  mt19937 engine(rd());
  quickSortImpl(engine, a,0, a.size());
}


int main() {
//  const int n = 10'000;
//  vector<int> a0(n);
//  iota(begin(a0), end(a0), 0);
//  quickSort(a0);
//  assert(is_sorted(begin(a0), end(a0)));
//
//  vector<int> a1(n);
//  iota(begin(a1), end(a1),0);
//  reverse(begin(a1), end(a1));
//  vector<int> a2(a1);
//  sort(begin(a2), end(a2));
//  quickSort(a1);
//  assert(a1 == a2);
//
//  //! Random test
//  random_device rd;
//  mt19937 engine(rd());
//  uniform_int_distribution<int> dist(0,n);
//  vector<int> a3(n);
//  generate(begin(a3), end(a3), [&](){return dist(engine);});
//  vector<int> a4(a3);
//  sort(begin(a3), end(a3));
//  quickSort(a4);
//  assert(a4 == a3);

  //! all elements equal
  vector<int> a5 = {5,5,5,5,5,5};
  vector<int> a6(a5);
  quickSort(a5);
  sort(begin(a6), end(a6));
  assert(a5 == a6);
  return 0;
}