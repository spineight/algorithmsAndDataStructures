#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/heapSort.hpp>
using namespace lec2::practice;
#else
#include <include/heapSort.hpp>
#endif

using namespace lec2;

#include <vector>
#include <algorithm>
#include <random>

TEST(heap_sort, random_arrays) {
  const size_t n_of_trials = 1000;
//  std::random_device rd;
  const int seed = 17;
//  std::mt19937 urng(rd());
  std::mt19937 urng(seed);
  uniform_int_distribution<int> distSize(0,1000);
  uniform_int_distribution<int> distVal(-1000,1000);
  for (size_t i = 0; i < n_of_trials; ++i) {
    std::vector<int> a(distSize(urng));
    std::generate(begin(a), end(a), bind(distVal,ref(urng)));
    heap_sort(a);
    EXPECT_TRUE(is_sorted(begin(a), end(a)));
  }
}