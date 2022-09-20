#include <bits/stdc++.h>
using namespace std;

constexpr int MAX_N {100};
using G = int [MAX_N][MAX_N];


//! Floyd algorithm - All pairs shortest paths
//! As we need shortest paths between for every pair of vertexes - adjacency matrix representation of graph is more convenient
//! In unweighted graph by a[i][j] = 1 - we denoted that there is edge between i,j, by a[i][j] = 0 - absence of edge
//! On weighted graph we need different approach, otherwise a[i][j] = 0 - will by the shortest edge
//! On weighted graph we agree that a[i][j] = INF - denotes the absence of edge between i and j vertexes

void Floyd(G& g, int n) {
  for(int k = 0; k < n; ++k) { //! k - intermediate vertex counter
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < n; ++j) {
        int through_k = g[i][k] + g[k][j]; //! distance through vertex k
        if(g[i][j] > through_k)
          g[i][j] = through_k;
      }
    }
  }
}

int main() {

  string task0 = R"(
    6 8
    0 1 1
    1 2 5
    2 3 1
    3 4 1
    4 5 2
    5 0 2
    2 5 2
    1 4 3
  )";
  stringstream ss(task0);
  int vN, eN;
  ss >> vN >> eN;
  G g;
  constexpr int INF{numeric_limits<int>::max() / 4};
  for(int i  = 0; i < size(g); ++i) {
    for(int j = 0; j < size(g); ++j)
      g[i][j] = INF;
  }
  //! This example is for undirected graph
  while(eN--) {
    int u,v,w;
    ss >> u >> v >> w;
    g[u][v] = g[v][u] = w;
  }

  Floyd(g, vN);

  for(int i = 0; i < vN; ++i) {
    for(int j = 0; j < vN; ++j) {
      cout << g[i][j] << " ";
    }
    cout << '\n';
  }

  return 0;
}