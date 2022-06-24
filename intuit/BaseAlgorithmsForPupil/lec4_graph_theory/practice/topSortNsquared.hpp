#pragma once
#include <bits/stdc++.h>
using namespace std;
#include <practice/graph.hpp>

namespace lec4::practice {
  /**
   * @attention Граф должен быть DAG (Directed Acyclic Graph)
   * Для того, чтобы показать, что задача пронумеровать вершины так, что вершины с меньшими номерами указывают
   * на вершины с большими - я место индексов вершин, использую char
   */
  struct TopSortNSquared {
    const Graph<char>& g;
    unordered_map<char, size_t> in_degree;
    unordered_map<char,bool> seen;
    size_t n;
    TopSortNSquared(const Graph<char>& g) : g(g) {
      set<char> vertexes;
      for(auto [v, adjList] : g.adjList) {
        vertexes.insert(v);
        if(in_degree.find(v) == in_degree.end())
          in_degree[v] = 0;
        for(auto u : adjList) {
          ++in_degree[u];
        }
      }
      n = vertexes.size();
    }
    //! @returns Массив вершин упорядоченных в порядке нумерации (vertexes[id] = v)
    //! @attention DAG (Directed Acyclic Graph) - в графе не должно быть циклов и он должен быть направленным
    vector<char> topSort() {
      vector<char> vertexes;
      for(size_t i = 0; i < n; ++i) {
        for(auto [v,degree] : in_degree) {
          if(degree == 0 && !seen[v]) {
            seen[v] = true;
            vertexes.push_back(v);
            if(g.adjList.find(v) != g.adjList.end()) {
              for(auto u : g.adjList.at(v)) {
                --in_degree[u];
              }
            }
          }
        }
      }
      return vertexes;
    }

  };
}