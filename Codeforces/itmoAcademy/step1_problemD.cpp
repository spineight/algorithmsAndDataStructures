//! https://codeforces.com/edu/course/2/lesson/3/1/practice/contest/272260/problem/D
#include <bits/stdc++.h>
using namespace std;

vector<int> getPositions(const string& s, const string& t) {
  if(s.size() > t.size()) return {};
  vector<int> positions;
  for(int i = 0; i < t.size()-s.size()+1;++i) {
    int soFar{0};
    while(soFar < s.size() && s[soFar] == t[i+soFar]) ++soFar;
    if(soFar == s.size()) positions.push_back(i);
  }
  return positions;
}

// 0. Наблюдение
// Число всех возможных подстрок длины k = k * (k + 1) / 2
// Чтобы их сгенерить мы перебераем все возможные упорядоченные пары индексов [i,j] - первый, последний элементы строки
// Для строки длины 4:
// 0  :  0 1 2 3     - 4
// 1  :  1 2 3       - 3
// 2  :  2 3         - 2
// 3  :  3           - 1
// Всего будет сгенирировано 1+2+3+4 строк, сумму можно найти по формуле k*(k+1)/2
vector<string> generateAllSubstrings(const string& s) {
  vector<string> subStrings;
  for(int i = 0; i < s.size(); ++i) {
    for(int j = i; j < s.size(); ++j) {
      const int len = j-i+1;
      subStrings.push_back(s.substr(i,len));
    }
  }
}

// 1. Наблюдение
// Если у нас есть одно вхождение строки t в строке s,
// то все хорошие подстроки слева от t будут заканчиваться на предпоследнем символе t
// все хорошие подстроки справа от t будут начинаться на втором символе t,
// так как все подстроки включающие t полностью будут плохими
// 01234567
// cd|abcd|bc
//    abcd
// cdabc bcdbc - все подстроки этих строк будут хорошими, так как они не содержат t = abcd
// Для вычисления кол-ва пользуемся наблюдением (0):
// 6*7/2 + 6*7/2 = 42
//

// 2. Наблюдение
// Если у нас есть несколько вхождений строки t в строку s
// То пользуясь только наблюдением 1 для подсчета хороших строк мы некоторые подстроки считаем несколько раз
// сколько лишних раз мы их считаем зависит от длины t
// 1)
// cd|ab|ghj|ab|dd
//    ab     ab
// cda bghja bdd
// 3*4/2 + 5*6/2 + 3*4/2 = 6 + 15 + 6 = 27
// Для проверки использую solveSlow - которая работает верно, но Time Limit exceeded:
// solveSlow("cdabghjabdd", "ab") = 27
//
// 2)
// cd|abc|ef|abc|ef|abc|d
// abc
// cdab bcefab bcefab bcd
// 4*5/2 + 6*7/2 + 6*7/2 + 3*4/2 = 10+21+21+6 = 58
// При этом solveSlow("cdabcefabcefabcd", "abc") = 55
// Что показывает, какие-то подсторки были сосчитаны дважды
// cdab bcefab bcefab bcd
//    b b    b b    b b
//      -1    -1      -1 - вычтем подсторки посчитанные дважды
// Получим 58 - 3 == 55
// Возмем более длинные t и на них найдем закономерность как вычислять число дважды подсчитанных подстрок
// abc|defghk|cba|defghk|t|defghk|rrrr|defghk|llll
// defghk
// abcdefgh efghkcbadefgh efghktdefgh efghkrrrrdefgh efghkllll
// 8*9/2 + 13*14/2 + 11*12/2 + 14*15/2 + 9*10/2 = 36+91+66+105+45 = 343
// solveSlow("abcdefghkcbadefghktdefghkrrrrdefghkllll", "defghk") = 303
//
// abcdefgh efghkcbadefgh efghktdefgh efghkrrrrdefgh efghkllll
//     efgh efgh     efgh efgh   efgh efgh      efgh efgh
//           -4            -4          -4             -4
//  343 - 4 * 4 = 343 - 16 = 327 - не получается
// Нужно вычитать не длину строки, а количество подстрок совпадающей строки:
// cnt = 4*5/2 = 10
//           -10           -10         -10            -10
// 343 - 40 = 303 !



int solve(const string& s, const string& t) {
  const auto positions = getPositions(t,s);
  if(positions.empty()) return s.size() * (s.size()+1) / 2;

  int cnt{0};
  int prevPos{-1};
  for(int i = 0; i < positions.size();++i) {
    // 0123456789
    // cdabcefabc   abc
    // cdab
    //    bcefab
      // (7 + 3 - 2) - (2+1) + 1 = 6
    int seqLen = (positions[i] + t.size() - 2) - (prevPos + 1) + 1; // Наблюдение (1)
    cnt += seqLen * (seqLen+1) / 2; // Наблюдение (0)
    prevPos = positions[i];

  }
  // suffix
  int seqLen = s.size() - prevPos-1;
  cnt += seqLen * (seqLen+1) / 2;

  const int duplicates = ( positions.size() * (t.size()-2) * (t.size()-1) ) / 2; // Наблюдение (2)
//  cout << "pos.size():" << positions.size() <<  " dup:" << duplicates << '\n';
  cnt -=  duplicates;// (1)
  return cnt;
}

int solveSlow(const string& s, const string& t) {
  const auto positions = getPositions(t,s);
  int cnt{0};
  for(int i = 0; i < s.size(); ++i) {
    for(int j = i; j < s.size(); ++j) {
      auto it = lower_bound(begin(positions), end(positions), i);
      const bool contains = it != end(positions) && (*it + t.size() - 1 <= j);
      if(!contains) ++cnt;
    }
  }
  return cnt;
}

int main() {
  int q;
  cin >> q;
  vector<string> tasks(2*q);
  for(auto& t : tasks) cin >> t;
  for(int i = 0; i < tasks.size(); i += 2) {
    cout << solve(tasks[i], tasks[i+1]) << '\n';
  }
//  cout << solveSlow("abcdefghkcbadefghktdefghkrrrrdefghkllll", "defghk") << '\n';
//  cout << solve("abcdefghkcbadefghktdefghkrrrrdefghkllll", "defghk") << '\n';
//  cout << solveSlow("cdabcefabcefabcd", "abc") << '\n';
//  cout << solveSlow("cdabghjabdd", "ab") << '\n';
//  cout << solveSlow("cdabcabc", "ab") << '\n';
  return 0;
}