#pragma once
#include <bits/stdc++.h>
#include <include/graph.hpp>
using namespace std;

namespace lec4 {
  /**
   * Дан неориентированный граф G с n вершинами и m рёбрами.
   * Требуется найти в нём все компоненты связности, т.е. разбить вершины графа на несколько групп так,
   * что внутри одной группы можно дойти от одной вершины до любой другой, а между разными группами — пути не существует.
   * @attention Этот алгоритм работает только для неориентированного графа!
   */
  struct ConnectedComponents {
    const Graph<size_t>& g;
    ConnectedComponents(const Graph<size_t>& g) : g(g) {}
    unordered_map<size_t, size_t> color;

    //! раскраска компонентов в цвета
    //! @returns количество компонент
    size_t find_components() {
      size_t component_color = 0;
      for(auto [u, adjList] : g.adjList) {
        if(!color[u]) {
          ++component_color; // создаем цвет для новой компоненты
          dfs(u, component_color);
        }
      }
      return component_color;
    }

    void dfs(size_t u, size_t component_color) {
      color[u] = component_color;
      for(auto v : g.adjList.at(u)) {
        if(!color[v])
          dfs(v, component_color);
      }
    }

    map<size_t, set<size_t>> get_components() {
      map<size_t, set<size_t>> components;
      find_components();
      for(auto [key, value] : g.adjList) {
        components[color[key]].insert(key);
      }
      return components;
    }
  };

}