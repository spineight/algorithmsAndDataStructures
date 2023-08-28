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

//! [28/08/2023][0]
//! Вычисления детей и предка с таким индексом проще
//! Можно брать и с корнем с индексом 0, но тогда:
//! parent(i) = (i-1) / 2
//! leftChild(i) = 2*i+1
//! rightChild(i) = 2*i+2

template<size_t SZ>
struct MinHeapStankevich {
  // Просеивание вверх ( всплывание)

  int a[SZ+1]; // +1 as array starts from 1
  int n{0};
  void insert(int val) {
    ++n;
    a[n] = val;
    siftUp(n);
  }
  //! Просеивание вверх (всплывание) Swim
  //! @param i - какой элемент нужно просеить
  void siftUp(int i) {
    while (i > 1 && a[i / 2] > a[i]) {
      swap(a[i / 2], a[i]);
      i = i / 2;
    }
  }
  int peek_min() const { return a[1]; }

  //! Просееивание вниз (утапливание) Sink
  void siftDown(int i) {
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
    swap(a[1], a[n]);
    --n;
    siftDown(1);
    return res;
  }
  bool empty() const {
    return 0 == n;
  }
};
}