//! https://codeforces.com/edu/course/2/lesson/3/4/practice/contest/272262/problem/C
#include <bits/stdc++.h>
using namespace std;

vector<int> zFn(const string& s) {
  vector<int> z(s.size(),0);
  int l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r >= i) z[i] = min(z[i-l], r-i+1);
    while(i+z[i] < s.size() && s[i+z[i]] == s[z[i]]) ++z[i];
    if(r < i + z[i] - 1) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

//! abacaba
//! a       4
//! ab      2
//! aba     2
//! abac    1
//! abaca   1
//! abacab  1
//! abacaba 1
//  3010301
vector<int> solveSlow(const string& s) {
  vector<int> res(s.size(),1);
  auto z = zFn(s);
  for(int i = 1; i < s.size(); ++i) {
    for(int j = 0; j < z[i]; ++j) ++res[j];
  }
  return res;
}

//! Я улучшил solveSlow которое не проходило по времени
//! Первоначальная идея:
//!     abacaba
//! z   0010301
//! Заметим, что кол-во вхождений префикса строки S длины 1 в строке == кол-во всех значений Z больших 0
//! Префиксов длины 2 == кол-во всех значений Z больших 1
//! Префиксов длины k == кол-во всех значений Z больших k-1
//! Осталось эффективно их посчитать, превоначальная реализация работала за n^2 и не проходила по времени
//! Наблюдение:
//! Посчитаем кол-во значений z больших нуля, тем самым для каждого префикса данной длины посчитаем кол-во его вхождений в строке
//!          0 1 2 3 4 5 6
//! res[] =  2     1         -> у нас индексация с 0, поэтому ++res[z[i]-1];
//!                           в 0 индексе кол-во вхождений в строку префиксов длины 1
//! из подсчета видим, что у нас 2 вхождения префикса длины 1, и одно вхождение префикса длины 3
//! заметим, что префикс большой длины, так же содержит в себе префикс меньшей длины
//! Получается префикс меньшей длины учавствует +1 в подсчете для всех префиксов меньшей длины, таким образом:
//! res[k] = res[k] + res[k+1] + res[k+2] + ... + res[n]

vector<int> solve(const string& s) {
  vector<int> res(s.size(),0);
  auto z = zFn(s);
  for(int i = 1; i < s.size(); ++i) {
    if(z[i] > 0)
      ++res[z[i]-1];
  }
  for(int j = res.size()-2; j>=0; --j) {
    res[j] += res[j+1];
  }
  for(auto& r: res) ++r;
  return res;
}

int main() {
  int t;
  cin >> t;
  while(t--) {
    string s;
    cin >> s;
    auto res = solve(s);
    for(auto r : res) cout << r << ' ';
    cout << '\n';
  }
  return 0;
}