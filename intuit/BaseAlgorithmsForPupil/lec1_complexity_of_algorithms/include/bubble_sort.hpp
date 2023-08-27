#pragma once
#include <vector>
using namespace std;

namespace lec1 {

/**
*  Алгоритм сортировки как пример для анализа времени работы.
*
*/
void bubble_sort(vector<int> &a) {
  const int n = a.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j + 1 < n; ++j) {
      if (!(a[j] < a[j + 1])) {
        swap(a[j], a[j + 1]);
      }
    }
  }
}

/**
*  Алгоритм сортировки как пример для анализа времени работы.
*  Оптимизированный, но с той же сложностью работы что
*  @see bubble_sort
*/
void bubble_sort_ver2(vector<int> &a) {
  const int n = a.size();
  for (int i = 0; i < n; ++i) {
    // После i-ого прохода i-ый элемент станет на свое место
    for (int j = 0; j + 1 < n - i; ++j) {
      if (!(a[j] < a[j + 1])) {
        swap(a[j], a[j + 1]);
      }
    }
  }
}


/**
 * [27/08/2023]
 * Более понятная на мой взгляд реализация
 * (на каждом шаге внешнего цикла мы выбираем самый большой элемент, который всплывает)
 */
  void bubble_sort_ver3(vector<int> &a) {
    for(size_t i = 0; i < size(a); ++i) {
      for(size_t j = 0; j < size(a) - 1; ++j) {
        if(a[j] >a[j+1]) swap(a[j],a[j+1]);
      }
    }
  }

/**
 * [27/08/2023]
 * Ver3 - Оптимизация - проверка во внешнем цикле, что массив уже отсортирован
 */
  void bubble_sort_ver4(vector<int> &a) {
    for(size_t i = 0; i < size(a); ++i) {
      bool isSorted{true};
      //! -j - так как j элементов с конца находятся на своих местах и они заведомо больше текущего
      //! поэтому нет смысла пытаться в них встроить текущий элемент
      for(size_t j = 0; j < size(a) - 1 - j; ++j) {
        if(a[j] >a[j+1]) {
          swap(a[j],a[j+1]);
          isSorted = false;
        }
      }
      if(isSorted) break;
    }
  }
}
