#include <bits/stdc++.h>
using namespace std;

//! Single source shortest paths : compute shortest paths from the source s vertex to all other vertexes
//!
//! The algorithm is very similar to MST Prims`s algorithm, in both we maintain a set of edges for which we solved
//!
//! In Dijkstra we maintain a set (a tree) of edges for which the shortest distance has been estimated
//! In Dijkstra we compute solution to the bigger subproblem based on the solutions to smaller once, in this
//! this is similar to a DP algorithm
//!
//! Unlike Prims algorithm Dijkstra does not work with negative cost edges

struct Info {
  size_t distTo;
  int parent;
};

using G = unordered_map<int/*v*/, vector< pair<int/*w_vu*/,int/*u*/> > >;

vector<Info> Dijkstra(G & g, int s) {
  const int n = g.size();
  constexpr size_t INF = numeric_limits<size_t>::max();
  //! vertexes are labeled from 0 .. n-1, initially our tree is empty
  vector<Info> shortestPaths(n, {INF,-1});
  vector<char> inTree(n, 0);

  int v = s; // v - is vertex for which min distance has been established
  shortestPaths[s].parent = -1;
  shortestPaths[s].distTo = 0; //! base

  while(!inTree[v]) {
    inTree[v] = 1;

    for(const auto& [w_vu,u] : g[v]) {
      if(shortestPaths[u].distTo > shortestPaths[v].distTo + w_vu) {
        shortestPaths[u].distTo = shortestPaths[v].distTo + w_vu;
        shortestPaths[u].parent = v;
      }
    }

    // pick the vertex with the shortest distance
    size_t minDist = INF;
    for(int i = 0; i < g.size(); ++i) {
      if(!inTree[i] && minDist > shortestPaths[i].distTo) {
        minDist = shortestPaths[i].distTo;
        v = i;
      }
    }
  }
  return shortestPaths;
}

//! prints the shortest path from s to t
void printShortestPath(const vector<Info>& path, int t) {
  if(t == -1) return;
  printShortestPath(path, path[t].parent);
  cout << t << "->";
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
  //! This example is for undirected graph
  while(eN--) {
    int u,v,w;
    ss >> u >> v >> w;
    g[u].emplace_back(w,v);
    g[v].emplace_back(w,u);
  }

  auto sp = Dijkstra(g, 0);
  for(int i = 0; i < g.size(); ++i) {
    cout << i << " length of the shortest path:" << sp[i].distTo << '\n';
    cout << i << " shortest path:";
    printShortestPath(sp, i);
    cout << '\n';
  }

  return 0;
}