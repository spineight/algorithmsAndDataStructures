#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2 {

/*!
*  \addtogroup lec2_sorting_and_search
*  @{
*/
/**
 * позволит решать многие задачи:
 * Массив элементов a,
 * функция A(a[m])  - для первых элементов массиваа возвращает 0, далее начиная
 * с какого-то элемента (возможно никакого) возвращает 1
 * Возможна такая ситуация, что для всех элементов 0 или 1
 *     0 0 0 0 0 0 0 1 1 1 1
 *  a [ | | | | | | | | | | ]
  */

/** @brief Находит первый элемент равный x в неубывающем массиве
 *
 *  @param a - array sorted in nondescending order
 *  @param x - element for search
 *  @returns индекс элемента если найден, иначе -1
 *  @details Задача поиска элемента в массиве
 *   Для задачи поиска элемента в массиве мы в качестве функции A выбрали:
 *   A(a[m]) = [ a[m] >= x ]
 *
 *   @attention Предусловие
 *
 *    У нас предусловие для поиска элемента = x - массив должен быть упорядочен по возрастанию
 *    (При этом Станкевич не говорит о том, что массив должен быть упорядочен по возрастанию,
 *    а это необходимое условие)
 *
 */
int findFirstStankevich(const vector<int> &a, int x) {

  assert(is_sorted(begin(a), end(a)) &&
           "array should be sorted (non decreasing order)");
  const int n = a.size();
  int L = -1; // virtual elements with idxs : -1,n
  int R = n;

  // invariant: element >=x , is in (L,R]
  while (R - L > 1) { // пока у нас на отрезке больше одного элемента
    int m = L + (R - L) / 2; // чтобы избежать переполнения
    if (a[m] >= x)
      R = m;
    else
      L = m;
  }
  // проверка, найден ли элемент равный X
  if (R == n) // не найден
    return -1;
  if (a[R] == x)
    return R;
  else
    return -1;
}

/**
 *  Находит первое вхождение элемента который не меньше чем X
 *  @param a - array sorted in nondescending order
 *  @param x - element for search
 *  @returns индекс элемента если найден, иначе -1
 *
  *   Предусловие взято от сюда: https://en.cppreference.com/w/cpp/algorithm/lower_bound
  *     Returns an iterator pointing to the first element in the range [first, last) that is not less than (i.e. greater or equal to) value,
  *     or last if no such element is found.
  *   The range [first, last) must be partitioned with respect to the expression element < value or comp(element, value),
  *    i.e., all elements for which the expression is true must precede all elements for which the expression is false.
  *    A fully-sorted range meets this criterion.
  *
  * @attention Здесь в отличие от версии Станкевича не требуется отсортированного по неубыванию массива
  * Но требуется partition относительно X
  *
 */
int findFirst(const vector<int>& a, int x) {
   assert(is_partitioned(begin(a), end(a),[x](int val) {return val < x;}) &&
          "array should be partitioned with respect to x");
   if(!is_partitioned(begin(a), end(a),[x](int val) {return val < x;}))
     return -1;
   const int n = a.size();
   int L = -1; // virtual elements with idxs : -1,n
   int R = n;

   // invariant: element >=x , is in (L,R]
   while (R - L > 1) { // пока у нас на отрезке больше одного элемента
     int m = L + (R - L) / 2; // чтобы избежать переполнения
     if (a[m] >= x)
       R = m;
     else
       L = m;
   }
   // проверка, найден ли элемент равный X
   if (R == n) // не найден
     return -1;
   return R;
}

/** Find index of last element in the sorted array < x, if no such element
 *returns -1.
 *
 *  @param a - array sorted in nondescending order
 *  @param x - element to compare with
 */
int binary_search_find_last_less(const vector<int> &a, int x) {
  assert(is_sorted(begin(a), end(a)) &&
         "array should be sorted (non decreasing order)");
  const int n = a.size();
  int L = -1;
  int R = n;
  // invariant: element < x is in [L,R) - так как a[L] = -inf, виртуальный
  // элемент, который точно подходит
  while (R - L > 1) {
    const int m = L + (R - L) / 2;
    if (!(a[m] >= x))
      L = m;
    else
      R = m;
  }
  // проверка, найден ли элемент равный X
  if (L == -1)
    return -1;
  return L;
}

}