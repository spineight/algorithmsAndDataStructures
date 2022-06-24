#pragma once
#include <bits/stdc++.h>
using namespace std;

#include <practice/graph.hpp>

namespace lec4::practice {
  /**
 * Граф задается списками смежности, они хранятся в unordered_map
 * @attention для направленного графа нужно делать проверку есть ли вершина среди ключей unordered_map
 */
  struct DFS {
    const Graph<size_t>& g;
    unordered_map<size_t, bool> visited;
    vector<size_t> dfs_;
    DFS(const Graph<size_t>& g) : g(g) {

    }

    //! @param u
    void dfs(size_t u) {
      visited[u] = true;
      dfs_.push_back(u);
      if(g.adjList.find(u) != g.adjList.end()) {
        for(auto v : g.adjList.at(u)) {
          if(!visited[v])
            dfs(v);
        }
      }
    }
    //! @param u
    vector<size_t> get_dfs(size_t u) {
      dfs_.clear();
      dfs(u);
      return dfs_;
    }
  };
}


