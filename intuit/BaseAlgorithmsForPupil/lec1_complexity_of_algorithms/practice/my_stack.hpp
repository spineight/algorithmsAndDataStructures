#pragma once
#include <bits/stdc++.h>

using namespace std;

// refs
// http://e-maxx.ru/algo/stacks_for_minima
// https://informatics.mccme.ru/mod/statements/view.php?id=33285#1

// tasks:
// https://informatics.mccme.ru/mod/statements/view3.php?id=8755&chapterid=1007#1
// https://informatics.mccme.ru/mod/statements/view3.php?id=33285&chapterid=412#1


namespace lec1::practice {
/**
*  Стэк основанный на массиве фиксированной длины.
*/
  template<size_t MAX_SIZE /**< вместимость стэка */>
  struct StackArrayBased {
    StackArrayBased() : sp(-1) {}
    int sp; /**< указывает на последний элемент в стеке. Если стэк пуст == -1*/
    int s[MAX_SIZE];
    bool empty() const { return sp == -1;}
    void push(int x) {
      ++sp;
      s[sp] = x;
    }
    int back() const {
      return s[sp];
    }
    void clear() {sp = -1;}
    int pop() {
      return s[sp--];
    }
    size_t size() { return sp+1; }
  };

/**
*  Стэк основанный на статических списках.
*
*  Так как мы всегда добавляем элемент в конец, то в отличие от статического списка фиктивная голова не нужна
*/
  struct StackLinkedListBased {
    StackLinkedListBased()
    : head(0), free(1)
    {
      memset(next,0,sizeof(next));
      memset(val,0,sizeof(val));
    }
    int head;
    int free;
    static const int MAX_N = 10;
    int next[MAX_N];
    int val[MAX_N];

    // добавляем в голову
    void push(int x) {
      val[free] = x;
      next[free] = head;
      head = free;
      ++free;
    }
    int pop() {
      int res = val[head];
      head = next[head];
      return res;
    }
  };

  struct MultiStack {
    MultiStack() : free(0) {
      memset(sp,0,sizeof(sp));
      memset(next,0,sizeof(next));
      memset(val,0,sizeof(val));
    }
    static const int MAX_N_OF_STACKS = 10;
    static const int MAX_N = 100;
    int sp[MAX_N_OF_STACKS]; // верхушки стэка
    int next[MAX_N];
    int val[MAX_N];
    int free;
    void push(int i, int x) {
      next[free] = sp[i];
      sp[i] = free;
      val[free] = x;
      ++free;
    }
    int pop(int i) {
      int res = sp[i];
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
  struct StackMemoryMgmt {
    StackMemoryMgmt() : free(0) {
      memset(sp,0,sizeof(sp));
      memset(next,0,sizeof(next));
      memset(val,0,sizeof(val));
    }
    static const int MAX_N_OF_STACKS = 10;
    static const int MAX_N = 100;
    static const int ID_OF_STACK_WITH_AVAILABLE_CELLS = 0;
    // 0-ой стэк содержит высвобожденные индексы
    int sp[MAX_N_OF_STACKS+1]; // верхушки стэка
    int next[MAX_N];
    int val[MAX_N];
    int free;
    void push(int i, int x) {
      int cell_id = free;
      if(i != ID_OF_STACK_WITH_AVAILABLE_CELLS && !isEmpty(sp[ID_OF_STACK_WITH_AVAILABLE_CELLS])) {
        cell_id = pop(ID_OF_STACK_WITH_AVAILABLE_CELLS);
      } else {
        ++free;
      }
      next[cell_id] = sp[i];
      sp[i] = cell_id;
      val[cell_id] = x;
    }
    int pop(int i) {
      int res = sp[i];
      if(i != ID_OF_STACK_WITH_AVAILABLE_CELLS)
        push(ID_OF_STACK_WITH_AVAILABLE_CELLS, sp[i]); // recollect freed cell for later reusage
      sp[i] = next[sp[i]];
      return res;
    }
    bool isEmpty(int i) {
      return sp[i] == 0;
    }
  };

}

// https://informatics.mccme.ru/mod/statements/view.php?id=33285#1
// Задача A. Простой стек
//
//

//Реализуйте структуру данных "стек".
// Напишите программу, содержащую описание стека и моделирующую работу стека, реализовав все указанные здесь методы.
// Программа считывает последовательность команд и в зависимости от команды выполняет ту или иную операцию.
// После выполнения каждой команды программа должна вывести одну строчку.
//
// Возможные команды для программы:
//
//push n - Добавить в стек число n (значение n задается после команды). Программа должна вывести ok.
//pop - Удалить из стека последний элемент. Программа должна вывести его значение.
//back - Программа должна вывести значение последнего элемента, не удаляя его из стека.
//size - Программа должна вывести количество элементов в стеке.
//clear - Программа должна очистить стек и вывести ok.
//exit - Программа должна вывести bye и завершить работу.
//
//Входные данные
//
//Команды управления стеком вводятся в описанном ранее формате по 1 на строке.
//
//Гарантируется, что набор входных команд удовлетворяет следующим требованиям:
// максимальное количество элементов в стеке в любой момент не превосходит 100,
// все команды pop и back корректны, то есть при их исполнении в стеке содержится хотя бы один элемент.
//Выходные данные
//
//Требуется вывести протокол работы со стеком, по 1 сообщению в строке
//        Примеры
//Входные данные
//
// push 3
// push 14
// size
// clear
// push 1
// back
// push 2
// back
// pop
// size
// pop
// size
// exit
//
//Выходные данные
//
// ok
// ok
// 2
// ok
// ok
// 1
// ok
// 2
// 2
// 1
// 1
// 0
// bye

namespace informatics {
  void solve_simple_stack() {
    my::StackArrayBased s;
    while(1) {
      string cmd;
      cin >> cmd;
      if(cmd == "push") {
        int val;
        cin >> val;
        s.push(val);
        cout << "ok\n";
      }
      else if (cmd == "pop") {
        cout << s.pop() << '\n';
      }
      else if (cmd == "back") {
        cout << s.back() << '\n';
      }
      else if (cmd == "size") {
        cout << s.size() << '\n';
      }
      else if (cmd == "clear") {
        s.clear();
        cout << "ok\n";
      }
      else if (cmd == "exit") {
        cout << "bye\n";
        break;
      }
    }
  }
}
