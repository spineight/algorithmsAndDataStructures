#pragma once

#include <bits/stdc++.h>

namespace lec4::practice {
  /** Для хранения графа используем мультистек
   *
   *   В стеке head[u] - храним список вершин соседей u,
   *   так как порядок не важен, то добавляем в голову (O(n))
   */
  template<size_t MAX_V>
  struct Graph {
    size_t head[MAX_V+1];
    static constexpr size_t MAX_E = MAX_V * (MAX_V-1);
    size_t next[MAX_E+1];
    size_t dest[MAX_E+1];
    size_t nOfEdges;
    Graph() : nOfEdges(0) {
      memset(head,0,sizeof(head));
      memset(next,0,sizeof(next));
      memset(dest,0,sizeof(dest));
    }
    //! Добавить ребро u,v
    void add(size_t u, size_t v) {
      ++nOfEdges;
      next[nOfEdges] = head[u];
      head[u] = nOfEdges;
      dest[nOfEdges] = v;
    }
  };
}

//! Нумерация вершин начинается с 1
//! Undirected graph
template<size_t MAX_V>
std::istream& operator>>(std::istream& in, lec4::practice::Graph<MAX_V>& g) {
  size_t n,m;
  in >> n >> m;
  while(m--) {
    size_t u,v;
    in >> u >> v;
    g.add(u,v);
    g.add(v,u);
  }
  return in;
}

//! @example "1:2, 2:3,1, 3:2, "
template<size_t MAX_V>
std::ostream & operator<<(std::ostream& out, const lec4::practice::Graph<MAX_V>& g) {
  for(size_t u = 1; u <= MAX_V; ++u) {
    if(g.head[u]) {
      out << u <<":";
      size_t v = g.head[u];
      while(v) {
        out << g.dest[v] << ",";
        v = g.next[v];
      }
      out << " ";
    }
  }
  return out;
}