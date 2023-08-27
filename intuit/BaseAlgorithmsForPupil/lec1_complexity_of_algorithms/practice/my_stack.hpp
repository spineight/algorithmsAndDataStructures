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
    int a[MAX_SIZE]{0};
    int sp{-1};
    StackArrayBased()  {}

    bool empty() const { return -1 == sp; }
    void push(int x) {
     a[++sp] = x;
    }
    int back() const {
      return a[sp];
    }
    void clear() {sp = -1;}
    void pop() {
      --sp;
    }
    size_t size() { return sp+1; }
  };

/**
*  Стэк основанный на статических списках.
*
*  Так как мы всегда добавляем элемент в конец, то в отличие от статического списка фиктивная голова не нужна
*/
template<size_t sz>
  struct StackLinkedListBased {
    int data[sz]{0};
    int next[sz]{-1};
    int id{0};
    StackLinkedListBased()
    {

    }
    // добавляем в голову
    void push(int x) {

    }
    int pop() {

    }
  };

  struct MultiStack {
    MultiStack()  {

    }

    void push(int i, int x) {

    }
    int pop(int i) {

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
    StackMemoryMgmt()  {

    }

    void push(int i, int x) {

    }
    int pop(int i) {

    }
    bool isEmpty(int i) {

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
    lec1::practice::StackArrayBased<32> s;
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
        cout << s.back()  << '\n';
        s.pop();
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
