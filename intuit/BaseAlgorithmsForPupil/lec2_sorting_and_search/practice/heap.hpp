#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec2::practice {

struct MinHeapStankevich {
  // Просеивание вверх ( всплывание)
  //! Корень имеет индекс 1
  vector<int> a;
  MinHeapStankevich() : a(1,0) {}
  void insert(int v) {
    a.push_back(v);
    siftUp(a.size()-1);
  }
  //! Просеивание вверх (всплывание)
  //! @param i - какой элемент нужно просеить
  void siftUp(int i) {
    while(i > 1 && a[i/2] > a[i]) {
      swap(a[i], a[i/2]);
      i /= 2;
    }
  }
  int peek_min() const { return a[1]; }

  //! Просееивание вниз (утапливание)
  void siftDown(int i) {
    const int n = a.size();

    while(i*2 < n) {
      int j = i;
      if(a[i*2] < a[j])
        j = i*2;
      if(i*2+1< n && a[i*2+1] < a[j])
        j = i*2+1;
      if(i == j) break;
      swap(a[i], a[j]);
      i = j;
    }
  }
  int extract_min() {
    int res = peek_min();
    a[1] = a.back();
    a.pop_back();
    siftDown(1);
    return res;
  }
  bool empty() const {
    return a.size() > 1;
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
  HeapInZeroIndexedArray() {}
  vector<int> a;
  void insert(int v) {
    a.push_back(v);
    swim(a.size()-1);
  }
  void swim(size_t i) {
    Compare cmp;
    while(i > 0) {
      if( !cmp(a[(i-1) / 2] , a[i])) {
        swap(a[(i-1) / 2] , a[i]);
        i = (i-1) / 2;
      } else break;
    }
  }
  int peek_top() const { return a.front(); }

  void sink(size_t i) {
    const size_t n = a.size();
    Compare cmp;
    while(i*2+1 < n) {
      size_t j = i;
      if(cmp(a[i*2+1],a[j]))
        j = i*2+1;
      if(i*2+2<n && cmp(a[i*2+2] , a[j]))
        j = i*2+2;
      if(j == i) break;
      swap(a[i],a[j]);
      i = j;
    }
  }
  int get_front() {
    int res = a.front();
    a.front() = a.back();
    a.pop_back();
    sink(0);
    return res;
  }
  bool empty() const { return a.empty(); }
  std::size_t size() const { return a.size(); }
};


}