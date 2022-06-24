#pragma once

#include <bits/stdc++.h>

namespace lec4 {
  /** Для хранения графа используем мультистек
   *
   *   В стеке head[u] - храним список вершин соседей u,
   *   так как порядок не важен, то добавляем в голову (O(n))
   */
  template<size_t MAX_V>
  struct Graph {
    Graph() : nOfEdges(0) {
      memset(dest, 0, sizeof(dest));
      memset(next, 0, sizeof(next));
      memset(head, 0, sizeof(head));
    }
    //! Максимальное количество ребер V*(V-1)/2
    //! Но так как граф ненаправленный, то мы каждое ребро добавим дважды: u-v, v-u
    static constexpr size_t MAX_E = MAX_V*(MAX_V-1)/2 * 2;

    //! dest - аналог масива value
    size_t dest[MAX_E+1];
    //! для хранения стека
    size_t next[MAX_E+1];
    //! head[u] - голова стека содержащего вершины соседи вершины u
    size_t head[MAX_V+1];
    //! Используем для присвоения id элементам мульти стека, аналог free
    size_t nOfEdges;
    //! Добавить ребро u,v
    void add(size_t u, size_t v) {
      ++nOfEdges; // nOfEdges - id of current list element
      dest[nOfEdges] = v;
      next[nOfEdges] = head[u];
      head[u] = nOfEdges;
    }
  };
}

//! Нумерация вершин начинается с 1
//! Undirected graph
//! @param in: n,m followed by the list of edges
template<size_t MAX_V>
std::istream& operator>>(std::istream& in, lec4::Graph<MAX_V>& dg) {
  size_t N,M;
  //! N - кол-во вершин
  //! M - кол-во ребер
  in >> N >> M;
  while(M--) {
    size_t u,v;
    in >> u >> v;
    dg.add(u,v);
    dg.add(v,u);
  }
  return in;
}

//! @example "1:2, 2:3,1, 3:2, "
template<size_t MAX_V>
std::ostream & operator<<(std::ostream& out, const lec4::Graph<MAX_V>& dg) {
  //! Нумерация вершин начинается с 1
  for(size_t i = 1; i <= MAX_V; ++i) {
    if(dg.head[i]) { // если голова списка существует, значит из вершины с idx u есть исходящие ребра
      out << i << ":";
      size_t j = dg.head[i];
      while(j) { // выводим i-ый список
        out <<  dg.dest[j] << ","; // выводим ребро начинающееся вершине i
        j = dg.next[j]; // переходим к следующему элементу списка
      }
      out << ' ';
    }
  }
  return out;
}