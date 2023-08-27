#pragma once
#include <bits/stdc++.h>

using namespace std;

// refs
// http://e-maxx.ru/algo/stacks_for_minima
// https://informatics.mccme.ru/mod/statements/view.php?id=33285#1

// tasks:
// https://informatics.mccme.ru/mod/statements/view3.php?id=8755&chapterid=1007#1
// https://informatics.mccme.ru/mod/statements/view3.php?id=33285&chapterid=412#1


namespace lec1 {

/**
*  Стэк основанный на статических списках.
*
*  Так как мы всегда добавляем элемент в конец, то в отличие от статического списка фиктивная голова не нужна
*/
  template<size_t MAX_N>
  struct StackLinkedListBased {
    int sp{-1}; //! [27/08/2023] id of top element of the stack
    int free{0}; //! [27/08/2023] - выдача индексов (все используются, нет фиктивной головы)
    int next[MAX_N];
    int val[MAX_N];

    bool empty() const { return -1 == sp;}
    int back() const {
      assert(!empty());
      return val[sp];
    }
    // добавляем в голову
    void push(int x) {
      val[free] = x;
      next[free] = sp;
      sp = free;
      ++free;
    }
    void pop() {
      sp = next[sp];
    }
  };






}





