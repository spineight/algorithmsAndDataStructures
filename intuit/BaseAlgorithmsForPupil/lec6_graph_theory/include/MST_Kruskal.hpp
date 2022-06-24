#pragma once
#include <include/graph.hpp>

namespace lec6 {
  /**
 * Идея - сначала у нас лес из пней
 * Жадно берем очередное ребро наименьшего веса, если это ребро разреза(имеет концы разных цветов) - добавляем его в MST,
 * красим
 * @tparam T
 */
  template<typename T>
  struct MST_Kruskal {
    const WeightedGraph<T>& g;
    vector<pair<T,T>> MST;
    unordered_map<T, size_t> colors;

    //!@attention Наивная реализация (TODO - использовать систему непересекающихся множеств для O(1))
    void Union(T u, T v) {
      size_t colorU = colors[u];
      for(auto& [i, color] : colors) {
        if(color == colors[v])
          color = colorU;
      }
    }

    MST_Kruskal(const WeightedGraph<T>& g) : g(g) {}

    void Do() {

      vector<tuple<size_t, T,T>> edges;

      //! изначально лес из пней, каждый из которых покрашен в свой цвет
      size_t color = 0;
      for(auto [v, adjList] : g.adj) {
        if(!colors[v]) // если пень еще не красили, создаем новый цвет
          colors[v] = ++color;
        for(auto [weight, u] : adjList) {
          edges.emplace_back(weight,v,u);
        }
      }

      sort(begin(edges), end(edges));

      for(auto [weight, u,v] : edges) {
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