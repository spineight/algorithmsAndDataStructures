#pragma once
namespace lec2 {
/** Для монотонной функции вида F(x)= X^3 + ax + b = с, где a > 0, b > 0, c > 0
* найти такой первый целый x: что x^3+ax+b=c
*   // Возвращает -1 при неудаче.
*
*  @param a - coeff > 0
*  @param b - coeff > 0
*  @param c - coeff > 0
 *
 *  Заметим, что a>0 , b > 0
 *  При возрастании x => F(x) возрастает
 *  Давайте виртуально(в уме нашем, заведем массив, назовем его f и забьем в него
 *  f(0), f(1)...f(n)
 *  Заметим, что в этом массиве значения будут возрастать
 *  Предположим то, что мы добьемся, что f(n) > c
 *  f(k) < c
 *  Нам нужно найти такой элемент i, что f(i) = c
 *
*/
  int find_function_root(int a, int b, int c) {
    assert(a > 0 && b > 0 && c > 0 && "coefficients should be positive");
    // 1. Находим такие виртуальные элементы, чтобы инвариант x in (L,R]
    // выполнялся

    auto Fx = [](int a, int b, int x) { return x * x * x + a * x + b; };

    int R = 1;
    while (Fx(a, b, R) < c)
      R *= 2;
    int L = -1;
    while (Fx(a, b, L) >= c)
      L *= 2;
    // 2. Запускаем бинарный поиск
    while (R - L > 1) {
      int m = L + (R - L) / 2;
      if (Fx(a, b, m) >= c)
        R = m;
      else
        L = m;
    }
    // 3. Проверка найден ли подходящий x, при котором достигается равенство:
    // x^3+ax+b=c
    if (Fx(a, b, R) == c)
      return R;
    return -1;
  }
}