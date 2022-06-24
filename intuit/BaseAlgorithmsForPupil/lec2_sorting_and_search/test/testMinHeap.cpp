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

using namespace std;
bool is_heap(const std::vector<int> &a, int i) {
  int n = a.size() - 1;
  bool ok = true;
  if (i * 2 <= n) {
    if (a[i] > a[i * 2])
      ok = false;
  }
  if (i * 2 + 1 <= n) {
    if (a[i] > a[i * 2 + 1])
      ok = false;
  }
  if (!ok)
    return false;

  bool left = true;
  bool right = true;
  if (i * 2 <= n)
    left = is_heap(a, 2 * i);
  if (i * 2 + 1 <= n)
    right = is_heap(a, 2 * i + 1);
  return left && right;
}

bool is_heap(const std::vector<int> &a) { return is_heap(a, 1); }

TEST(make_heap, hand_picked_array0) {
  std::vector<int> a = { 1, 3, 2, 4, 6, 5, 7, 9, 8 };
  MinHeapStankevich h;
  for (auto &v : a)
    h.insert(v);
  EXPECT_TRUE(is_heap(h.a));
}

TEST(make_heap, hand_picked_array1) {
  std::vector<int> a = { 1,2,3 };
  MinHeapStankevich h;
  for (auto &v : a)
    h.insert(v);
  EXPECT_TRUE(is_heap(h.a));
  EXPECT_EQ(1, h.extract_min());
  EXPECT_TRUE(is_heap(h.a));
  EXPECT_EQ(2, h.extract_min());
  EXPECT_TRUE(is_heap(h.a));
  EXPECT_EQ(3, h.extract_min());
  EXPECT_TRUE(is_heap(h.a));
}

TEST(make_heap, shuffled_array) {
  const int n = 100;
  std::vector<int> a(n);
  std::iota(begin(a), end(a), 0);

  std::random_device rd;
  std::mt19937 urng(rd());

  std::shuffle(begin(a), end(a), urng);

  MinHeapStankevich h;
  for (auto &v : a)
    h.insert(v);
  EXPECT_TRUE(is_heap(h.a));
}

TEST(make_heap, random_array) {
  const int n = 100;
  std::vector<int> a(n);
  std::random_device rd;
  std::mt19937 urng(rd());
  std::generate(begin(a), end(a), [&urng]() { return urng(); });
  MinHeapStankevich h;
  for (auto &v : a)
    h.insert(v);
  EXPECT_TRUE(is_heap(h.a));
}

TEST(make_heap, is_heap) {
  std::vector<int> a = { 1, 2, 3, 1, 4, 5, 6 };
  EXPECT_FALSE(is_heap(a));
  a = { 1, 2, 3, 4, 5 };
  EXPECT_TRUE(is_heap(a));
  a = { 1 };
  EXPECT_TRUE(is_heap(a));
  a = { 1, 2 };
  EXPECT_TRUE(is_heap(a));
  a = { 2, 1 };
  EXPECT_TRUE(is_heap(a));
  a = { 3, 4, 2 };
  EXPECT_FALSE(is_heap(a));
  a = { 3, 6, 9, 7, 5, 10 };
  EXPECT_FALSE(is_heap(a));
}