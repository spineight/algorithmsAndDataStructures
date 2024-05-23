#include <bits/stdc++.h>
using namespace std;

//! Stable sort guarantee that order of equal elements wrt to the comparison function
//! stays the same

//! Stable sort elements in range [0,255]
template<typename ValT>
void stableCountingSort(vector<ValT>& a, auto getKeyFn) {
  if(!a.empty()) {
    constexpr size_t MAX_VAL{255};
    size_t count[MAX_VAL + 1];
    memset(count, 0, sizeof(count));

    for (auto v: a) ++count[getKeyFn(v)];

    //! build prefix sums array
    //! count[val] - position in res array of element with val
    //! 0 0 0 0 0 0    1 1 1        2
    //!           v        v        v
    //!         cnt[0]   cnt[1]   cnt[2]
    for (size_t i = 1; i <= MAX_VAL; ++i)
      count[i] += count[i - 1];

    vector<ValT> res(a);
    for (int i = a.size() - 1; i >= 0; --i) {
      //! NB!!! --count, as count is number of elements, but we need position in 0 indexed array!!!
      res[--count[getKeyFn(a[i])]] = a[i];
    }
    a = std::move(res);
  }
}

void print(const auto& a) {
  for(const auto& [first, second] : a)
    cout << "(" << first << "," << second << ") ";
  cout << '\n';
}

int main() {
  vector<pair<size_t, size_t>> a = { {1,3}, {1,2}, {2,2}, {2,3}, {1,1}, {1,4},{5,5} };
  print(a);
  stableCountingSort(a, [](const pair<size_t,size_t>& p){return p.second;});
  print(a);
  stableCountingSort(a, [](const pair<size_t,size_t>& p){return p.first;});
  print(a);
  return 0;
}