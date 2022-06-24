#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec1 {
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
  template<size_t MAX_N>
  struct StaticSingleLinkedList {
    StaticSingleLinkedList() :
            free(1), /**< Указывает на первый доступный id для присвоения элементу списка. */
            head(0), /**< При инициализации в списке есть один элемент - фиктивная голова. Голова-> Хвост -> 0 (не используемый индекс). */
            tail(0)  // fictive head
    {
      memset(next, 0, sizeof(next));
      memset(val, 0, sizeof(val));
    }
    // MAX_N+1 - так как один элемент(фиктивная голова) не используется
    int next[MAX_N+1]; /**< Зависимости(связи) между элементами списка. */
    int val[MAX_N+1]; /**< По id элемента - получаем его значение. */
    int free; // id of next available element, free < MAX_N
    int head;
    int tail;

    bool empty() const {
      return head == tail;
    }
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
      assert(i != tail);

      if(i != tail) {
        if(next[i] == tail)
          tail = i;
        next[i] = next[next[i]];
      }

    }
  };
}

template<size_t MAX_N>
ostream& operator<<(ostream& out, const lec1::StaticSingleLinkedList<MAX_N>& l) {
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