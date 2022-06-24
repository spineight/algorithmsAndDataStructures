#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec3::practice {
// Задача о рюкзаке и золотых слитках
// У каждого слитка есть какой-то вес W[i] и стоимость V[i]
// Известно, что мы можем унести не больше A кг
// Задача унести как можно больше по стоимости но при этом не надорваться


//! @param w - вектор весов
//! @param v - вектор стоимости
//! @param A - вместимость рюкзака
//! @returns Максимальную стоимость, которую можно набрать из заданных слитков, таких что их все <= A
  int knapsack(const std::vector<size_t> &w, const std::vector<int> &v, size_t A) {
    const size_t n = w.size();
    vector<vector<int>> a(n+1, vector<int>(A+1,0));
    for(size_t i = 1; i <= n; ++i) {
      for(size_t j = 1; j <= A; ++j) {
        size_t idx = i-1;
        a[i][j] = a[i-1][j];
        if(j >= w[idx]) a[i][j] = max(a[i][j], a[i-1][ j-w[idx] ] + v[idx]);
      }
    }
    return a[n][A];
  }
}