#pragma once
#include <bits/stdc++.h>
using namespace std;

//E. Быстрый поиск в массиве
//https://codeforces.com/group/QmrArgR1Jp/contest/254626/problem/E
//
//ограничение по времени на тест
//1 секунда
//        ограничение по памяти на тест
//512 мегабайт
//        ввод
//стандартный ввод
//вывод
//        стандартный вывод
//
//        Дан массив из n
//        целых чисел. Все числа от −10^9 до 10^9
//
//Нужно уметь отвечать на запросы вида «Cколько чисел имеют значения от l до r»?
//Входные данные
//
//Число n
//        (1≤n≤10^5). Далее n целых чисел.
//
//Затем число запросов k
//        (1≤k≤10^5).
//
//Далее k
//пар чисел l,r (−10^9≤l≤r≤10^9) — собственно запросы.
//Выходные данные
//
//Выведите k чисел — ответы на запросы.
//Пример
//        Входные данные
//
//5
//10 1 10 3 4
//4
//1 10
//2 9
//3 4
//2 2
//
//Выходные данные
//5 2 2 0

namespace lec5::taskE {

  // Ищем индекс первого элемента >= x
  // инвариант на отрезке (l,r] есть элемент >= x
  // a[l] = -inf; a[r] = +inf > x
  // Если такой элемент не найден, вернем n
  int binSearchLowerBound(const vector<int>& a, int x) {
    const int n{(int)a.size()};
    int l = -1; // -inf
    int r = n; // +inf

    while(r-l > 1) {
      int m = l + (r-l)/2;
      if(a[m] < x)
        l = m;
      else
        r = m;
    }
    return r;
  }

  // Ищем индекс первого элемента > x
  // инвариант на отрезке (l,r] есть элемент > x
  // a[l] = -inf; a[r] = +inf > x
  // Если такой элемент не найден, вернем n
  int binSearchUpperBound(const vector<int>& a, int x) {
    const int n{(int)a.size()};
    int l = -1; // -inf
    int r = n; // +inf

    while(r-l > 1) {
      int m = l + (r-l)/2;
      if(a[m] <= x)
        l = m;
      else
        r = m;
    }
    return r;
  }

  int count(const vector<int>& a, int low, int high) {
//    assert(is_sorted(begin(a), end(a)));
    const int lessEqualIdx = binSearchLowerBound(a,low);
    const int greaterIdx = binSearchUpperBound(a, high);
    return greaterIdx - lessEqualIdx;
  }

  void solveE() {
    int n,k;
    cin >> n;
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    sort(begin(a), end(a));
    cin >> k;

    while(k--) {
      int l,r;
      cin >> l >> r;
      cout << count(a,l,r) << ' ';
    }
  }

  void testE() {
    vector<int> a = {1,2,3,4,5,6,7};
    cout << count(a,1,7); // 7
    a = {1,2,3,4,5,6,6};
    cout << count(a,1,7); // 7
    a = {1,1,1};
    cout << count(a,1,7); // 3
    a = {1};
    cout << count(a,1,7); // 1
    a = {1};
    cout << count(a,2,7); // 0
  }
}

// https://codeforces.com/group/QmrArgR1Jp/contest/254626/problem/F
//F. Приближенный двоичный поиск
//        ограничение по времени на тест
//2 секунды
//        ограничение по памяти на тест
//256 мегабайт
//        ввод
//стандартный ввод
//вывод
//        стандартный вывод
//
//        Даны два массива. Первый массив отсортирован по неубыванию, второй массив содержит запросы — целые числа.
//
//Для каждого запроса выведите число из первого массива наиболее близкое (то есть с минимальным модулем разности) к числу в этом запросе . Если таких несколько, выведите меньшее из них.
//Входные данные
//
//В первой строке входных данных содержатся числа n и k (0 < n, k ≤ 10^5).
// Во второй строке задаются n чисел первого массива, отсортированного по неубыванию, а в третьей строке — k чисел второго массива.
// Каждое число в обоих массивах по модулю не превосходит 2·10^9 .
//Выходные данные
//
//Для каждого из k чисел выведите в отдельную строку число из первого массива, наиболее близкое к данному. Если таких несколько, выведите меньшее из них.
//Пример
//        Входные данные
//        Скопировать
//
//5 5
//1 3 5 7 9
//2 4 8 1 6
//
//Выходные данные
//Скопировать
//
//1
//3
//7
//1
//5
namespace lec5::taskF {
  int findClosest(const vector<int> &a, int x) {
    // Ищем первое число >= x
    const int n = a.size();
    // (l,r]
    int l{-1}, r{n};
    while (r - l > 1) {
      int m = l + (r - l) / 2;
      if (a[m] >= x)
        r = m;
      else
        l = m;
    }
    if (r == n) return a.back();
    if (r == 0) return a.front();
    if(a[r] == x) return a[r];

    if(abs(x - a[r-1]) <= abs(x - a[r]))
      return a[r-1];
    return a[r];
  }

