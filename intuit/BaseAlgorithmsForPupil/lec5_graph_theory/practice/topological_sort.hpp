#pragma once
#include <bits/stdc++.h>
using namespace std;
#include <practice/graph.hpp>

namespace lec5::practice {
  /**
   *   Пусть есть ациклический ориентированный граф.
   *     Тогда утверждается следующее: его вершины можно занумеровать (присвоить им номера) в таком порядке,
   *     что ребра будут идти только из вершин с меньшими номерами в вершины с большими номерами.
   */
  template<typename T>
  struct TopSort {
    const Graph<T>& g;
     //!@param g g - DAG(Directed Acyclic Graph), заданный списками смежности
    TopSort(const Graph<T>& g) : g(g), isCycle(false) {}
    vector<T> exitOrder;
    enum Color{WHITE,GREY,BLACk};
    unordered_map<T,Color> colors;
    bool isCycle;

    /**
     * @param u
     * @return true - если существует топологическая сортировка, false - найден цикл и Топ сорт не существует
     */
    bool topSortImpl(T u) {
      colors[u] = GREY;
      if(g.adj.find(u) != g.adj.end()) {
        for(auto v : g.adj.at(u)) {
          if(colors[v] == WHITE)
            if(!topSortImpl(v)) return false;
          if(colors[v] == GREY) return false;
        }
      }
      exitOrder.push_back(u);
      colors[u] = BLACk;
      return true;
    }
    //! @returns true - если существует топологическая сортировка, false - найден цикл и Топ сорт не существует
    bool topSort() {
      vector<T> vertexes;
      for(auto [v, adjLists] : g.adj) {
        vertexes.push_back(v);
        for(auto u : adjLists) {
          vertexes.push_back(u);
        }
      }
      isCycle = false;
      for(auto v : vertexes) {
        if(colors[v] == WHITE) {
          if(!topSortImpl(v)) {
            isCycle = true;
            break;
          }
        }
      }
      return !isCycle;
    }
    vector<T> getTopSort() const {
      if(isCycle)
        return {};
      vector<T> result{rbegin(exitOrder),rend(exitOrder)};
      return result;
    }

  };







  //! Писал раньше, решил оставить, чтобы смотреть как можно использовать статические листы для хранения графа
  //! Не использую в практике, так как долго писать (использую более простое представление графа)
  struct [[deprecated]] GraphStankevich {
    GraphStankevich() : nOfEdges(0) {
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
    int colors[MAX_V];
    // topsort
    std::vector<size_t> top_order;
    bool dfs_is_cycle(size_t u) {
      colors[u] = gray;
      for(size_t i = head[u]; i !=0; i = next[i]) {
        size_t v = dest[i];
        if(colors[v] == white) {
          if(dfs_is_cycle(v)) return true;
        }
        else if (colors[v] == gray) {
          return true;
        }
      }
      colors[u] = black;
      top_order.push_back(u);
      return false;
    }
    std::vector<size_t> top_sort() {
      bool is_cycle = false;
      // look at readme for the lecture - we observed that
      // running from virtual vertex 0(which we connected to all graph vertexes) is same as:
      for(size_t i = 1; i < MAX_V && !is_cycle; ++i) {
        if(!head[i]) continue;
        if(colors[i] == white) {
          if(dfs_is_cycle(i))
            is_cycle = true;
        }
      }
      if(is_cycle) return {};
      std::reverse(begin(top_order), end(top_order));
      return top_order;
    }
  } ;
}