#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec3::practice {
// Зоомагазин, выставляют клетки с животными (кошки и собаки)
// Кошек обозначим ноликами, собак единицами
// Подряд разрешается ставить не более двух клеток с одинаковыми животными
// [0][1][0][0][1]...[]
//       n
// Сколькими способами можно расставить n клеток
//

  size_t zoo_store(size_t n) {
    vector<vector<size_t>> a(n+1, vector<size_t>(2,0));
    if(n == 0) return a[0][0];
    a[1][0] = 1;
    a[1][1] = 1;
    if(n == 1) return a[1][0] + a[1][1];
    a[2][0] = 2;
    a[2][1] = 2;
    for(size_t i = 3; i <= n; ++ i) {
      for(size_t j = 0; j <= 1; ++j) {
        // |j|j|
        a[i][j] += a[i-2][1-j];
        // |1-j|j|
        a[i][j] += a[i-1][1-j];
      }
    }
    return a[n][0] + a[n][1];
  }
}