#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/heap.hpp>
using namespace lec2::practice;
#else
#include <include/heap.hpp>
#endif

using namespace lec2;

#include <vector>
#include <algorithm>
#include <random>

TEST(MinHeapStankevich, using_min_heap_for_sorting) {
  MinHeapStankevich h;
  std::vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8 };
  std::random_device rd;
  std::mt19937 urng(rd());
  std::shuffle(begin(a), end(a), urng);
  for (auto v : a)
    h.insert(v);
  std::vector<int> a1;
  while (!h.empty())
    a1.push_back(h.extract_min());
  EXPECT_TRUE(is_sorted(begin(a1), end(a1)));
}


TEST(MinHeapStankevich, using_min_heap_for_sorting_n_random_arrays) {
  const size_t n_of_trials = 100;
  const size_t n = 100;
  std::random_device rd;
  std::mt19937 urng(rd());
  for (size_t i = 0; i < n_of_trials; ++i) {
    MinHeapStankevich h;
    std::vector<int> a(n);
    std::generate(begin(a), end(a), urng);
    for (auto v : a)
      h.insert(v);
    std::vector<int> a1;
    while (!h.empty())
      a1.push_back(h.extract_min());
    EXPECT_TRUE(is_sorted(begin(a1), end(a1)));
  }
}

TEST(MinHeapStankevich,
     using_max_heap_for_sorting_in_descending_order_n_random_arrays) {
  const size_t n_of_trials = 100;
  const size_t n = 100;
  std::random_device rd;
  std::mt19937 urng(rd());
  for (size_t i = 0; i < n_of_trials; ++i) {
    MinHeapStankevich h;
    std::vector<int> a(n);
    std::generate(begin(a), end(a), urng);
    for (auto v : a)
      h.insert(v);
    std::vector<int> a1;
    while (!h.empty())
      a1.push_back(h.extract_min());
    EXPECT_TRUE(is_sorted(begin(a1), end(a1), std::greater_equal<>()));
  }
}

TEST(HeapInZeroIndexedArray, using_min_heap_for_sorting) {
  HeapInZeroIndexedArray<std::less_equal<>> h;
  std::vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8 };
  std::random_device rd;
  std::mt19937 urng(rd());
  std::shuffle(begin(a), end(a), urng);
  for (auto v : a)
    h.insert(v);
  std::vector<int> a1;
  while (!h.empty())
    a1.push_back(h.get_front());
  EXPECT_TRUE(is_sorted(begin(a1), end(a1)));
}

TEST(HeapInZeroIndexedArray, using_max_heap_for_sorting_in_descending_order) {
  HeapInZeroIndexedArray<std::greater_equal<>> h;
  std::vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8 };
  std::random_device rd;
  std::mt19937 urng(rd());
  std::shuffle(begin(a), end(a), urng);
  for (auto v : a)
    h.insert(v);
  std::vector<int> a1;
  while (!h.empty())
    a1.push_back(h.get_front());
  EXPECT_TRUE(is_sorted(begin(a1), end(a1), std::greater<>()));
}

TEST(HeapInZeroIndexedArray, using_min_heap_for_sorting_n_random_arrays) {
  const size_t n_of_trials = 100;
  const size_t n = 100;
  std::random_device rd;
  std::mt19937 urng(rd());
  for (size_t i = 0; i < n_of_trials; ++i) {
    HeapInZeroIndexedArray<std::less_equal<>> h;
    std::vector<int> a(n);
    std::generate(begin(a), end(a), urng);
    for (auto v : a)
      h.insert(v);
    std::vector<int> a1;
    while (!h.empty())
      a1.push_back(h.get_front());
    EXPECT_TRUE(is_sorted(begin(a1), end(a1)));
  }
}

TEST(HeapInZeroIndexedArray,
     using_max_heap_for_sorting_in_descending_order_n_random_arrays) {
  const size_t n_of_trials = 100;
  const size_t n = 100;
  std::random_device rd;
  std::mt19937 urng(rd());
  for (size_t i = 0; i < n_of_trials; ++i) {
    HeapInZeroIndexedArray<std::greater_equal<>> h;
    std::vector<int> a(n);
    std::generate(begin(a), end(a), urng);
    for (auto v : a)
      h.insert(v);
    std::vector<int> a1;
    while (!h.empty())
      a1.push_back(h.get_front());
    EXPECT_TRUE(is_sorted(begin(a1), end(a1), std::greater<>()));
  }
}