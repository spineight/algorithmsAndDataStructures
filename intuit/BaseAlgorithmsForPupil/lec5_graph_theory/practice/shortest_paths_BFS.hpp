#pragma once
#include <bits/stdc++.h>
using namespace std;
#include <practice/graph.hpp>

namespace lec5::practice {

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
    unordered_map<T, size_t> distTo;
    unordered_map<T, T> parent;
    T startVertexUsedForBFS;
    void BFS(T s) {
      startVertexUsedForBFS = s;
      constexpr size_t INF = numeric_limits<size_t>::max();
      for(auto [v, adj] : g.adj) {
        distTo[v] = INF;
        parent[v] = v;
        for(auto u : adj) {
          distTo[u] = INF;
          parent[u] = u;
        }
      }
      queue<T> q;
      q.push(s);
      distTo[s] = 0;
      while(!q.empty()) {
        T v = q.front();
        q.pop();
        if(g.adj.find(v) != g.adj.end()) {
          for(auto u : g.adj.at(v)) {
            if(distTo[u] > distTo[v] + 1) {
              distTo[u] = distTo[v] + 1;
              parent[u] = v;
              q.push(u);
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
      if(distTo[t] != numeric_limits<size_t>::max())
        return (long long)distTo[t];
      return -1;
    }
    /**
     *
     * @param s
     * @param t
     * @return возвращает наикратчайщий путь, или пустой массив если такого пути не существует
     * @attention Для того, чтобы получить путь от s - BFS должен быть вызван с параметром s
     */
    vector<T> get_shortest_path(T s, T t) {
      if(distTo[t] == numeric_limits<size_t>::max())
        return {};
      vector<T> reversedPath;
      T i = t;
      while(i != s) {
        reversedPath.push_back(i);
        i = parent[i];
      }
      reversedPath.push_back(s);
      reverse(begin(reversedPath), end(reversedPath));
      return reversedPath;
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