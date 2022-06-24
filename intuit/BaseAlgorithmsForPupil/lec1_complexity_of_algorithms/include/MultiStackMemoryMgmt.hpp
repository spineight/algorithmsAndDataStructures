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
      // Для каждого из списков создаем фиктивную голову
      for (int i = 0; i < MAX_N_OF_STACKS; ++i) {
        sp[i] = free++;
      }
      memset(next, 0, sizeof(next));
      memset(value, 0, sizeof(value));
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

    int pop(int i) {
      int res = value[sp[i]];
      sp[i] = next[sp[i]];
      return res;
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
    MultiStackMemoryMgmt() : free(1) { // id начинаем выдавать начиная с 1-ого, так как 0 используется как служебное значение
      static_assert(MAX_N_OF_STACKS > 1, "At least 2 stacks are required, one is aux that is used for memory mgmt");
      memset(sp, 0, sizeof(sp));
      memset(next, 0, sizeof(next));
      memset(val, 0, sizeof(val));
    }

    // 0-ой стэк содержит высвобожденные индексы
    static const int ID_OF_STACK_WITH_AVAILABLE_CELLS = 0;

    int sp[MAX_N_OF_STACKS]; // верхушки стэков
    // MAX_N+1 - мы не использеум элемент с индексом 0
    int next[MAX_N+1];
    int val[MAX_N+1];
    int free;

    // Каждый стек хранится в виде списка:
    // Пример как выглядит k-ый стек
    // #####################
    // #|0| <-- |1| <-- |2|
    // #####################
    // sp[k] = 2

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
      assert(cell_id < MAX_N+1);
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
      assert(sp[ID_OF_STACK_WITH_AVAILABLE_CELLS] != 0);
      int idx = sp[ID_OF_STACK_WITH_AVAILABLE_CELLS];
      sp[ID_OF_STACK_WITH_AVAILABLE_CELLS] = next[sp[ID_OF_STACK_WITH_AVAILABLE_CELLS]];
      return idx;
    }
    bool isIdxForReuse() {
      return sp[ID_OF_STACK_WITH_AVAILABLE_CELLS] != 0;
    }

    bool empty(int i) const{
      return sp[i] == 0;
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