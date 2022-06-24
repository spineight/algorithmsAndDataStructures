#include <bits/stdc++.h>
using namespace std;

#include <MultiStackMemoryMgmt.hpp>

void task51_right_brackets_sequence() {
  string str;
  cin >> str;
  stack<char> s;
  map<char, bool> isOpen( { {'(', true}, {'[', true}, {'{', true} });
  map<char,char> closed( { {'(',')'}, {'[',']'}, {'{','}'} });

  bool isOK = true;
  for(auto ch : str) {
    if(isOpen[ch]) {
      s.push(ch);
    } else {
      if(s.empty() || closed[s.top()] != ch) {
        isOK = false;
        break;
      }
      s.pop();
    }
  }
  if(!s.empty()) isOK = false;

  if(isOK) cout << "yes\n";
  else cout << "no\n";
}

int main(int argc, char* argv[]) {
//  task51_right_brackets_sequence();
  using namespace lec1;
  constexpr int N_OF_ELEMENTS = 4;
  MultiStackMemoryMgmt<1+2, N_OF_ELEMENTS> list; // 1 - стек свободных индексов, + 2 - стеки с данными
  for(int i = 1; i <= N_OF_ELEMENTS / 2; ++i) {
    cout << list << '\n';
    list.push(1,i);
    cout << list << '\n';
    list.push(2,i);
    cout << list << '\n';
    cout << list.pop(1) << '\n';
    cout << list << '\n';
    cout << list.pop(2) << '\n';
    cout << list << '\n';
    (list.empty(1));
    (list.empty(2));
  }
}