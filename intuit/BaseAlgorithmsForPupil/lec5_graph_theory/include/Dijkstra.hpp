#pragma once

#include <bits/stdc++.h>
using namespace std;

#include <include/graph.hpp>

namespace lec5 {

  /**
   * Я использую реализацию с сайта e-maxx(file:///home/oleg/e-maxx/Нахождение кратчайших путей от заданной вершины до всех остальных вершин алгоритмом Дейкстры)
   *
   * Станкевич в лекции не дает реализацию, но дает идеи
   *
   * Работает за `n^2`
   * И решает задачу о кратчайших путях из одной вершины для взвешенного неотрицательного графа (веса неотрицательные)

   * У нас корректность обхода в ширину для невзвешеннго графа основывалась на том, что вершинки из очереди достаются
   * в порядке возростания растояния до них и кладутся в этом порядке.
   * Обычная очередь нам теперь не подходит, нужно, на самом деле, использовать приоритетную очередь,
   * не будем использовать сложную Heap реализацию, мы будем использовать простую(наивную) реализацию приоритетной очереди -
   * приоритетная очередь на массиве.

      Алгоритм Дейкстры действует:
      Все вершины делятся на два множества: помеченные и не помеченные,
      помеченные U - до них нам уже известно правильное расстояние.
      Шаг алгоритма Дейкстры - берется непомеченная вершина у которой минимальная текущая гипотеза расстояния
      у каждой вершины хранится в массиве `d[u]` - за сколько мы умеем до нее доходить (такая гипотеза)
      она помечается и по всем ребрам которые ведут из этой вершины проводится операция которая называется - релаксация,
      мы смотрим, а что лучше то как мы раньше умели ходить до этой вершины или через вершину u и минимум из этих двух
      запоминаем.
   */
  template<typename T>
  struct ShortestPathsDijkstra {
    const WeightedGraph<T>& g;
    ShortestPathsDijkstra(const WeightedGraph<T>& g) : g(g) {}

    unordered_map<T, size_t> dist;
    unordered_map<T, bool> marked;
    unordered_map<T,T> parent;
    void Dijkstra(T s) {
      marked.clear();

      constexpr size_t INF = numeric_limits<size_t>::max();
      // Для удобства, составим список всех используемых вершин
      // В дальнейшем он нам пригодится, чтобы просматривать все вершины
      // Такая необходимость, так как мы храним в std::unordered_map
      // где ключ появляется только если есть из вершины исходящие ребра, если нет - ее не будет среди ключей
      set<T> vertexes;
      for(auto [u, adjList] : g.adj) {
        vertexes.insert(u);
        //! Проходим по списку смежности, так как если нет исходящих ребер из вершине - она не будет среди ключей в g.adj
        //! но при этом нам нужно установить значения для всех вершин
        for(auto [weight, v] : adjList)
          vertexes.insert(v);
      }

      for(auto v : vertexes) {
        dist[v] = INF;
        parent[v] = v;
      }

      dist[s] = 0;

      while(1) {
        T idx_min_dist = -1;
        // Ищем вершину с минимальной гипотезой расстояния до нее среди всех непомеченных вершин
        for(auto v : vertexes) {
          if(!marked[v] && (idx_min_dist == -1 || dist[idx_min_dist] > dist[v]))
            idx_min_dist = v;
        }
        if(idx_min_dist == -1 || dist[idx_min_dist] == INF)
          break;

        marked[idx_min_dist] = true;
        // просматриваем все вершины достижимые из нее и если нужно обновляем для них гипотезу расстояния (реклаксация)
        if(g.adj.find(idx_min_dist) != g.adj.end()) // есть исходящие ребра
        {
          for(auto [weight,u] : g.adj.at(idx_min_dist)) {
            if(dist[u] > dist[idx_min_dist] + weight) {
              dist[u] = dist[idx_min_dist] + weight;
              parent[u] = idx_min_dist;
            }
          }
        }
      }
    }
    //! @returns length of the shortest path from s to t, or -1 if no such path
    long long getShortestPathLen(T t) {
      if(!marked[t]) return -1;
      return static_cast<long long>(dist[t]);
    }
    //! @returns the shortest path from s to t, or empty vector if no such path
    vector<T> getShortestPath(T t) {
      vector<T> path;
      T i = t;
      path.push_back(t);
      while(i != parent[i]) {
        i = parent[i];
        path.push_back(i);
      }
      reverse(begin(path), end(path));
      return path;
    }
  };
}
