#include <bits/stdc++.h>
using namespace std;

struct S {
  int x;
};

unique_ptr<S> modify(unique_ptr<S>& ptr) {
  cout << "1\n";
  return move(ptr);
}

unique_ptr<S> modify(unique_ptr<S>&& ptr) {
  cout << "2\n";
  return move(ptr);
}

unique_ptr<S> modify(const unique_ptr<S>& ptr) {
  cout << "3\n";
  return make_unique<S>(*ptr);
}

int main() {
  bitset<32> bs{3};
  cout << bs.count() << '\n';

  return 0;
}
