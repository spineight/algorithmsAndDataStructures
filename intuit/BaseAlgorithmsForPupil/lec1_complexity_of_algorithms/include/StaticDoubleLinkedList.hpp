#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec1 {
  /**
 *  Двухсвязный список, не использующий динамическое выделение памяти
 *
 *  Такие же идеи, что для односвязного, но нам еще нужна доп информация для
 *  каждого элемента - prev, ее храним в массиве
 */
  template<size_t MAX_N>
  struct StaticDoubleLinkedList {
    StaticDoubleLinkedList() :
            free(1),
            head(0), // fictive head
            tail(0)  // fictive head
    {
      memset(next, 0, sizeof(next));
      memset(prev, 0, sizeof(prev));
      memset(val, 0, sizeof(val));
    }
    int next[MAX_N+1];
    int prev[MAX_N+1];
    int val[MAX_N+1];
    int free;
    int head;
    int tail;

    void add_after(int i, int x) {
      next[free] = next[i];
      next[i] = free;
      prev[free] = i;
      if(next[free] != 0)
        prev[next[free]] = free;
      val[free] = x;

      if(tail == i)
        tail = free;

      ++free;
    }
    void add_front(int x) {
      add_after(head,x);
    }
    void add_back(int x) {
      add_after(tail,x);
    }

    bool empty() const {
      return head == tail;
    }

    //
/**
* метод remove_after(i) - здесь не нужен, так как список двухсвязный и мы знаем предыдущий элемент для элемента с id = i
*  Поэтому i - это id элемента, который нужно удалить
*/
    void remove(int i) {
      // Мы не можем удалить из пустого списка
      // Также мы не можем удалить фиктивную голову
      assert(!empty() && i != head);
      if(!empty() && i != head) {
        if(i == tail)
          tail = prev[i];
        next[prev[i]] = next[i];
        if(next[i] != 0)
          prev[next[i]] = prev[i];
      }
    }
  };
}

template<size_t MAX_N>
ostream& operator<<(ostream& out, const lec1::StaticDoubleLinkedList<MAX_N>& l) {
  out << "head: " << l.head << ", tail: " << l.tail << '\n';
  out << "index: ";
  // MAX_N включительно, так как размеры массивов: int next[MAX_N+1]
  for(int i = 0; i <= MAX_N; ++i)
    out << i << " ";
  out << '\n';
  out << "next:  ";
  for(int i = 0; i <= MAX_N; ++i)
    out << l.next[i] << " ";
  out << '\n';
  out << "prev:  ";
  for(int i = 0; i <= MAX_N; ++i)
    out << l.prev[i] << " ";
  out << '\n';
  out << "value: ";
  for(int i = 0; i <= MAX_N; ++i)
    out << l.val[i] << " ";
  out << '\n';

  int i = l.next[l.head];
  while(i != 0) {
    out << l.val[i] << " ";
    i = l.next[i];
  }
return out;
}