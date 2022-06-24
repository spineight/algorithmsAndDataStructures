#include <bits/stdc++.h>
using namespace std;

struct MoveTowersSolver {
  MoveTowersSolver(int n) : a(n) {
    int cnt = n;
    for(auto& v : a) v = cnt--;
  }
  void showProgress() {
    int h = int( max({a.size(),b.size(),c.size()} ));
    while(h--) {
      if(a.size() >= h + 1) cout << setw(3) << a[h];
      else cout << setw(3) << '#';

      if(b.size() >= h + 1) cout << setw(3) << b[h];
      else cout << setw(3) << '#';

      if(c.size() >= h + 1) cout << setw(3) << c[h];
      else cout << setw(3) << '#';

      cout << '\n';
    }
    cout << '\n';
    cout << '\n';
    this_thread::sleep_for(chrono::seconds{1});
  }
  void MoveSingleDisk(vector<int>& src, vector<int>& dest) {
    dest.push_back(src.back());
    src.pop_back();
    showProgress();
  }
  void MoveTowers(int n, vector<int>& src, vector<int>& dest, vector<int>& tmp) {
    if(n > 0) {
      MoveTowers(n-1, src, tmp, dest);
      MoveSingleDisk(src, dest);
      MoveTowers(n-1, tmp, dest, src);
    }
  }

  void solve() {
    showProgress();
    MoveTowers(a.size(), a,b,c);
  }

  vector<int> a,b,c; // spindles
};

int main() {
  MoveTowersSolver solver(3);
  solver.solve();
  return 0;
}