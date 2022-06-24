#pragma once
#include <include/graph.hpp>

namespace lec6 {
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
    EulerCycle(const Graph<T>& g) : g(g) {}

    set<pair<T,T>> visitedEdges;
    void DFS(pair<T,T> edge) {

      auto [u,v] = edge;
//      cout << "in:" << u << "-" << v << '\n';
      //! @attention Важно пометить также и обратное ребро (граф у нас неориентированный)
      //! Это делается для того, чтобы мы не пошли по нему второй раз
      visitedEdges.emplace(u,v);
      visitedEdges.emplace(v,u);
      if(g.adj.find(v) != g.adj.end()) {
        for(auto to : g.adj.at(v)) {
          if(visitedEdges.find({v,to}) == visitedEdges.end()) {
            DFS({v,to});
          }
        }
//        cout << "out:" << u << "-" << v << '\n';
        cycle.push_back(edge);
      }
    }
    /**
     *
     * @return true if cycle exists
     */
    bool Do() {

      unordered_map<T, long long> deg;

      for(auto [u, adjList] : g.adj) {
        --deg[u];

        for(auto v : adjList) {
          ++deg[v];
        }
      }

      // Нам подойдет любое ребро, так как это цикл
      T u = g.adj.begin()->first;
      T v = g.adj.at(u).front();

      // Степени всех вершин четны TODO - не работает
//      for(auto [v,d] : deg) {
//        if (d & 1) return false;
//      }
      // TODO В графе есть не более одной компоненты связности содержащей более одной вершины
      //  (Существование пней не мешает нашему циклу, так как они не добавляют вершин)
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