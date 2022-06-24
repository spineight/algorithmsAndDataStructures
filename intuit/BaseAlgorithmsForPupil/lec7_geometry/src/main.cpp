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


int main() {
  return 0;
}