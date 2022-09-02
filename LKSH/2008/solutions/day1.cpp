#include <bits/stdc++.h>
using namespace std;
//! Right. Правое вхождение
//! Здесь он как и Станкевич говорит про индикаторную функцию f(x), такая что:
//! 000000000 11111111
//! Здесь мы берем за индикаторную функцию F(X)  X <= target:
//! 111111111 00000000
int binarySearchRightVer1(const vector<int>& numbers, int target) {
  const int n = numbers.size();
  int l{-1}, r{n};

  while(r-l>1) {
    int m = l + (r-l) / 2;
    if(numbers[m] <= target) l = m;
    else r = m;
  }
  if(l == -1 || numbers[l] != target) return 0;
  return r;
}

vector<int> right(const vector<int>& numbers, const vector<int>& queries) {
  vector<int> res;
  for(auto q : queries) {
    res.push_back(binarySearchRightVer1(numbers,q));
  }
  return res;
}

//! Задача про распил досок
//! Идея: двоичный поиск по ответу и по вещественным числам
// Пусть у нас есть n досок разной длины.
// И мы умеем делать распилы. Наша задача такими распилами сделать k досок одинаковой длины
// И мы хотим эту длину сделать как можно больше.
// Вывести какой максимальной длины мы можем сделать k досок одинаковой длины
// Дано n,k и размеры досок
// Вывести максимальную длину разреза с точностью до `10^-6` при которой мы получим k досок одинаковой длины
//! Aux function which given sewSize returns number of boards of sewSize length
int count(const vector<int>& boards, double sewSize) {
  int res{0};
  for(auto b : boards) {
    res += b / sewSize;
  }
  return res;
}
double solveBoards(const vector<int>& boards, int k) {
  const double kEpsilon{1e-6};
  double l{0};
  double r = *max_element(begin(boards), end(boards));
  //! Indicator function f(x) cut size of x  produces >= k boards
  //! 1111111 000000
  while(r-l > kEpsilon) {
    double m = l + (r-l)/2;
    if(count(boards, m) >= k) l = m;
    else r = m;
  }
  return l;
}

//! Задача про фонтаны, есть холл где расположены фонтаны разного радиуса
//! Мы хотим туда добавить еще один фонтан
//! Вопрос какого максимального радиуса мы туда можем добавить фонтан
//! Решается через двоичный поиск по ответу


//! Kth minimum
//! Find k-th number (position of number in sorted array in non decreasing order)
//! Idea is to use modified quick sort
int kth(vector<int>& a, int k, int l, int r) {
  if(l==r) return a[l];
  int i{l}, j{r};
  const int pivot = a[0];
  while(i <= j) {
    while(a[i] < pivot) ++i;
    while(a[j] > pivot) --j;
    if(i <= j) {
      swap(a[i], a[j]);
      ++i;
      --j;
    }
  }
  if(l <= k && k <= j) return kth(a,k,l,j);
  if(i <= k && k <= r) return kth(a,k,i,r);
  return a[l];
}
optional<int> kth(const vector<int>& a, int k) {
  if(a.empty()) return {};
  vector<int> b(a);
  return kth(b,k-1,0,b.size()-1);
}

int main() {
  auto res = right({1,3,5},{1,5,7});
  for(auto r : res) cout << r << " ";
  cout << '\n';

  res = right({1,1,3,3},{1,3});
  for(auto r : res) cout << r << " ";
  cout << '\n';

  cout << "solve boards\n";
  cout << solveBoards({4,5,6},8) << '\n'; // 1
  cout << solveBoards({6,5,6},5) << '\n'; // 3
  cout << solveBoards({1,5,10},2) << '\n'; // 5
  cout << solveBoards({1,5,10},1) << '\n'; // 10

  cout << "solve k-th element\n";
  cout << kth({1388}, 1).value() << '\n'; // 1388
  cout << kth({1388,402,1154,950}, 1).value() << '\n'; // 402



  return 0;
}