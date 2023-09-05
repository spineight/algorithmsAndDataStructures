#include <bits/stdc++.h>

using namespace std;

//! /home/oleg/github/algorithmsAndDataStructures/e-maxx/strings/Нахождение_всех_подпалиндромов.pdf

//! [01/09/2023]
void findSubPalindromesTrivial(const string& s) {
  const int n = s.size();
  vector<int> oddLength(n, 0); // (oddLength[i] - 1) * 2 - length of  odd palindrome (ex. "aba") with center at i
  vector<int> evenLength(n, 0); // evenLength[i] * 2 - length of  even palindrome (ex. "abba") with center at i

  for (int i = 0; i < n; ++i) {
    // odd length
    oddLength[i] = 1;
    while (0 <= i - oddLength[i] && i + oddLength[i] < n && s[i - oddLength[i]] == s[i + oddLength[i]])
      ++oddLength[i];

    // even length
    while (0 <= i - evenLength[i] - 1 && i + evenLength[i] < n && s[i - evenLength[i] - 1] == s[i + evenLength[i]])
      ++evenLength[i];
  }
  cout << "oddLength\n";
  for (auto v: oddLength) cout << v << " ";
  cout << "\n";

  cout << "evenLength\n";
  for (auto v: evenLength) cout << v << " ";
  cout << "\n";

}

//! [01/09/2023]
//! My implementation
// В основе идеи - использование findSubPalindromesTrivial, только более умно, за счет использования ранее
// вычисленных значений и хранения границ внешнего палиндрома
// Так делая расчеты внутри внешнего палиндрома мы можем переиспользовать расчитанные ранее значения
//          j       i
//   0  1   2   3   4  5  6  7  8  9  10  11  12  13  14
//   a  b   a   c   a  b  a  d  a  b  a   c   a   b   a
//  (a  b  [a]  c  |a|  b  a)  d  a  b  a   c   a   b   a
//   L                     R
//
//  Если центр палиндрома i, для которого мы делаем расчеты находится внутри внешнего палиндрома
//  То мы ищем зеркальный элемент j и можем значение oddLength[j] этого элемента использовать
//  1) j(reflected element) = (R-i) + l
//    идея: (R-i) - сколько от i ого элемента до конца палиндрома заданного (L,R)
//    если мы это кол-во отложим от L - мы получим зеркальный элемент
//    И мы начинаем наращивать oddLength[i] не с 1, а с того значения которое получили от зеркального элемента
// Важные моменты:
//    1. обновлять L,R
//    2. Когда внутренний палиндром достигает или вылезает за границы внешнего
//      поскольку за границами внешнего никакой симметрии не гарантируется - то нужно воспользоваться с момента границы наивным способом
void findSubPalindromesManaker(const string& s) {
  cout << "findSubPalindromesManaker\n";
  const int n = s.size();
  vector<int> oddLength(n,1);
  int l{0};
  int r{-1};
  for(int i = 0; i < n; ++i) {
    if(i < r) {
      const int reflectedI = l+(r-i);
      oddLength[i] = min(oddLength[reflectedI], r-i+1);
    }
    while(0 <= i - oddLength[i] && i + oddLength[i] < n && s[i - oddLength[i]] == s[i + oddLength[i]])
      ++oddLength[i];
    if(i + oddLength[i]-1 > r) {
      l = i - oddLength[i]+1;
      r = i + oddLength[i]-1;
    }
  }

  cout << "oddLength\n";
  for (auto v: oddLength) cout << v << " ";
  cout << "\n";
}

void findSubPalindromesManakerOddEmaxx(const string& s) {
  const int n = s.size();
  vector<int> d1(n);
  int l = 0, r = -1;
  for (int i = 0; i < n; ++i) {
    int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);

    while (i + k < n && i - k >= 0 && s[i + k] == s[i - k]) ++k;
    d1[i] = k;

    if (i + k - 1 > r)
      l = i - k + 1, r = i + k - 1;
  }
}

void findSubPalindromesManakerEvenEmaxx(const string& s) {
  const int n = s.size();
  int l = 0, r = -1;
  vector<int> d2 (n);
  l=0, r=-1;
  for (int i=0; i<n; ++i) {
    int k = i>r ? 0 : min (d2[l+r-i+1], r-i+1);

    while (i+k < n && i-k-1 >= 0 && s[i+k] == s[i-k-1]) ++k;
    d2[i] = k;

    if (i+k-1 > r)
      l = i-k, r = i+k-1;
  }
}

int main() {
//  findSubPalindromesTrivial("ababac");
//
//  findSubPalindromesTrivial("abaabac");

  findSubPalindromesManaker("ababac");

  findSubPalindromesManaker("abacabadabacaba");
}