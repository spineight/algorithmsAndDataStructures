#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/heapify.hpp>
using namespace lec2::practice;
#else
#include <include/heapify.hpp>
#endif

using namespace lec2;

#include <vector>
#include <algorithm>
#include <random>


TEST(heapify, reversed_array) {
  std::vector<int> a = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
  heapify<std::less<> >(a);
  EXPECT_TRUE(is_heap(begin(a),end(a), greater<int>()));
}

TEST(heapify, random_arrays) {
  const size_t n_of_trials = 1000;
  const int seed = 13;
//  std::random_device rd;
//  std::mt19937 urng(rd());
  std::mt19937 urng(seed);
  uniform_int_distribution<int> distVals(-1000,1000);
  uniform_int_distribution<int> distSize(0,1000);
  for (size_t i = 0; i < n_of_trials; ++i) {
    std::vector<int> a(distSize(urng),0);
    std::generate(begin(a), end(a), bind(distVals,ref(urng)));
    heapify<std::less<> >(a);
    EXPECT_TRUE(is_heap(begin(a),end(a), greater<int>()));
  }
}