#pragma once
#include <bits/stdc++.h>
using namespace std;

#include <include/graph.hpp>

namespace lec4 {
  /**
   * Граф задается списками смежности, они хранятся в unordered_map
   * @attention для направленного графа нужно делать проверку есть ли вершина среди ключей unordered_map
   */
  struct DFS {
    const Graph<size_t>& g;
    DFS(const Graph<size_t>& g) : g(g) {}
    unordered_map<size_t, bool> visited;
    vector<size_t> dfs_;

    void dfs(size_t u) {
      visited[u] = true;
      cout << "in: " << u << '\n';
      dfs_.push_back(u);
      //! @attention Для направленного графа, возможна ситуация когда нет исходящих ребер из данной вершине
      //! поэтому ее не будет в качестве ключа в g.adjList и g.adjList.at(u) will throw
      if(g.adjList.find(u) != g.adjList.end()) {
        for(auto v : g.adjList.at(u)) {
          if(!visited[v])
            dfs(v);
        }
      }
      cout << "out: " << u << '\n';
    }

    vector<size_t> get_dfs(size_t u) {
      visited.clear();
      dfs_.clear();
      dfs(u);
      return dfs_;
    }
  };
}
