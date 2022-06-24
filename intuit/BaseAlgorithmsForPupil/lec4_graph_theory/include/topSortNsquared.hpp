#pragma once
#include <bits/stdc++.h>
using namespace std;
#include <include/graph.hpp>

namespace lec4 {
  /**
   * @attention Граф должен быть DAG (Directed Acyclic Graph)
   * Для того, чтобы показать, что задача пронумеровать вершины так, что вершины с меньшими номерами указывают
   * на вершины с большими - я место индексов вершин, использую char
   */
  struct TopSortNSquared {
    const Graph<char>& g;
    size_t n;
    unordered_map<char,size_t> in_degree;
    TopSortNSquared(const Graph<char>& g) : g(g) {
      set<char> vertexes;
      for(auto [u, adjList] : g.adjList) {
        vertexes.insert(u);
        if(in_degree.find(u) == in_degree.end())
          in_degree[u] = 0;
        for(auto v : adjList) {
          ++in_degree[v];
          vertexes.insert(v);
        }
      }
      n = vertexes.size();
    }
    //! @returns Массив вершин упорядоченных в порядке нумерации (vertexes[id] = v)
    //! @attention DAG (Directed Acyclic Graph) - в графе не должно быть циклов и он должен быть направленным
    vector<char> topSort() {
      vector<char> vertexes;
      unordered_map<char, bool> seen;
      // Нам нужно присвоить номер каждой из вершин
      for(size_t i = 0; i < n; ++i) {
        // Находим вершину в которую ни входит никаких других (такая обязательно будет, иначе в графе есть циклы)
        for (auto[v, degIn] : in_degree) {
          if (degIn == 0 && !seen[v]) {
            vertexes.push_back(v);
            seen[v] = true;
            // После того как ей присовили номер - вычеркиваем ее из списка вершин, и пересчитываем степень вершин,
            // в которые из нее было входящее ребро
            // Для этого пройдем по всем ребрам выходящим из этой вершины
            if(g.adjList.find(v) != g.adjList.end()) {
              for (auto u : g.adjList.at(v)) {
                --in_degree[u];
              }
            }
            break;
          }
        }
      }
      return vertexes;
    }

  };

}