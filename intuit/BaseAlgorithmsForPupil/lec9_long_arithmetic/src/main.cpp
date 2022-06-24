#include <bits/stdc++.h>
using namespace std;

#define show_vars(args...) { \
  string names = #args; \
  replace(begin(names), end(names), ',' , ' ');\
  stringstream ss(names); \
  istream_iterator<string> it(ss);\
  _show_vars(it, args);\
}

void _show_vars(istream_iterator<string>& it) {
  cout << "!\n";
}

template<typename T, typename ... TArgs>
void _show_vars(istream_iterator<string>& it, const T& val, TArgs ... args) {
  cout << *it++ << ":" << val << '\n';
  _show_vars(it, args...);
}

#include <big_int.hpp>


int main() {
//  lec9_long_arithmetic::BigInt bi0("12345678123"), bi1("010000"), bi2("1000"), bi3("0");
//  cout << bi0 << "," << bi1 << "," << bi2 << "," << bi3 << '\n';

//  cout << lec9_long_arithmetic::BigInt ("50") +  lec9_long_arithmetic::BigInt("50") << '\n';
//  cout << lec9_long_arithmetic::BigInt ("99999999") +  lec9_long_arithmetic::BigInt("1") << '\n';
//  cout << lec9_long_arithmetic::BigInt ("1") +  lec9_long_arithmetic::BigInt("999") << '\n';

  lec9_long_arithmetic::BigInt ("10000");
  lec9_long_arithmetic::BigInt("1");
  cout << (lec9_long_arithmetic::BigInt ("999999999") +  lec9_long_arithmetic::BigInt("999999999")) << '\n';
  cout << numeric_limits<int>::max() << '\n';

//  lec9_long_arithmetic::BigInt first("12345"),second("54321");
//  cout << first << "," << second << '\n';
//  cout << (first + second) << '\n';
//
//  lec9_long_arithmetic::BigInt third("999"), fourth("999");
//  cout << third + fourth << '\n';
//  cout << third * 10000 << '\n';
//
//  lec9_long_arithmetic::BigInt num0("90000"), num1("1");
//  cout << num1 - num0 << '\n';
//
//  lec9_long_arithmetic::BigInt num3("24682468");
//  lec9_long_arithmetic::BigInt num4("2");
//  cout << num3 / 2 << '\n';
  return 0;
}