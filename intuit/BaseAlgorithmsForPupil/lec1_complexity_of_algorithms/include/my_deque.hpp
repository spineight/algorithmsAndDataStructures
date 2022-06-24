#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec1 {
/**
 *  Циклическая очередь с двумя концами, поддерживающая добавление элементов в конец и начало
 *  и извлечение элементов из конца и начала.
 *
 *  В основе организации такие же идеи как и в Queue
 *  @see my_queue
 */
  template<size_t MAX_N>
  struct RingDeque {
    int h = 0; /**< Указатель на голову. */
    int t = 0; /**< Указатель на хвост. */
    static constexpr int SIZE = MAX_N + 1;

    int q[SIZE];

    void push_back(int x) {
      q[t] = x;
      t = (t+1)%SIZE;
    }
    void push_front(int x) {
      h = ( (h-1) % SIZE + SIZE ) % SIZE;
      q[h] = x;
    }
    int pop_front() {
      int res = q[h];
      h = (h+1)%SIZE;
      return res;
    }
    int pop_back() {
      t = ( (t-1) % SIZE + SIZE ) % SIZE;
      int res = q[t];
      return res;
    }

    int front() const {
      return q[h];
    }
//          t     h
    // | | | | | | | | |
    int size() {
      if(t >= h) return t-h;
      else return SIZE - h + t;
    }
    void clear() {
      h=t=0;
    }
  };

}