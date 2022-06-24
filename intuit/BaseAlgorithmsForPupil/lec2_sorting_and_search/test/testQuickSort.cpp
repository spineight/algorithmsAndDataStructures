#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/quick_sort.hpp>
using namespace lec2::practice;
#else
#include <include/quick_sort.hpp>
#endif

using namespace lec2;

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

TEST(quick_sort, random_array) {
  // Важно проверить, что отсортированный массив имеет те же элементы, что начальный
  const size_t n_of_trials = 10000;
  std::random_device rd;
  std::mt19937 urng(rd());
  std::uniform_int_distribution<int> num_dist(-1000, 1000);
  std::uniform_int_distribution<int> size_dist(1, 100);
  for (size_t i = 0; i < n_of_trials; ++i) {
    std::vector<int> a(size_dist(urng));
    std::generate(begin(a), end(a), std::bind(num_dist, ref(urng)));
    std::vector<int> a_initial{a};
    std::sort(begin(a_initial),end(a_initial));
    const int n = a.size();
    quick_sort(a, 0, n - 1);
    for(size_t j = 0; j < a_initial.size(); ++j) {
      EXPECT_EQ(a_initial[j], a[j]);
    }
    EXPECT_TRUE(is_sorted(begin(a), end(a)));
  }
}

TEST(quick_sort, handPicked) {
    vector<int> a = {1, 3, 1, 2, 3, 4};
    quick_sort(a, 0, a.size() - 1);
    EXPECT_TRUE(is_sorted(begin(a), end(a)));
}