  void solveF() {
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    while(k--) {
      int x;
      cin >> x;
      cout << findClosest(a,x) << ' ';
    }
  }

  void testF() {
    vector<int> a = {1,3,5,7,9};
    cout << findClosest(a,2); // 1
    cout << findClosest(a,4); // 3
    cout << findClosest(a,8); // 7
    cout << findClosest(a,1); // 1
    cout << findClosest(a,6); // 5
  }
}

//https://codeforces.com/group/QmrArgR1Jp/contest/254626/problem/G
//G. Очень Легкая Задача
//        ограничение по времени на тест
//2 секунды
//        ограничение по памяти на тест
//256 мегабайт
//        ввод
//стандартный ввод
//вывод
//        стандартный вывод
//
//        Сегодня утром жюри решило добавить в вариант олимпиады еще одну, Очень Легкую Задачу.
//        Ответственный секретарь Оргкомитета напечатал ее условие в одном экземпляре,
//        и теперь ему нужно до начала олимпиады успеть сделать еще n копий.
//        В его распоряжении имеются два ксерокса, один из которых копирует лист за x секунд, а другой — за y.
//        (Разрешается использовать как один ксерокс, так и оба одновременно. Можно копировать не только с оригинала, но и с копии.)
//        Помогите ему выяснить, какое минимальное время для этого потребуется.
//Входные данные
//
//На вход программы поступают три натуральных числа n, x и y, разделенные пробелом (1 ≤ n ≤ 2·10^8, 1 ≤ x, y ≤ 10).
//Выходные данные
//
//Выведите одно число — минимальное время в секундах, необходимое для получения n копий.
//Примеры
//        Входные данные
//        Скопировать
//
//4 1 1
//
//Выходные данные
//Скопировать
//
//3
//
//Входные данные
//Скопировать
//
//5 1 2
//
//Выходные данные
//Скопировать
//
//4

namespace lec5::taskG {
  // Эта задача на бинарный поиск по ответу
  // Идея: используя бинарный поиск мы ищем оптимальный ответ (минимальное значение времени для которого выполняется функция)
  // сколько будет сделано копий на n-th секунде
  auto copies_in_nth_second = [](int sec, int x, int y) {
    // Чтобы код был проще(меньше сравнений) находим быстрый принтер
    int fastTimePerCopy = min(x,y);
    int slowTimePerCopy = max(x,y);

    if(sec < fastTimePerCopy) // если у нас времени < чем требуется мин времени на копию - 0 копий
      return 0;

    // sec / fastTimePerCopy - кол-во копий на быстром принтере
    // (sec-fastTimePerCopy) - в начале у нас один лист, используем быстрый принтер, при этом более медленный простаивает fastTimePerCopy
    return sec / fastTimePerCopy + (sec-fastTimePerCopy) / slowTimePerCopy;
  };

  void solveG() {
    int n,x,y;
    cin >> n >> x >> y;

    // бинарный поиск по ответу
    // максимальный ответ min(x,y) * n - если мы будем использовать только быстрый принтер
    // Нам нужно найти первый ответ для которого кол-во копий >= заданного
    // (l,r]
    int l{-1}, r{min(x,y) * n};
    while(r-l > 1) {
      int m = l + (r-l) / 2;
      if(copies_in_nth_second(m,x,y) >= n)
        r = m;
      else
        l = m;
    }
    cout << r;
  }
}


// https://codeforces.com/group/QmrArgR1Jp/contest/254626/problem/H
//H. Diplomas
//        time limit per test
//1 second
//        memory limit per test
//256 megabytes
//        input
//standard input
//output
//        standard output
//
//        During his high school years, Johnny had participated in a lot of Olympiads in information technology, mathematics and physics.
//        He was quite successful and acquired a descent number of diplomas n
//. After graduating, he was surprised by the fact that all of his diplomas had equal width w and height h
//
//.
//
//Now Johnny is studying at one of the best universities of the state and lives with his group mates at the dormitory.
// He wants to decorate one of his walls with his diplomas.
// But to do so, he has to find a wooden board to attach to the wall and afterwards diplomas to it.
// He wants his board of success to be square shaped and to acquire as less area as possible.
// Every one of his diplomas must be located strictly inside the rectangle w×h
//
//. Diplomas must not be rotated and must not have mutual interior points.
//
// Your task is to find the minimal length of the board that Johnny will need to locate his diplomas.
//Input
//
//        The single line of input contains three integer numbers w, h and n —
//        the width, the height and the number of diplomas respectively (1≤w,h,n≤10^9).
//Output
//
//        The output must contain single integer — the minimal length of the board that Johnny will need to locate his diplomas.
//
//Example
//        Input
//        2 3 10
//
//        Output
//
//        9

