#pragma once

#include <bits/stdc++.h>

using namespace std;

namespace lec3::practice {

// Черепашка живет в узлах прямоугольной сетки размера m x n в верхнем левом углу, с координатамми (0,0)
// она хочет добраться в правый нижний угол (координаты (m,n))
//
//  (0,0)       n
//   -------------------------
//   |     |     |     |     |
//   |     |     |     |     |
//   -------------------------
// m |     |     |     |     |
//   |     |     |     |     |
//   -------------------------
//   |     |     |     |     |
//   |     |     |     |     | (m,n)
//   -------------------------
//
// Она умеет ходить только в двух направлениях: вниз и вправо
// Сколько способов добраться из точки (0,0) в точку (m,n) ?


  //! @returns Сколькими способами можно добраться из (0,0) -> (m,n)
  //! @param m - номер строки
  //! @param n - номер столбца
  size_t turtle(size_t m, size_t n) {
    vector<vector<size_t>> a(m+1, vector<size_t>(n+1,0));
    a[0][0] = 1;
    for(size_t i = 0; i <= n; ++i) {
      for(size_t j = 0; j <= m; ++j) {
        if(i > 0) a[j][i] += a[j][i-1];
        if(j > 0) a[j][i] += a[j-1][i];
      }
    }
    return a[m][n];
  }

//! Когда у нас в узлах решетки монеты и нужно собрать max:
//! @returns Последовательность ячеек по которым нужно пройти, чтобы собрать MAX денег
//! По прежнему нужно добраться из левого верхнего в правый нижний угол
  vector<std::pair<int, int> >
  turtle_and_money(size_t m, size_t n, const vector<std::vector<int> > &money) {
    vector<vector<int>> a(m+1, vector<int>(n+1,0));
    a[0][0] = money[0][0];
    for(size_t i = 0; i <= n; ++i) {
      for(size_t j = 0; j <=m; ++j) {
        if(i > 0 && j > 0) a[j][i] = max(a[j][i-1], a[j-1][i]) + money[j][i];
        else if(i > 0) a[j][i] = a[j][i-1] + money[j][i];
        else if(j > 0) a[j][i] = a[j-1][i] + money[j][i];
      }
    }
    vector<std::pair<int, int> > idxs;
    size_t j{m}, i{n};
    while(j || i) {
      idxs.emplace_back(j,i);
      if(i > 0 && j > 0) {
        if(a[j][i-1] > a[j-1][i]) --i;
        else --j;
      }
      else if( i > 0) --i;
      else if(j > 0) --j;
    }
    idxs.emplace_back(0,0);
    reverse(begin(idxs), end(idxs));
    return idxs;
  }
}