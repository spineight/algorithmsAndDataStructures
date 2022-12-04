#include <bits/stdc++.h>
using namespace std;

long long hornersRule(const vector<int>& a, long long x) {
  long long res{0};
  const int n = a.size();
  for(int i = 0; i < n - 1; ++i) {
    res += a[i];
    res *= x;
  }
  res += a.back();
  return res;
}

int main() {
  // x^4
  // x = 2 : 16
  cout << hornersRule({1,0,0,0,0}, 2) << '\n';

  // x^4 + 4x^2 + 2x + 1
  // x = 2 : 16 + 16 + 4 + 1 = 37
  // x = 4 : 256 + 64 + 8 + 1 = 329
  cout << hornersRule({1,0,4,2,1}, 2) << '\n';
  cout << hornersRule({1,0,4,2,1}, 4) << '\n';

  // x^10 + x^5 + 1
  // x = 2 : 1024 + 32 + 1 = 1057
  cout << hornersRule({1,0,0,0,0,1,0,0,0,0,1}, 2) << '\n';

  // 10
  cout << hornersRule({10},4) << '\n';
  return 0;
}