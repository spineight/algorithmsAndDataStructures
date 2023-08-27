#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec1 {
/**
* Много списков, доступ к списку выполняется по id, далее с ним те же операции что с обычным списком
*  Поэтому i - это id элемента, который нужно удалить
*
*  free - общая переменная для всех списков, откуда мы получаем следующий свободный id
 *
 *  Внимание: так как мы здесь не высвобождаем индексы удаленных элементов, то
 *  MAX_N - должно быть не менее количества операций добавления
 *  (Если мы добавим MAX_N элементов, затем их все удалим, то больше не сможем добавить ни одного элемента
 *  так как, free - который мы используем для присвоения id, и доступа к элементам массивов по этим id выйдет за пределы массивов
 *  решение: научиться переиспользовать индексы удаленных элементов)
*/
  template<size_t MAX_N_OF_STACKS, size_t MAX_N>
  struct MultiLists {
    MultiLists() : free(0) {
      // Для каждого из списков создаем фиктивную голову
      for (size_t i = 0; i < MAX_N_OF_STACKS; ++i) {
        head[i] = tail[i] = free++;
      }
    }

    int head[MAX_N_OF_STACKS]; // верхушки стэка
    int tail[MAX_N_OF_STACKS];
    // +MAX_N_OF_STACKS - так как первые MAX_N_OF_STACKS у нас зарезервированы как id для фиктивных голов
    int next[MAX_N+MAX_N_OF_STACKS];
    int prev[MAX_N+MAX_N_OF_STACKS];
    int val[MAX_N+MAX_N_OF_STACKS];
    int free;

/**
* возвращает id созданного узла
*  который нам нужно знать для добавления в хвост списка
*/
    int add_after(int i, int x) {
      next[free] = next[i];
      prev[free] = i;
      next[i] = free;

      if (next[free] != 0)
        prev[next[free]] = free;

      val[free] = x;
      int ret = free;
      ++free;
      return ret;
    }

    // к i списку добавить в хвост значение x
    void add_to_tail(int i, int x) {
      tail[i] = add_after(tail[i], x);
    }

    int pop_front(int i) {
      assert(!empty(i));
      if(next[head[i]] == tail[i])
        tail[i] = head[i];
      int res = val[next[head[i]]];
      next[head[i]] = next[next[head[i]]];
      return res;
    }
    // Пустой ли стек с id = i
    bool empty(int i) const {
      return head[i] == tail[i];
    }
  };
}