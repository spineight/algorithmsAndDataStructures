#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2 {

/** Куча / Пирамида
 * https://neerc.ifmo.ru/wiki/index.php?title=%D0%94%D0%B2%D0%BE%D0%B8%D1%87%D0%BD%D0%B0%D1%8F_%D0%BA%D1%83%D1%87%D0%B0
 * 1. Почти полное двоичное дерево (последний ряд заполнен не доконца,
*заполнение
* слева на право) - на i-ом слое 2^i вершин, кроме последнего (слои нумеруются с
*нуля)
 * 2. у которого в узлах хранятся ключи такие что ключ родителя <=
* ключа его детей (если куча на минимум)
 *
 *
* Двоичное дерево - каждый узел имеет не более 2-х детей
* Лист - узел без детей
 * Высота - расстояние от корня до самого далекого листа
 *
 * Так как она почти полное двоичное дерево, ее можно упаковать в массив
 *
 *                    3(1)
 *               4(2)                     5(3)
 *       7(4)           8(5)       10(6)       15(7)
 *    9(8)   10(9)   20(10)
 *
 *    left_child_idx = 2 * parent_idx
 *    right_child_idx = 2 * parent_idx + 1
 *    parent_idx = child / 2
 *    Условие кучи: a[i/2] <= a[i]
 */
//! Корень имеет индекс 1
struct MinHeapStankevich {
  // Просеивание вверх ( всплывание)

  vector<int> a;
  MinHeapStankevich() : a(1,0) {}
  void insert(int v) {
    a.push_back(v);
    siftUp(a.size() - 1);
  }
  //! Просеивание вверх (всплывание)
  //! @param i - какой элемент нужно просеить
  void siftUp(int i) {
    while (i > 1 && a[i / 2] > a[i]) {
      swap(a[i / 2], a[i]);
      i = i / 2;
    }
  }
  int peek_min() const { return a[1]; }

  //! Просееивание вниз (утапливание)
  void siftDown(int i) {
    int n = a.size() - 1;
    while (2 * i <= n) { // левый ребенок имеет индекс 2*i, пока он есть можно топить
      int j = i; // Поиск минимума из 3-х, в j хранится индекс минимума из 3-х: i, 2*i,
                 // 2*i + 1
      if (a[2 * i] < a[i])
        j = 2 * i;
      if (2 * i + 1 <= n && a[2 * i + 1] < a[j])
        j = 2 * i + 1;
      if (j == i)
        break;
      swap(a[i], a[j]);
      i = j;
    }
  }
  int extract_min() {
    int res = a[1];
    a[1] = a.back();
    a.pop_back();
    siftDown(1);
    return res;
  }
  bool empty() const {
    return a.size() > 1; // индексация с 1, первый элемент не используется
  }
};


/** Куча / Пирамида Индекс первого элемента в массиве - 0
 *
 * @tparam Compare - позволяет создать MIN/MAX heap
 * Алгоритмы такие же как в HeapInOneIndexedArray
 * Меняется формула рассчета предка/ детей
 */
template <typename Compare>
struct HeapInZeroIndexedArray {
  vector<int> a;
  HeapInZeroIndexedArray() {}
  void insert(int v) {
    a.push_back(v);
    swim(a.size()-1);
  }
  void swim(size_t i) {
    Compare cmp;
    while (i > 0 && !cmp(a[(i - 1) / 2], a[i])) {
      swap(a[(i - 1) / 2], a[i]);
      i = (i - 1) / 2;
    }
  }
  int peek_top() const { return a[0]; }

  void sink(size_t i) {
    Compare cmp;
    const size_t n = a.size();
    while (2 * i + 1 < n) {
      size_t j = i;
      if (cmp(a[2 * i + 1], a[i]))
        j = 2 * i + 1;
      if (2 * i + 2 < n && cmp(a[2 * i + 2], a[j]))
        j = 2 * i + 2;
      if (j == i)
        break;
      swap(a[i], a[j]);
      i = j;
    }
  }
  int get_front() {
    int res = a[0];
    a[0] = a.back();
    a.pop_back();
    sink(0);
    return res;
  }
  bool empty() { return a.empty(); }
  std::size_t size() { return a.size(); }
};

}