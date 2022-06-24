#pragma once

#include <bits/stdc++.h>
using namespace std;

#include <include/graph.hpp>

namespace lec5 {



  template<typename T, size_t IS_DIRECTED_GRAPH = 1>
  struct CycleDetection {
    const Graph<T>&g;
    CycleDetection(const Graph<T>&g) :g(g) {}
    enum Color {WHITE, GRAY, BLACK};
    unordered_map<T, Color> colors;
    stack<T> callStack;
    vector<T> cycle;
    /**
     *
     *  Для неориентированного графа нужен дополнительный параметер, так как в нем для любой вершины, кроме начальной
     *     есть всегда серый сосед (родитель из которого мы в нее пришли)
    *      Поэтому добавляем условие, что назад не смотрим
     * @param u
     * @param parentOfU - родитель вершины u
     * @return true - is cycle, false otherwise
     */
    bool dfs_is_cycle(T u, T parentOfU) {
      // IN
      colors[u] = GRAY;
      callStack.push(u);

      // Так как граф может быть направленный, то нужно проверить есть ли куда идти из u (есть исходящие ребра из этой вершины)
      if(g.adj.find(u) != g.adj.end()) {
        for (auto v : g.adj.at(u)) {
          if (colors[v] == WHITE) {
            if (dfs_is_cycle(v, u)) return true;
          }
          else if (colors[v] == GRAY && ( IS_DIRECTED_GRAPH || v != parentOfU) ) {
//            cycle_start = v;
//            cycle_end = u;
            // записываем цикл
            // Как вариант у нас есть массив предков, можно использовать его ? Похоже, что нет TODO: нужно тест на это придумать
            T i = u;
            while(i != v) {
              i = callStack.top(); callStack.pop();
              cycle.push_back(i);
            }
            reverse(begin(cycle), end(cycle));
            return true;
          }
        }
      }

      // OUT (DONE)
      colors[u] = BLACK;
      callStack.pop();
      return false;
    }

    bool isCycle() {
      // look at readme for the lecture - we observed that
      // running from virtual vertex 0(which we connected to all graph vertexes) is same as having this cycle:
      for (auto [u, adj_list] : g.adj) {
        if (colors[u] == WHITE)
          if (dfs_is_cycle(u,u)) {
            return true;
          }
      }
      return false;
    }
    auto get_cycle() {
      return cycle;
    }
  };













  //! Оставил, вдруг понадобится
  // Я использую более простое представление графа
  struct [[deprecated]] GraphStankevichCycleDetection {
    GraphStankevichCycleDetection() : nOfEdges(0), cycle_start(0), cycle_end(0) {
      memset(head,0,sizeof(head));
      memset(next,0,sizeof(next));
      memset(dest,0,sizeof(dest));
      memset(colors,0,sizeof(colors));
    }
    static const size_t MAX_V = 100;
    static const size_t MAX_E = MAX_V * MAX_V;
    size_t head[MAX_V];
    size_t next[MAX_E];
    size_t dest[MAX_E];
    size_t nOfEdges;
    void add(size_t u, size_t v) {
      ++nOfEdges;
      dest[nOfEdges] = v;
      next[nOfEdges] = head[u];
      head[u] = nOfEdges;
    }
    // cycle detection
    enum Color {white, gray, black};
    size_t colors[MAX_V];
    size_t parent[MAX_V];
    size_t cycle_start, cycle_end;
    //! Для неориентированного графа нужен дополнительный параметер, так как в нем для любой вершины, кроме начальной
    //! есть всегда серый сосед (родитель из которого мы в нее пришли)
    //! Поэтому добавляем условие, что назад не смотрим
//    * @param parentOfu
//    bool topSortImpl(T u, T parentOfu)
//    else if(colors[v] == GRAY && parentOfu != v)
//    return false;
    bool dfs_is_cycle(size_t u) {
      colors[u] = gray;
      for(size_t i = head[u]; i !=0; i = next[i]) {
        size_t v = dest[i];
        if(colors[v] == white) {
          parent[v] = u;
          if(dfs_is_cycle(v)) return true;
        }
        else if (colors[v] == gray) {
          cycle_start = v;
          cycle_end = u;
          return true;
        }
      }
      colors[u] = black;
      return false;
    }
    auto get_cycle() {
      // look at readme for the lecture - we observed that
      // running from virtual vertex 0(which we connected to all graph vertexes) is same as:
      for(size_t u = 1; u <= MAX_V; ++u) {
        if(!head[u]) continue;
        if(colors[u]==white)
          dfs_is_cycle(u);
      }
      if(!cycle_start) return std::vector<size_t>();
      std::vector<size_t> cycle;
      size_t i = cycle_end;
      while(i != cycle_start) {
        cycle.push_back(i);
        i = parent[i];
      }
      cycle.push_back(cycle_start);
      std::reverse(begin(cycle), end(cycle));
      return cycle;
    }
  };
}
//std::ostream& operator<<(std::ostream& out, const  lec5::GraphStankevichCycleDetection& g) {
//  for(size_t i = 1; i < g.MAX_V; ++i) {
//    if(!g.head[i]) continue;
//    out << i << ":";
//    size_t j = g.head[i];
//    while(j) {
//      out << g.dest[j] << ",";
//      j = g.next[j];
//    }
//    out << "\n";
//  }
//  return out;
//}
