#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/isZeroIndexedHeap.hpp>
using namespace lec2::practice;
#else

#include <include/isZeroIndexedHeap.hpp>

#endif

using namespace lec2;

#include <vector>
#include <algorithm>
#include <random>

TEST(is_zero_indexed_heap, oneElement) {
  std::vector<int> a = {1};
  EXPECT_TRUE(is_zero_indexed_heap<std::less<> >(a));
}

TEST(is_zero_indexed_heap, handPickedTest) {
  std::vector<int> a = {1, 2};
  EXPECT_TRUE(is_zero_indexed_heap<std::less<> >(a));
  a = {1, 2, 3};
  EXPECT_TRUE(is_zero_indexed_heap<std::less<> >(a));
  a = {1, 2, 3, 5};
  EXPECT_TRUE(is_zero_indexed_heap<std::less<> >(a));
  a = {1, 2, 3, 5, 4};
  EXPECT_TRUE(is_zero_indexed_heap<std::less<> >(a));
  a = {1, 2, 3, 5, 4, 7};
  EXPECT_TRUE(is_zero_indexed_heap<std::less<> >(a));
  a = {1, 2, 3, 5, 4, 7, 6};
  EXPECT_TRUE(is_zero_indexed_heap<std::less<> >(a));
}

TEST(is_zero_indexed_heap, randomVectorHeapifiedWithSTL) {
  int seed = 1272;
  std::mt19937 rng(seed);
  uniform_int_distribution<int> distValues(-1000, 1000);
  uniform_int_distribution<int> distSize(1, 100);
  int n_of_trials = 100;
  while (n_of_trials--) {
    vector<int> a(distSize(rng), 0);
    generate(begin(a), end(a), bind(distValues, ref(rng)));
    make_heap(begin(a), end(a), greater<int>());
    EXPECT_TRUE(is_zero_indexed_heap<less<>>(a));
  }
}

TEST(is_zero_indexed_heap, randomVectorGroundTruthWithSTL) {
  int seed = 1272;
  std::mt19937 rng(seed);
  uniform_int_distribution<int> distValues(-1000, 1000);
  uniform_int_distribution<int> distSize(1, 100);
  int n_of_trials = 100;
  while (n_of_trials--) {
    vector<int> a(distSize(rng), 0);
    generate(begin(a), end(a), bind(distValues, ref(rng)));
    EXPECT_EQ(is_zero_indexed_heap<less<>>(a), is_heap(begin(a),end(a), greater<>()));
  }
}