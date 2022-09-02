#include <bits/stdc++.h>
using namespace std;

//! Z function
//!               i
//!  s0_s1_s2_s3_s4_s5_s6_s7_s8
//! Z[i] - это длина наибольшего префикса строки S, такого что он совпадает с префиксом подстроки S[i..n-1]
//! Зная Z function для s$t - можно найти все вхождения строки s в текст t
//!
//! Z алгоритм - алгоритм вычисления Z функции
//!
//! Z блок: Z блок для позиции i - такой блок совпадающий с префиксом строки s, что его начало до позиции i, а конец после
//!               i
//!  s0_s1_s2_s3_s4_s5_s6_s7_s8
//!       [               ]        -> s0s1s2s3s4s5 == s2s3s4s5s6s7
//! Знание Z блока и предыдущих значений Z позволяет вычислить Z функию для i позиции
//! Как мы используем предыдущие значения Z функции и данные текущего Z блока:
//!               i
//!  s0_s1_s2_s3_s4_s5_s6_s7_s8
//!       [               ]
//!  [               ]
//!        k
//! Так как по определению Z блока он совпадает с префиксом строки, значит в соответствующей позиции k этого префикса:
//! z_k = z_i

vector<int> zAlgorithm(const string& s, const string& t) {
  vector<int> positions;
  const auto aux = s+'$'+t;
  int zBlockStartPos{1}, zBlockLength{0};
  vector<int> z(aux.size());
  z[0] = 0;

  for(int i = 1; i < aux.size(); ++i) {
    // Есть действующий Z block
    if(zBlockStartPos + zBlockLength-1 >= i) {
      const int k = i - zBlockStartPos;
      // z[k] - количество символов начиная с k-th pos которые совпадают с началом строки
      // 1. Если i + кол-во совпадающих символов заканчиваются до конца блока
      //!               i----\
      //!  s0_s1_s2_s3_s4_s5_s6_s7_s8  - i + z[k] - попадает в s6,  последний символ блока s7
      //!       [               ]
      if(i + z[k] < zBlockStartPos + zBlockLength )
        z[i] = z[k];
      //! если i + z[k] - приходится на последний символ блока или выходит за него - мы пытаемся продлить
      else {
        // если выходит, мы расширяем текущий блок, начинающийся в i
        zBlockLength = zBlockLength - k; // все совпадения до i мы убираем, так как старт у нас теперь в i
        zBlockStartPos = i;
        while(aux[i+zBlockLength] == aux[zBlockLength]) ++zBlockLength;
        z[i] = zBlockLength;
      }
    }
    // Если Z блока нет(он нас не покрывает) - возмем наш символ и будем с него сравнивать и это будет новый z block
    else {
      zBlockStartPos = i;
      zBlockLength = 0;
      while(aux[zBlockStartPos + zBlockLength] == aux[zBlockLength]) ++zBlockLength;
      z[i] = zBlockLength;
    }
    if(z[i] == s.size()) positions.push_back(i - s.size()-1);
  }
  return positions;
}

int main() {
  //  0123456789
  // "aba$abaaba"
  //
  // i   zBlockStart   zBlockLength  k
  // 1   1             0
  // 2   1             0             0
  // 3   2             1

  auto pos = zAlgorithm("aba", "abaaba");
  for(auto p : pos) cout << p << ' '; // 0 3
  cout << '\n';

  pos = zAlgorithm("acab", "acacab");
  for(auto p : pos) cout << p << ' '; // 2
  cout << '\n';

  pos = zAlgorithm("abacabab", "abacabacabab");
  for(auto p : pos) cout << p << ' '; // 4
  cout << '\n';

  pos = zAlgorithm("aba", "abacabadabacaba");
  for(auto p : pos) cout << p << ' '; // 0 4 8 12
  cout << '\n';
  return 0;
}