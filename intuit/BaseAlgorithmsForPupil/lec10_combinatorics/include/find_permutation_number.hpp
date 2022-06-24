#pragma once

#include <vector>
using namespace std;

namespace lec10_combinatorics {

  // нужно найти номер перестановки по перестаноке
  size_t find_permutation_number(const std::vector<int>& a) {
    const int n = a.size();
    vector<long long> factorial(n+1,1);
    for(int i = 1; i < n; ++i)
      factorial[i] = factorial[i-1]*i;

    vector<char> used(n+1,0);
    // Решаем в обратном порядке задачи find_kth_permutation
    size_t res = 0;
    for(int i = 1; i <= n; ++i) {
      int cnt = 0;
      int j = 1;
      // находим номер блока
      for(; j != a[i-1]; ++j) {
        if(!used[j]) ++cnt;
      }
//      std::cout << "a[i-1]:" << a[i-1] << ", cnt:" << cnt << '\n';
      used[j] = 1;
      res += factorial[n-i] * cnt;
    }
    return res+1;
  }
}