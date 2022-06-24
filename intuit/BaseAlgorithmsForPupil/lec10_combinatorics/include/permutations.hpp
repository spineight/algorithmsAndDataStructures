#pragma once
#include <algorithm>


namespace lec10_combinatorics {
/**
 *  @brief  Permute range into the next @e dictionary ordering.
 *  @ingroup sorting_algorithms
 *  @param  __first  Start of range.
 *  @param  __last   End of range.
 *  @return  False if wrapped to first permutation, true otherwise.
 *
 *  Treats all permutations of the range as a set of @e dictionary sorted
 *  sequences.  Permutes the current sequence into the next one of this set.
 *  Returns true if there are more sequences to generate.  If the sequence
 *  is the largest of the set, the smallest is generated and false returned.
*/
  template<typename T>
  bool next_permutation(T *first, T *last) {
    if (first + 1 == last) return false;

    T *k = last - 2;

    // ищем излом
    while (k >= first && *k > *(k + 1)) {
      --k;
    }
//   Значит нам не удалось найти такой элемент, это значит что элементы в перестановке идут убывающем порядке
//   значит перестановка максимально возможная
    if (k < first) return false;

//   Мы нашли вот это вот место:
//
//      /\
//        \
//         \
// Теперь нужно в хвосте найти минимальное число большее a[k]
// Воспользуемся тем что все числа в хвосте у нас возрастающие, значит нам нужно найти первое число справа большее a[k]
    T *t = last - 1;
    while (*t < *k) --t;
    std::iter_swap(t, k);

    // осталось развернуть хвост, так что элементы в нем идут в возрастающем порядке
    T *l = k + 1;
    T *r = last - 1;
    while (l < r) {
      std::iter_swap(l, r);
      ++l;
      --r;
    }
    return true;
  }
}
