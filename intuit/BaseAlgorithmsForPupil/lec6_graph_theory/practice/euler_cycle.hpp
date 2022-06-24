#pragma once
#include <practice/graph.hpp>

namespace lec6::practice {
  /**
   * Он базируется на обходе в глубину, но обход в глубину, он чем характеризуется:
   *   он не проходит по одной вершине два раза
     А мы напишем вариант, который не входит в одно ребро два раза
   * @tparam T
   */
  template<typename T>
  struct EulerCycle {
    const Graph<T>& g;
    vector<pair<T,T>> cycle;
    set<pair<T,T>> visitedEdges;
    EulerCycle(const Graph<T>& g) : g(g) {}

    void DFS(const pair<T,T>& edge) {
      auto& [u,v] = edge;
      visitedEdges.emplace(u,v);
      visitedEdges.emplace(v,u);

      for(auto to : g.adj.at(v)) {
        if(visitedEdges.find({v,to}) == visitedEdges.end()) {
          DFS({v,to});
        }
      }
      cycle.emplace_back(u,v);
    }
    /**
     *
     * @return true if cycle exists
     */
    bool Do() {
      T u = g.adj.begin()->first;
      T v = g.adj.at(u).front();
      DFS({u,v});
      return true;
    }
    vector<pair<T,T>> getCycle() {
      Do();
      reverse(begin(cycle), end(cycle));
      return cycle;
    }
  };
}