#pragma once

#include <bits/stdc++.h>
using namespace std;

#include <practice/graph.hpp>

namespace lec5::practice {

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
    unordered_map<T,size_t> distTo;
    unordered_map<T,bool> marked;
    unordered_map<T,T> parent;
    static constexpr size_t INF = numeric_limits<size_t>::max();
    T start;

    void Dijkstra(T s) {
      start = s;
      marked.clear();
      for(auto [v, adj] : g.adj) {
        distTo[v] = INF;
        parent[v] = v;
        for(auto [weight,u] : adj) {
          distTo[u] = INF;
          parent[u] = u;
        }
      }

      distTo[s] = 0;

      while(1) {
        T minV = -1;
        size_t bestDist = INF;
        for(auto [v, dist] : distTo) {
          if(!marked[v] && bestDist > dist) {
            bestDist = dist;
            minV = v;
          }
        }
        if(bestDist == INF) break;
        marked[minV] = true;
        if(g.adj.find(minV) != g.adj.end()) {
          for(auto [weight, u] : g.adj.at(minV)) {
            if(distTo[u] > distTo[minV] + weight) {
              distTo[u] = distTo[minV] + weight;
              parent[u] = minV;
            }
          }
        }
      }
    }
    //! @returns length of the shortest path from s to t, or -1 if no such path
    long long getShortestPathLen(T t) {
      if(distTo[t] == INF) return -1;
      return (long long)distTo[t];
    }
    //! @returns the shortest path from s to t, or empty vector if no such path
    vector<T> getShortestPath(T t) {
      if(distTo[t] == INF)
        return {};
      vector<T> back_path;
      T i = t;
      while(i != start) {
        back_path.push_back(i);
        i = parent[i];
      }
      back_path.push_back(start);
      reverse(begin(back_path), end(back_path));
      return back_path;
    }
  };
}
