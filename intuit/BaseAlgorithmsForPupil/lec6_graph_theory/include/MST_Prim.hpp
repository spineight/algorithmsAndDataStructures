#pragma once
#include <bits/stdc++.h>
using namespace std;
#include <include/graph.hpp>

namespace lec6 {
  template<typename T>

  /**
   * Идея: мы растим одно дерево MST
   * Вершины у нас делятся на два множества которые в MST и которые нет, вершины в MST помечены как marked
   *
   * Шаг алгоритма:
   * Находим такое ребро минимального веса, ребро разреза, что оно соединяет вершину в MST и вне этого множества
   * Добавляем его в MST, помечаем marked
   * В результате добавление новой вершины в MST - у нас возможно появляются новые ребра разреза из этой вершины в ее соседей
   * Мы обновляем расстояние до этих вершин, как результат возможно нахождение нового ребра разреза минимального веса
   * @tparam T
   * @attention Этот алгоритм подходит только для неориентированного графа (https://codeforces.com/blog/entry/20079)
   * @attention Граф должен быть связанный
   * @attention Время работы: https://neerc.ifmo.ru/wiki/index.php?title=Алгоритм_Прима
   * @attention Это наивная реализация
   * @tparam T
   */
  struct MST_Prim {
    const WeightedGraph<T>& g;
    //! Ребро разреза минимального веса соединяющее вершину u множества U(marked) и вершину v не из этого множества
    unordered_map<T, size_t> dist;
    //! from[v] = u - значит ребро u--v минимального веса разреза, где u во множестве marked, v не пренадлежит этом множеству
    unordered_map<T,T> from;
    //! marked[u] = true - значит, что допустимое остовное дерево стягивает вершину u
    unordered_map<T, bool> marked;
    //! ребра MST, которое мы строим (результат)
    vector<pair<T, T>> MST;
    static constexpr size_t INF = numeric_limits<size_t>::max();
    MST_Prim(const WeightedGraph<T>& g) :g(g) {

    }

    //! Алгоритм один в один с алгоритмом Дейкстры для поиска минимальных путей, есть два отличия
    void Do() {
      marked.clear();

      for(auto [v, adjList] : g.adj) {
        dist[v] = INF; // так как граф неориентированный, вершина будет в ключе если у нее есть ребро
      }

      // нужно выбрать стартовую вершину, подойдет любая, так как в итоге они все должны попасть в дерево
      const T startV{g.adj.begin()->first};
      dist[startV] = 0;

      while(1) {
        T bestV = -1;
        for(auto [v,d] : dist) {
          if(!marked[v] && (bestV == -1 || dist[bestV] > dist[v])) {
            bestV = v;
          }
        }
        if(bestV == - 1 || dist[bestV] == INF) break;

        marked[bestV] = true;
        //! Отличие от алгоритма Дейкстры
        // "на первом шаге когда v=s не нужно добавлять"
        // для первой найденной вершины MST мы еще не можем добавить ребро, ждем пока появится вторая
        if(bestV != startV)
          MST.emplace_back(from[bestV], bestV);


        // посмотрим, возможно у нас в кандидатах появилась вершина до которой расстояние от нашего дерево еще меньше
        // чем сейчас
        if(g.adj.find(bestV) != g.adj.end()) {
          for(auto [weight, u] : g.adj.at(bestV)) {
            if(dist[u] > weight) {
              //! Отличие от алгоритма Дейкстры
              dist[u] = weight;
              from[u] = bestV;
            }
          }
        }
      }
    }
    vector<pair<T, T>> getMST() {
      Do();
      return MST;
    }

  };
}