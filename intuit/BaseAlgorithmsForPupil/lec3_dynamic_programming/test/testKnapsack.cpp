#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/knapsack.hpp>
using namespace lec3::practice;
#else
#include <include/knapsack.hpp>
using namespace lec3;
#endif

TEST(knapsack, show_that_greedy_not_work) {
  EXPECT_EQ(knapsack({4,3,3}, {9,5,5},6), 10);
}

TEST(knapsack, can_take_all) {
  EXPECT_EQ(knapsack({1,1,1}, {2,2,2},3), 6);
}

TEST(knapsack, can_take_none) {
  EXPECT_EQ(knapsack({2,2,2}, {2,2,2},1), 0);
}

TEST(knapsack, can_take_one) {
  EXPECT_EQ(knapsack({2,2,2,1}, {2,2,2,1},1), 1);
}

TEST(knapsack, restore_answers) {
  vector<int> expected = {5,5};
  EXPECT_EQ(knapsack_find_items({4,3,3}, {9,5,5},6), expected);

  expected = {2,2,2};
  EXPECT_EQ(knapsack_find_items({1,1,1}, {2,2,2},3), expected);

  expected = {};
  EXPECT_EQ(knapsack_find_items({2,2,2}, {2,2,2},1), expected);

  expected = {1};
  EXPECT_EQ(knapsack_find_items({2,2,2,1}, {2,2,2,1},1), expected);
}