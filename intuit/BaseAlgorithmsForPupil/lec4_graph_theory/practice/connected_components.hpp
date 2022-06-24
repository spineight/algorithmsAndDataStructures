#pragma once

#include <bits/stdc++.h>
#include <practice/graph.hpp>

using namespace std;

namespace lec4::practice {
  /**
   * Дан неориентированный граф G с n вершинами и m рёбрами.
   * Требуется найти в нём все компоненты связности, т.е. разбить вершины графа на несколько групп так,
   * что внутри одной группы можно дойти от одной вершины до любой другой, а между разными группами — пути не существует.
   * @attention Этот алгоритм работает только для неориентированного графа!
   */
  struct ConnectedComponents {
    const Graph<size_t> &g;
    unordered_map<size_t, size_t> colors;
    ConnectedComponents(const Graph<size_t> &g) : g(g) {}


    //! раскраска компонентов в цвета
    //! @returns количество компонент
    size_t find_components() {
      size_t color = 0;
      for(auto [u, adjList] : g.adjList) {
        if(!colors[u]) {
          ++color;
          dfs(u,color);
        }
      }
      return color;
    }

    //! @param u
    //! @param component_color
    void dfs(size_t u, size_t color) {
      colors[u] = color;
      for(auto v : g.adjList.at(u)) {
        if(!colors[v])
          dfs(v,color);
      }
    }

    map<size_t, set<size_t>> get_components() {
      find_components();
      map<size_t, set<size_t>> components;
      for(auto [u, adjList] : g.adjList) {
        components[colors[u]].insert(u);
      }
      return components;
    }
  };

}