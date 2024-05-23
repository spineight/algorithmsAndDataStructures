#include <bits/stdc++.h>
using namespace std;

//! https://www.spoj.com/problems/RPLN/

//! source: https://codeforces.com/blog/entry/101083
//! source code: https://cses.fi/paste/e2ba5886552dabab38838a/
//! looked up idea with rewriting min, to enable vectorization:
//! https://github.com/AliOsm/CompetitiveProgramming/blob/master/SPOJ/RPLN%20-%20Negative%20Score.cpp
using ll = long long;

int const nmax = 100'000;
int const lgmax = 16;
int v[nmax];
int rmq[lgmax+1][nmax+1];

//int lg(int number) {
//  return 31 - __builtin_clz(number);
//}

void precompute(int n) {
  const int maxK = __lg(n);
  for(int i = 0;i < n; ++i)
    rmq[0][i] = v[i];

  for(int k = 1; k <= maxK; ++k) {
    for (int i = 0; i + (1 << (k - 1)) < n; ++i) {
      if (rmq[k - 1][i] < rmq[k - 1][i + (1 << (k - 1))])
        rmq[k][i] = rmq[k - 1][i];
      else
        rmq[k][i] = rmq[k - 1][i + (1 << (k - 1))];
    }
  }
}

//! [l,r)
int extract(int l, int r) {
  const int k = __lg(r - l);
  return std::min(rmq[k][l], rmq[k][r - (1 << k)]);
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  int t;
  scanf("%d",&t);
  for(int i = 1; i <= t; ++i) {
    printf("Scenario #%d:\n", i);
    int n,q;
//    cin >> n >> q;
    scanf("%d %d",&n,&q);
    for(int j = 0; j < n; ++j) scanf("%d", &v[j]);
    precompute(n);


    while(q--) {
      int l,r;
//      cin >> l >> r;
      scanf("%d %d",&l,&r);
      if(l > r) swap(l,r);
      printf("%d\n",extract(l-1,r));
    }
  }
  return 0;
}