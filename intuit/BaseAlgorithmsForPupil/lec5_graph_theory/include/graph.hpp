#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec5 {
  //! @attention нет поддержки независимой вершины (которая не связанна хотябы с одной другой)
  template<typename T>
  struct Graph {
    unordered_map<T, vector<T>> adj;

    void add(T u, T v) {
      adj[u].push_back(v);
    }
  };

  template<typename T>
  struct WeightedGraph {
    unordered_map<T/*u*/, vector< pair<size_t/*weight*/,T /*v*/>> > adj;

    void add(T u, T v, size_t weight) {
      adj[u].emplace_back(weight,v);
    }
  };
}
