#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec1 {
/**
   * Мультистек
   * @tparam MAX_N_OF_STACKS
   * @tparam MAX_N
   */
  template<size_t MAX_N_OF_STACKS, size_t MAX_N>
  struct MultiStack {
    MultiStack() : free(0) {
      //! [27/08/2023][0] - Для стеков фиктивная голова не нужна (об этом же говорится и в лекции)
//      // Для каждого из списков создаем фиктивную голову
//      for (int i = 0; i < MAX_N_OF_STACKS; ++i) {
//        sp[i] = free++;
//      }

      for (int i = 0; i < MAX_N_OF_STACKS; ++i) {
        sp[i] = -1;
      }
    }

    int sp[MAX_N_OF_STACKS]; // верхушки стэка
    int next[MAX_N];
    int value[MAX_N];
    int free;

    /**
     * Положить в i-ый стек число x
     * @param i
     * @param x
     */
    void push(int i, int x) {
      next[free] = sp[i];
      sp[i] = free;
      value[free] = x;
      ++free;
    }

    void pop(int i) {
      sp[i] = next[sp[i]];
    }
    int top(int i) {
      return value[sp[i]];
    }
    bool empty(int i) {
      return -1 == sp[i];
    }
  };

/**
*  МультиСтэк основанный на статических списках.
*  с освобождением памяти
*  Множество стэков, доступ по idx стэка
*
*  В стэке с нулевым индексом хранятся id удаленных элементов (они могут быть снова использованы под новые элементы)
*
*/
  template<size_t MAX_N_OF_STACKS, size_t MAX_N>
  struct MultiStackMemoryMgmt {
    MultiStackMemoryMgmt()
//    free(1)
    {
      // id начинаем выдавать начиная с 1-ого, так как 0 используется как служебное значение
      //! [27/08/2023][0]
      //! Не нужно нам никакое служебное значение, так как в стеке не нужна фиктивная голова,
      //! поэтому можем раздавать id начиная с 0

      static_assert(MAX_N_OF_STACKS > 1, "At least 2 stacks are required, one is aux that is used for memory mgmt");
      for(size_t i = 0; i < MAX_N_OF_STACKS; ++i)
        sp[i] = -1;
    }

    // 0-ой стэк содержит высвобожденные индексы
    static const int ID_OF_STACK_WITH_AVAILABLE_CELLS = 0;

    int sp[MAX_N_OF_STACKS]; // верхушки стэков
    // MAX_N+1 - мы не использеум элемент с индексом 0
    //! [27/08/2023][1] - используем, см [27/08/2023][0]
    int next[MAX_N];
    int val[MAX_N];
    int free{0}; //! [27/08/2023][2]

    // Каждый стек хранится в виде списка:
    // Пример как выглядит k-ый стек
    // #####################
    // #|0| <-- |1| <-- |2|
    // #####################
    // sp[k] = 2
    //! [27/08/2023]
    //! sp[k] = 2 - означает, что в k-ом стеке на верхушке находится элемент с id = 2

    // Пололжить в i-ый стек число x
    void push(size_t i, int x) {
      assert(i != ID_OF_STACK_WITH_AVAILABLE_CELLS && i < MAX_N_OF_STACKS);
      size_t cell_id = free;
      if(isIdxForReuse()) {
        cell_id = getIdxForReuse();
      }
      else {
        ++free;
      }
      assert(cell_id < MAX_N);
      next[cell_id] = sp[i];
      sp[i] = cell_id;
      val[cell_id] = x;
    }



    // pop from i-th stack
    int pop(size_t i) {
      assert(i != ID_OF_STACK_WITH_AVAILABLE_CELLS && i < MAX_N_OF_STACKS);
      int res = val[sp[i]];
      int idx = sp[i];
      sp[i] = next[sp[i]];
      addIdxForReuse(idx);
      return res;
    }

    void addIdxForReuse(int idx) {
      next[idx] = sp[ID_OF_STACK_WITH_AVAILABLE_CELLS];
      sp[ID_OF_STACK_WITH_AVAILABLE_CELLS] = idx;
    }
    int getIdxForReuse() {
      assert(sp[ID_OF_STACK_WITH_AVAILABLE_CELLS] != -1);
      int idx = sp[ID_OF_STACK_WITH_AVAILABLE_CELLS];
      sp[ID_OF_STACK_WITH_AVAILABLE_CELLS] = next[sp[ID_OF_STACK_WITH_AVAILABLE_CELLS]];
      return idx;
    }
    bool isIdxForReuse() {
      return sp[ID_OF_STACK_WITH_AVAILABLE_CELLS] != -1;
    }

    bool empty(int i) const{
      return sp[i] == -1;
    }
  };
}

template<size_t MAX_N_OF_STACKS, size_t MAX_N>
ostream& operator<<(ostream& out, const lec1::MultiStackMemoryMgmt<MAX_N_OF_STACKS, MAX_N>& s) {
  out << "idx:    ";
  for(int i = 0; i < MAX_N_OF_STACKS; ++i) {
    out << i << " ";
  }
  out << '\n';
  out << "sp:     ";
  for(int i = 0; i < MAX_N_OF_STACKS; ++i) {
    out << s.sp[i] << " ";
  }
  out << '\n';

  out << "value:  ";
  for(int i = 0; i < MAX_N_OF_STACKS; ++i) {
    out << s.val[s.sp[i]] << " ";
  }
  out << '\n';
  return out;
}