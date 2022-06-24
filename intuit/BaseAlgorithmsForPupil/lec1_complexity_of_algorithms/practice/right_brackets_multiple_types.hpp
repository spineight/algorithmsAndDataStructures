#include <bits/stdc++.h>
using namespace std;

namespace lec1::practice {
  bool right_brackets_multiple_types(const string& str){
    stack<char> s;

    map<char, bool> isOpen = { {'(', true}, {'[', true}, {'{', true} };
    map<char, char> getClosed = { {'(', ')'}, {'[', ']'}, {'{', '}'} };
    bool isOK = true;
    for(auto ch : str) {
      if(isOpen[ch]) {
        s.push(ch);
      } else if(!s.empty()) {
        char currentOpen = s.top();
        s.pop();
        if(getClosed[currentOpen] != ch) {
          isOK = false;
          break;
        }
      }
      else {
        isOK = false;
        break;
      }
    }

    if(!s.empty()) isOK = false;
    return isOK;
  }
}

namespace informatics {
  // # https://informatics.mccme.ru/mod/statements/view3.php?id=8755&chapterid=51


//  Рассмотрим последовательность, состоящую из круглых, квадратных и фигурных скобок.
//  Программа дожна определить, является ли данная скобочная последовательность правильной.
//
//  Пустая последовательность явлется правильной. Если A – правильная, то последовательности (A), [A], {A} – правильные.
//  Если A и B – правильные последовательности, то последовательность AB – правильная.

//Входные данные
//
//В единственной строке записана скобочная последовательность, содержащая не более 100000 скобок.

//Выходные данные
//
//Если данная последовательность правильная, то программа должна вывести строку yes, иначе строку no.
//Примеры
//        Входные данные
//
//        ()[]
//
//Выходные данные
//
//yes

  void task51_right_brackets_sequence() {

  }

}