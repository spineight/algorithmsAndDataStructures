#pragma once

#include <bits/stdc++.h>
using namespace std;

namespace algos {
  //! https://codeforces.com/group/pgkaqF4igo/contest/256214/problem/B

//  Дано число n. Выведите все числа, на которые оно делится.
//  Входные данные
//
//  Ввод содержит число n (1 ≤ n ≤ 1010).
//  Выходные данные
//
//  Выведите все делители числа n в порядке возрастания.
//  Пример
//          Входные данные
//          Скопировать
//
//  10
//
//  Выходные данные
//
//  1
//  2
//  5
//  10
  void solve_divisorsB() {
    long long n;
    cin >> n;
    vector<long long> res;
    for (long long i = 1; i * i <= n; ++i) {
      if(n % i == 0) {
        res.push_back(i);
        if(n/i != i)
          res.push_back(n / i);
      }
    }
    sort(begin(res), end(res));
    for(auto& v : res) cout << v << ' ';
    cout << '\n';
  }

  //! https://codeforces.com/group/pgkaqF4igo/contest/256214/problem/D
//  По введенному числу n выведите его разложение на простые множители в порядке возрастания.
//  Входные данные
//
//  В единственной строчке записано число n (1 ≤ n ≤ 1010), которое необходимо разложить на простые множители.
//  Выходные данные
//
//  Выведите в одной строке последовательность простых чисел ai таких что их произведение равно n и при этом ai ≤ ai + 1
//  Пример
//          Входные данные
//  10
//
//  Выходные данные
//  2
//  5
  void solve_factorizationD() {
    long long n;
    cin >> n;
    vector<long long> res;
    //! Если a - min делитель числа n, то a - простое
    //! предположим, что это не так a не простое и тогда a = p * q
    //! но тогда получаем противоречие, что a наименьшее число

    for(long long i = 2; i*i <= n; ++i) {
      while(n % i ==0) {
        n /= i;
        cout << i << ' ';
      }
    }

    if(n > 1)
      cout << n;
    cout << '\n';
  }

  //! https://codeforces.com/group/pgkaqF4igo/contest/256214/problem/E
  void solve_rectangularGameE() {
    long long n;
    cin >> n;
    long long result  = n;
    for(long long i = 2; i * i <= n; ++i) {
      while(n % i == 0) {
        result += n / i;
        n /= i;
      }
    }
    if(n > 1) ++result;
    cout << result << '\n';
  }
}