namespace lec5::taskH {

  void solveH() {

    long long w,h,n;
    cin >> w >> h >> n;

    auto isOk = [&](long long minLen)->bool {
      const long long rows = minLen / h;
      const long long cols = minLen / w;
      return rows * cols >= n;
    };

    long long l = -1;
    long long r = max(w,h)*n;
    while(r-l > 1) {
      long long m = l + (r-l)/2;
      if(isOk(m))
        r = m;
      else l = m;
    }
    cout << r;
  }
}

// https://codeforces.com/group/QmrArgR1Jp/contest/254626/problem/I
//I. Square root and square
//        time limit per test
//2 seconds
//        memory limit per test
//256 megabytes
//        input
//standard input
//output
//        standard output
//
//        Find x such that x^2 + sqrt(x) = C with the precision at least 6 digits after the point.
//        Input
//
//        The sole line of the input contains one double 1.0 ≤ C ≤ 10^10.
//Output
//
//        The sole line of the output should contain the required x.
//Examples
//        Input
//Copy
//
//2.0000000000
//
//Output
//        Copy
//
//1.0
//
//Input
//        Copy
//
//18.0000000000
//
//Output
//        Copy
//
//4.0

namespace lec5::taskI {

  void solveI() {
    double c;
    cin >> c;
    auto equation = [&c](double x){
      return x * x + sqrt(x) - c;
    };
    double l{-1}, r{1e5};
    for(int i = 0; i < 1000; ++i) {
      double m = l + (r-l) / 2;
      if(equation(m) > 1e-7)
        r = m;
      else if(equation(m) < - 1e-7)
        l = m;
      else {
        r = m;
        break;
      }
    }
    cout << setprecision(10) << r << '\n';
  }

  void solveISecondSolution() {
    double C;
    cin >> C;

    double l = -1;
    double r = C;
    auto fn = [](double x) {
      return x*x + sqrt(x);
    };
    while(r-l >= 1e-8) {
      double m = l + (r-l)/2;
      if(m <= l || m >= r) // number can't be represented
        break;
      if(fn(m) >= C)
        r = m;
      else
        l = m;
    }
    cout << setprecision(10) <<  r << '\n';
  }

}

// https://codeforces.com/group/QmrArgR1Jp/contest/254626/problem/J
//J. Into the Jungle
//        time limit per test
//2 seconds
//        memory limit per test
//256 megabytes
//        input
//standard input
//output
//        standard output
//
//        Tarzan has just collected orchids for Jane's Birthday and wants to return back as soon as possible.
//        But the way back goes across field and the mighty jungle and it's hard to find the optimal path.
//        The plan of the nearest area can be represented as a square, where
//
//        Tarzan's current position is (0, 1).
//
//        Tarzan's house on a tree is at (1, 0).
//
//        the border between field and jungle is a horizontal line y = a (0 ≤ a ≤ 1).
//
//  vf, vj — Tarzan's speed on the field and in the jungle, respectively. Moving along the border is either on the field or in the jungle.
//
//  Find the point on the border, where Tarzan has to enter the jungle, to return back as soon as possible.
//  Input
//
//        First line contains two positive integers vf and vj (1 ≤ vf, vj ≤ 10^5) — speed on the field and in the jungle, respectively.
//
//        Second line contains a single real number a (0 ≤ a ≤ 1) — coordinate on vertical axis of the border between field and jungle.
//Output
//
//        Output a single real number — coordinate on horizontal axis, where Tarzan should enter the jungle, with accuracy no less than 10^-4.
//Example
//        Input
//Copy
//
//5 3
//0.4
//
//Output
//        Copy
//
//0.783310604

// TODO Похоже, что задача на тернарный поиск и встречалась на Информатикс
// Решение, которое я отсылал ранее:
//int Vp,Vf;
//cin >> Vp >> Vf;
//long double a;
//cin >> a;
//auto f = [](long double x, long double a, int Vp, int Vf) {
//  return hypotl(x, a-1) / Vp + hypotl(1-x,-a) / Vf;
//};
//long double l = 0, r = 1;
//while(r-l > 1e-5) {
//// show_vars(r,l);
//long double m0 = l + (r-l) / 3.;
//long double m1 = l + (r-l) * 2. / 3.;
//if(f(m0,a,Vp,Vf) < f(m1,a,Vp,Vf))
//r = m1;
//else
//l = m0;
//}
//cout << setprecision(10) << r << '\n';