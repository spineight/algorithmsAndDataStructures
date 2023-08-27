#pragma once
#include <bits/stdc++.h>

using namespace std;

namespace lec1::practice {

  //

/**
 *  Односвязный список, не использующий динамическое выделение памяти
 *
 *  Используем фиктивную голову, для того, чтобы не делать проверок для добавления в пустой список
 *  (так код получается более компактный)
 *
 *  Для хранения значений, связей между элементами используем массивы - в качестве индекса id элемента
 *  Индексы выдаем использую переменную free
 *  Память(выданные индексы) при удалении элементов из списка не высвобождаем
 */
template<size_t sz>
struct StaticSingleLinkedList {

  //! sz + 1 - as one of elements is a dummy head with no data
  //! to make effective sz we add 1
  int data[sz+1]{0};
  int next[sz+1]{-1};
  int freeId{1}; // 0 - we use for dummy head ID
  StaticSingleLinkedList()
  {

  }

/**
*  Добавление элемента со значением x за элементом с id = i.
*/
    void add_after(int i, int x) {
      data[freeId] = x;
      auto tmp = next[i];
      next[i] = freeId;
      next[freeId] = tmp;
    ++freeId;
    }
    void add_front(int x) {
      add_after(next[0], x);
    }
    void add_back(int x) {
      int id = 0;
      while(next[id] != -1)
        id = next[id];
      add_after(id,x);
    }

    //
    //
/**
* Удалить элемент после элемента с id = i
*  так как список односвязный, то мы не знаем предыдущий элемент,
*  поэтому мы передаем предыдущий и используем remove_after
*/
    void remove_after(int i) {
      next[i] = next[next[i]];
    }
  };

template<size_t sz>
  ostream& operator<<(ostream& out, const StaticSingleLinkedList<sz>& l) {
    int id = 0;
    while(l.next[id]) {
      id = l.next[id];
      out << "id:" << id << ", val:" << l.data[id] << '\n';
    }
    return out;
  }

/**
 *  Двухсвязный список, не использующий динамическое выделение памяти
 *
 *  Такие же идеи, что для односвязного, но нам еще нужна доп информация для
 *  каждого элемента - prev, ее храним в массиве
 */
  struct StaticDoubleLinkedList {
    StaticDoubleLinkedList()

    {

    }


    void add_after(int i, int x) {

    }
    void add_front(int x) {

    }
    void add_last(int x) {

    }

    //
/**
* метод remove_after(i) - здесь не нужен, так как список двухсвязный и мы знаем предыдущий элемент для элемента с id = i
*  Поэтому i - это id элемента, который нужно удалить
*/
    void remove(int i) {

    }
  };

/**
* Много списков, доступ к списку выполняется по id, далее с ним те же операции что с обычным списком
*  Поэтому i - это id элемента, который нужно удалить
*
*  free - общая переменная для всех списков, откуда мы получаем следующий свободный id
*/
  struct MultiLists {
    MultiLists() : free(0) {
      for(int i = 0; i < MAX_LISTS_N; ++i) {
        head[i] = tail[i] = free;
        ++free;
      }
    }
    static const int MAX_LISTS_N = 10;
    int head[MAX_LISTS_N];
    int tail[MAX_LISTS_N];
    static const int MAX_N = 100;
    int next[MAX_N];
    int prev[MAX_N];
    int val[MAX_N];
    int free;

/**
* возвращает id созданного узла
*  который нам нужно знать для добавления в хвост списка
*/
    int add_after(int i, int x) {
      next[free] = next[i];
      prev[free] = i;
      next[i] = free;

      if(next[free] != 0)
        prev[next[free]] = free;

      val[free] = x;
      int ret = free;
      ++free;
      return ret;
    }

    void add_to_tail(int list_id, int x) {
      tail[list_id] = add_after(tail[list_id],x);
    }
  };



}