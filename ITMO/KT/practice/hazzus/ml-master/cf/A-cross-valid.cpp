#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::pair<int, int>> objs(n);
  for (std::size_t i = 0; i < n; i++) {
    std::cin >> objs[i].second;
    objs[i].first = i + 1;
  }
  std::sort(objs.begin(), objs.end(), [](auto a, auto b){ return a.second < b.second; });
  std::vector<std::vector<int>> answer(k);
  for (std::size_t i = 0; i < n; i++) {
    answer[i % k].push_back(objs[i].first);
  }
  for (auto const& x : answer) {
    std::cout << x.size() << " ";
    for (int a : x) {
      std::cout << a << " ";
    }
    std::cout << std::endl;
  }
}
