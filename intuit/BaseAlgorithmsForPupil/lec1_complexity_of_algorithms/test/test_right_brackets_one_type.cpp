#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/right_brackets_one_type.hpp>
using namespace lec1::practice;
#else
#include <include/right_brackets_one_type.hpp>
using namespace lec1;
#endif

#include <vector>
#include <algorithm>

using namespace std;

TEST(right_brackets_one_type, empty) {
  string str = "";
  EXPECT_TRUE(right_brackets_one_type(str));
}

TEST(right_brackets_one_type, single_element_open) {
  string str = "(";
  EXPECT_FALSE(right_brackets_one_type(str));
}

TEST(right_brackets_one_type, single_element_closed) {
  string str = ")";
  EXPECT_FALSE(right_brackets_one_type(str));
}

TEST(right_brackets_one_type, nested) {
  string str = "((((((((()))))))))";
  EXPECT_TRUE(right_brackets_one_type(str));
}

TEST(right_brackets_one_type, adjacent) {
  string str = "()()()()()()()()()()";
  EXPECT_TRUE(right_brackets_one_type(str));
}

TEST(right_brackets_one_type, nested_adjacent) {
  string str = "((()())())((()())())";
  EXPECT_TRUE(right_brackets_one_type(str));
}

TEST(right_brackets_one_type, nested_adjacent_removed0) {
  string str = "(()())())((()())())";
  EXPECT_FALSE(right_brackets_one_type(str));
}

TEST(right_brackets_one_type, opposite_direction0) {
  string str = ")(";
  EXPECT_FALSE(right_brackets_one_type(str));
}

TEST(right_brackets_one_type, opposite_direction1) {
  string str = ")()(";
  EXPECT_FALSE(right_brackets_one_type(str));
}