#pragma once
#include <bits/stdc++.h>
using namespace std;
#include <include/graph.hpp>

namespace lec5 {

  /**
   *  Находим кратчайшие пути в невзвешенном графе(все ребра одинакого веса) от заданной вершины s до остальных вершин
   * @tparam T
   *
   */
  template<typename T>
  struct ShortestPathsBFS {
    const Graph<T>& g;
    ShortestPathsBFS( const Graph<T>& g) : g(g), startVertexUsedForBFS(-1) {}

    // shortest paths
    enum {UNKNOWN=-1};
    unordered_map<T, long long> dist;
    unordered_map<T, T> parent;
    T startVertexUsedForBFS;
    void BFS(T s) {
      //! Для того, чтобы иметь возможность перезапускать с разными стартовыми вершинами - обнуляем состояние
      dist.clear();
      parent.clear();

      startVertexUsedForBFS = s;

      for(auto [u, adj_list] : g.adj) {
        dist[u] = UNKNOWN;
        //! @attention Если из вершины нет исходящих ребер, то ее не будет в adj_lists в качестве ключа
        //! поэтому мы дополнительно проходим каждый из списков смежности
        for(auto v : adj_list)
          dist[v] = UNKNOWN;
      }

      dist[s] = 0;
      std::queue<T> q;
      q.push(s);
      while(!q.empty()) {
        T u = q.front(); q.pop();
        if(g.adj.find(u) != g.adj.end()) {
          for(auto v : g.adj.at(u)) {
            if(dist.at(v) == UNKNOWN) {
              dist[v] = dist[u] + 1;
              q.push(v);
              parent[v] = u;
            }
          }
        }
      }
    }
    /**
     *
     * @param s - начальная вершина
     * @param t - конечная вершина
     * @return длину пути между вершинами или -1 если вершина t недостяжима из s
     * @attention Для того, чтобы получить длину пути от s - BFS должен быть вызван с параметром s
     */
    long long get_dist(T s, T t) {
      assert(startVertexUsedForBFS == s);
      return dist[t];
    }
    /**
     *
     * @param s
     * @param t
     * @return возвращает наикратчайщий путь, или пустой массив если такого пути не существует
     * @attention Для того, чтобы получить путь от s - BFS должен быть вызван с параметром s
     */
    vector<T> get_shortest_path(T s, T t) {
      if(dist[t] == UNKNOWN) return {};

      vector<T> result = {t};
      T i = t;
      while(i != s) {
        i = parent[i];
        result.push_back(i);
      }
      reverse(begin(result), end(result));
      return result;
    }
  };
















  //! Оставил, вдруг понадобится, я использую более простое представление графа
  struct [[deprecated]]GraphBFSStankevich {
    GraphBFSStankevich() : nOfEdges(0) {
      memset(head,0,sizeof(head));
      memset(next,0,sizeof(next));
      memset(dest,0,sizeof(dest));
    }
    static const size_t MAX_V = 100;
    static const size_t MAX_E = MAX_V * MAX_V;
    int head[MAX_V];
    int next[MAX_E];
    int dest[MAX_E];
    int nOfEdges;
    void add(int u, int v) {
      ++nOfEdges;
      dest[nOfEdges] = v;
      next[nOfEdges] = head[u];
      head[u] = nOfEdges;
    }
    // shortest paths
    int dist[MAX_V];
    int from[MAX_V];
    void BFS(int s) {
      std::fill(std::begin(dist), std::end(dist), -1);
      dist[s] = 0;
      std::queue<int> q;
      q.push(s);
      while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int j = head[u]; j != 0; j = next[j]) {
          int v = dest[j];
          if(dist[v] == -1) {
            dist[v] = dist[u] + 1;
            q.push(v);
            from[v] = u;
          }
        }
      }
    }
    int distance(int s, int t) {
      BFS(s);
      return dist[t];
    }
    void print_shortest_path(int s, int t) {
      if(s != t) print_shortest_path(s, from[t]);
      std::cout << t << "-->";
    }
    void shortest_path(int s, int t) {
      BFS(s);
      print_shortest_path(s,t);
    }

  };
}