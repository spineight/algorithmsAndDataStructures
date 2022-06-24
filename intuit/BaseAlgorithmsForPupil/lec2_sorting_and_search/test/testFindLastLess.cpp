#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/binary_search.hpp>
using namespace lec2::practice;
#else
#include <include/binary_search.hpp>
#endif

using namespace lec2;

#include <vector>
#include <random>

using namespace std;

TEST(find_last_less, hand_picked_arrays) {
  vector<int> a = { 1, 2, 3, 3, 4, 5, 6 };
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 3) == 1);

  a = { 1, 2, 3, 4, 5, 6 };
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 3) == 1);

  a = { 3, 3, 3, 3, 3, 3 };
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 3) == -1);
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 1) == -1);

  a = { 1, 2, 3, 3, 3, 4, 5, 6 };
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 3) == 1);

  a = { 1, 1, 1, 3, 3, 4, 5, 6 };
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 3) == 2);

  a = { 1, 1, 2, 3, 3, 4, 5, 6 };
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 3) == 2);

  a = { 1, 1, 2, 3, 3, 4, 5, 6, 6, 6 };
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 6) == 6);

  a = { 1, 1, 2, 3, 3, 4, 5, 6, 6 };
  EXPECT_TRUE(
      binary_search_find_last_less(
          a, 7) == 8);
}

TEST(find_last_lessDeathTest, non_sorted_array) {
  vector<int> a = { 1, 3, 2, 4, 6, 5 };
  EXPECT_DEBUG_DEATH(
      binary_search_find_last_less(a,
                                                                           1),
      "array should be sorted");
}