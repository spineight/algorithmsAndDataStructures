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
    StackLinkedListBased()
    : sp(0), free(1)
    {
      memset(next,0,sizeof(next));
      memset(val,0,sizeof(val));
    }
    int sp;
    int free;
    int next[MAX_N+1];
    int val[MAX_N+1];

    bool empty() const { return sp == 0;}
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
    int pop() {
      assert(!empty());
      int res = val[sp];
      sp = next[sp];
      return res;
    }
  };






}





