#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/bubble_sort.hpp>
using namespace algos::practice;
#else
#include <include/bubble_sort.hpp>
using namespace algos;
#endif

#include <vector>
#include <algorithm>
#include <random>

using namespace std;


TEST(bubble_sort, reverse_order) {
  vector<int> a= {9,8,7,6,5,4,3,2,1};
  bubble_sort(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort, empty_vector) {
  vector<int> a;
  bubble_sort(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort, one_element_in_vector) {
  vector<int> a = {1};
  bubble_sort(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort, multiple_equal_elements_in_vector) {
  vector<int> a = {1,1,1,1,1,1};
  bubble_sort(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}
// Bitonic Sequence is a sequence of numbers which is first strictly increasing then after a point strictly decreasing.
TEST(bubble_sort, bitonic_array) {
  vector<int> a = {-10,-5,0,5,3,1,-10};
  bubble_sort(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort, random_shuffled_ordered_array) {
  vector<int> a = {1,2,3,4,5,6,7,8,9};
  random_device rd;
  mt19937 urng(rd());
  shuffle(begin(a), end(a), urng);
  bubble_sort(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort, randomly_constructed_array) {
  const int n = 1000;
  vector<int> a(n,0);
  random_device rd;
  mt19937 urng(rd());
  generate(begin(a), end(a), urng);
  bubble_sort(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}


TEST(bubble_sort_ver2, reverse_order) {
  vector<int> a= {9,8,7,6,5,4,3,2,1};
  bubble_sort_ver2(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort_ver2, empty_vector) {
  vector<int> a;
  bubble_sort_ver2(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort_ver2, one_element_in_vector) {
  vector<int> a = {1};
  bubble_sort_ver2(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort_ver2, multiple_equal_elements_in_vector) {
  vector<int> a = {1,1,1,1,1,1};
  bubble_sort_ver2(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}
// Bitonic Sequence is a sequence of numbers which is first strictly increasing then after a point strictly decreasing.
TEST(bubble_sort_ver2, bitonic_array) {
  vector<int> a = {-10,-5,0,5,3,1,-10};
  bubble_sort_ver2(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort_ver2, random_shuffled_ordered_array) {
  vector<int> a = {1,2,3,4,5,6,7,8,9};
  random_device rd;
  mt19937 urng(rd());
  shuffle(begin(a), end(a), urng);
  bubble_sort_ver2(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}

TEST(bubble_sort_ver2, randomly_constructed_array) {
  const int n = 1000;
  vector<int> a(n,0);
  random_device rd;
  mt19937 urng(rd());
  generate(begin(a), end(a), urng);
  bubble_sort_ver2(a);
  EXPECT_TRUE(is_sorted(begin(a), end(a)));
}