#include <bits/stdc++.h>
using namespace std;

//! sorts numbers in range [0,255]
void countingSort(vector<size_t>& a) {
  constexpr size_t MAX_VAL{255};
  size_t count[MAX_VAL+1];
  memset(count,  0, sizeof(count));
  for(auto v : a) ++count[v];
  int outPos{0};
  for(size_t i = 0; i <= MAX_VAL;++i) {
    while(count[i] > 0) {
      a[outPos++] = i;
      --count[i];
    }
  }
}

int main() {
  const int n = 10'000;
  constexpr size_t MAX_VAL{255};
  {
    vector<size_t> a0(MAX_VAL+1);
    iota(begin(a0), end(a0), 0);
    countingSort(a0);
    assert(is_sorted(begin(a0), end(a0)));

    vector<size_t> a1(MAX_VAL+1);
    iota(begin(a1), end(a1), 0);
    reverse(begin(a1), end(a1));
    vector<size_t> a2(a1);
    sort(begin(a2), end(a2));
    countingSort(a1);
    assert(a1 == a2);

    //! Random test
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<size_t> dist(0, MAX_VAL);
    vector<size_t> a3(n);
    generate(begin(a3), end(a3), [&]() { return dist(engine); });
    vector<size_t> a4(a3);
    sort(begin(a3), end(a3));
    countingSort(a4);
    assert(a4 == a3);

    //! all elements equal
    vector<size_t> a5 = {5, 5, 5, 5, 5, 5};
    vector<size_t> a6(a5);
    countingSort(a5);
    sort(begin(a6), end(a6));
    assert(a5 == a6);
  }
  return 0;
}