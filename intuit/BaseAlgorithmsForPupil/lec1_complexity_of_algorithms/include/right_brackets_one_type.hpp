#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace lec1 {
  bool right_brackets_one_type(const string &str) {
    int balance = 0;
    for (char ch : str) {
      if (ch == '(') {
        ++balance;
      } else if (balance > 0) {
        --balance;
      } else {
        --balance;
        break;
      }
    }
    return balance == 0;
  }
}