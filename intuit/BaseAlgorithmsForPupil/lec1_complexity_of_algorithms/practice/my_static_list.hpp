#pragma once
#include <bits/stdc++.h>

using namespace std;

namespace my {

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
  struct StaticSingleLinkedList {
    StaticSingleLinkedList() :
    free(1), /**< Указывает на первый доступный id для присвоения элементу списка. */
    head(0), /**< При инициализации в списке есть один элемент - фиктивная голова. Голова-> Хвост -> 0 (не используемый индекс). */
    tail(0)  // fictive head
    {
      memset(next, 0, sizeof(next));
      memset(val, 0, sizeof(val));
    }
    static const int MAX_N = 10;
    int next[MAX_N]; /**< Зависимости(связи) между элементами списка. */
    int val[MAX_N]; /**< По id элемента - получаем его значение. */
    int free; // id of next available element, free < MAX_N
    int head;
    int tail;

/**
*  Добавление элемента со значением x за элементом с id = i.
*/
    void add_after(int i, int x) {
      next[free] = next[i];
      next[i] = free;
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

  ostream& operator<<(ostream& out, const my::StaticSingleLinkedList& l) {
    int i = l.next[l.head];
    while(i != 0) {
      out << l.val[i];
      i = l.next[i];
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
    StaticDoubleLinkedList() :
            free(1),
            head(0), // fictive head
            tail(0)  // fictive head
    {
      memset(next, 0, sizeof(next));
      memset(prev, 0, sizeof(prev));
      memset(val, 0, sizeof(val));
    }
    static const int MAX_N = 10;
    int next[MAX_N];
    int prev[MAX_N];
    int val[MAX_N];
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
    void add_last(int x) {
      add_after(tail,x);
    }

    //
/**
* метод remove_after(i) - здесь не нужен, так как список двухсвязный и мы знаем предыдущий элемент для элемента с id = i
*  Поэтому i - это id элемента, который нужно удалить
*/
    void remove(int i) {
      next[prev[i]] = next[i];
      prev[next[i]] = prev[i];
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