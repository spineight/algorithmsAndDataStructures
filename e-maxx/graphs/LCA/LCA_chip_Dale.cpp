#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> tree;
vector<int> timeIn, timeOut;
struct Task {
//  map<int, vector<int>> tree;

  int timer{0};
  void DFS(int u) {
    timeIn[u] = ++timer;
    for(int v = 0; v < tree.size(); ++v) {
      if(!timeIn[v] && tree[u][v] && u != v) DFS(v);
    }
    timeOut[u] = ++timer;
  }

  bool isAncestor(int u, int v) {
    return timeIn[u] <= timeIn[v] && timeOut[v] <= timeOut[u];
  }

  void solve() {
    int n;
    cin >> n;

    tree.assign(n+1, vector<char>(n+1,0));
    for(int i = 0; i < n-1; ++i) {
      int u,v;
      cin >> u >> v;
      tree[u][v] = 1;
    }
    int m;
    cin >> m;
    while(m--) {
      int from,to;
      cin >> from >> to;
      timeIn.assign(n+1,0);
      timeOut.assign(n+1,0);
      DFS(from);
      if(isAncestor(from,to)) cout << "Yes\n";
      else cout << "No\n";
    }
  }
};

int main() {
  Task t;
  t.solve();
  return 0;
}

