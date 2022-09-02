//! https://codeforces.com/group/yg7WhsFsAp/contest/355490/problem/P08

#include <bits/stdc++.h>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  int n,L,a;
  cin >> n >> L >> a;
  int res{0};
  int prevT{0};
  int t{0},l{0};
  while(n--) {
    cin >> t >> l;
    if(prevT < t) {
      res += (t-prevT) / a;
    }
    prevT = t + l;
  }
  res += (L - t - l) / a;
  cout << res << '\n';
  return 0;
}