#include <bits/stdc++.h>
using namespace std;
int main() {
  vector<int> a = { 3,1,2,5,4,6,7,8,9 };
  vector<int> a1{a};
  const int n = a.size();
  for (int i = 0; i < n; ++i) {
    int x = a[i];
    partition(begin(a1), end(a1), [x](int val){return val < x;});
    cout << "x:" << x << ": ";
    for(auto v : a1) cout << v << ",";
    cout << '\n';
    lower_bound(begin(a1), end(a1), x);
  }
  return 0;
}