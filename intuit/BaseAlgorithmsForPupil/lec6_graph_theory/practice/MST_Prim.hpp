#pragma once
#include <bits/stdc++.h>
using namespace std;
#include <practice/graph.hpp>

namespace lec6::practice {
  template<typename T>
  //!@attention Этот алгоритм подходит только для неориентированного графа (https://codeforces.com/blog/entry/20079)
  //!@attention Граф должен быть связанный
  //!@attention Время работы: https://neerc.ifmo.ru/wiki/index.php?title=Алгоритм_Прима
  //!@attention Это наивная реализация (поиск ребра наименьшего веса за O(n))
  struct MST_Prim {
    const WeightedGraph<T>& g;
    //! from[k] = i - ребро разреза один конец которого( i пренадлежит MST которое мы строим)
    //! другой конец k - не пренадлежит    |i|---k
    unordered_map<T,T> from;
    unordered_map<T,size_t> distTo; // distTo[i] = длина ребра разреза (from[i],i)
    unordered_map<T,size_t> marked; // вершина была добавлена в MST
    static constexpr size_t INF = numeric_limits<size_t>::max();
    //! ребра MST, которое мы строим (результат)
    vector<pair<T, T>> MST;
    MST_Prim(const WeightedGraph<T>& g) :g(g) {
      for(auto& [v, adjList] : g.adj) {
        distTo[v] = INF; // так как граф неориентированный, вершина будет в ключе если у нее есть ребро
        from[v] = v;
      }
    }

    //! Алгоритм один в один с алгоритмом Дейкстры для поиска минимальных путей, есть два отличия
    void Do() {
      // нужно выбрать стартовую вершину, подойдет любая, так как в итоге они все должны попасть в дерево
      distTo[g.adj.begin()->first] = 0;
      while(1) {
        T bestV = -1;
        for(auto& [v, adjList] : g.adj) {
          if(!marked[v] && (bestV == -1 || distTo[bestV] > distTo[v])) {
            bestV = v;
          }
        }
        if(bestV == -1 || distTo[bestV] == INF)
          break;

        // для первой найденной вершины MST мы еще не можем добавить ребро, ждем пока появится вторая
        if(from[bestV] != bestV)
          MST.emplace_back(from[bestV],bestV);
        marked[bestV] = true; // вершина добавлена в MST которое мы строим

        // посмотрим, возможно у нас в кандидатах появилась вершина до которой расстояние от нашего дерево еще меньше
        // чем сейчас
        for(auto& [weight, v]: g.adj.at(bestV)) {
          if(distTo[v] > weight) {
            distTo[v] = weight;
            from[v] = bestV;
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