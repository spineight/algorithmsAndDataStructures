#include <bits/stdc++.h>
using namespace std;

void bubble_sort(auto& v) {

}

int main(int argc, char* argv[]) {
  random_device rd;
  mt19937  engine(rd());
  uniform_int_distribution<int> dist(0,100);
  constexpr size_t iters{1000};
  for(size_t i = 0; i < iters; ++i) {
    const size_t n = dist(engine);
    vector<int> v(n);
    generate_n(begin(v), n, [&](){return dist(engine);});
    vector<int> check(v);

  }

}