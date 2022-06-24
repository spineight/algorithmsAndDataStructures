#pragma once
#include <practice/graph.hpp>

namespace lec6::practice {
  template<typename T>
  /**
   * Идея - сначала у нас лес из пней
   * Жадно берем очередное ребро наименьшего веса, если это ребро разреза(имеет концы разных цветов) - добавляем его в MST,
   * красим
   * @tparam T
   */
  struct MST_Kruskal {
    const WeightedGraph<T>& g;
    vector<pair<T,T>> MST;
    unordered_map<T, size_t> colors;

    //!@attention Наивная реализация (TODO - использовать систему непересекающихся множеств для O(1))
    void Union(T u, T v) {
      auto colorV = colors[v];
      for(auto& [i, adjList] : g.adj) {
        if(colors[i] == colorV)
          colors[i] = colors[u];
      }
    }

    MST_Kruskal(const WeightedGraph<T>& g) : g(g) {}

    void Do() {
      vector<tuple<size_t,T,T>> edges;
      //! изначально лес из пней, каждый из которых покрашен в свой цвет
      size_t color = 0;
      for(auto& [u, adjList] : g.adj) {
        if(!colors[u]) {
          colors[u] = ++color; // создаем новый цвет
        }
        for(auto [weight,v] : adjList) {
          edges.emplace_back(weight, u,v);
        }
      }
      sort(begin(edges), end(edges));
      for(auto& [weight, u,v] : edges) {
        if(colors[u] != colors[v]) {
          MST.emplace_back(u,v);
          Union(u,v);
        }
      }
    }

    vector<pair<T,T>> getMST() {
      Do();
      return MST;
    }

  };
}