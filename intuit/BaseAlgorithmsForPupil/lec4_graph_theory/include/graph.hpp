#pragma once

#include <bits/stdc++.h>

using namespace std;

namespace lec4 {
  template<typename T>
  struct Graph {
    unordered_map<T, vector<T>> adjList;

    void add(T u, T v) {
      adjList[u].push_back(v);
    }
  };
}
template<typename T>
std::istream & operator>>(istream& in, lec4::Graph<T>& g) {
  size_t n,m;
  in >> n >> m;
  while(m--) {
    T u,v;
    in >> u >> v;
    g.add(u,v);
  }
  return in;
}

template<typename T>
std::ostream & operator<<(std::ostream& out, const lec4::Graph<T>& dg) {
  for(auto u : dg.adjList) {
    out << u << ":";
    for(auto v : dg.adjList.at(u))
      out << v << ",";
  }
  return out;
}