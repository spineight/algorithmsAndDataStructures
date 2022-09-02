#include <bits/stdc++.h>
using namespace std;


//! Длиной периода строки S называется такое минимальное число к
//! Что строка S представима в виде конкатенации нескольких копиий префикса длины k
//! Примеры: s=abcabc p=abc; s=aaaaa p=a; s=abcab p = abcab
//
// Задача Step4_problemA - отличается от этой
// Там для s=abcab p=abc
//
// В этой задаче у нас проверяется доп условие, того что k должно быть делителем длины строки

vector<int> zFn(const string& s) {
  vector<int> z(s.size(),0);
  int l{0}, r{0};
  for(int i = 1; i < s.size(); ++i) {
    if(r >= i) {
      z[i] = min(z[i-l], r-i+1);
    }
    while(i+z[i] < s.size() && s[i+z[i]] == s[z[i]]) ++z[i];

    if(r < i + z[i]-1) {
      r = i + z[i]-1;
      l = i;
    }
  }
  return z;
}


string minPeriod(const string& s) {
  auto z = zFn(s);
  for(int i = 1; i < s.size(); ++i) {
    if(i+z[i] == s.size() && (s.size() % i) == 0) return s.substr(0,i);
  }
  return s;
}

int main() {
  cout << minPeriod("abcab") << '\n'; // abcab
  cout << minPeriod("abab") << '\n'; // ab
  cout << minPeriod("aaaa") << '\n'; // a
  cout << minPeriod("abacaba") << '\n'; // abacaba
  cout << minPeriod("ababa") << '\n'; // ababa
  cout << minPeriod("ababab") << '\n'; // ab
  return 0;
}