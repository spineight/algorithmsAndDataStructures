#include <gtest/gtest.h>

#include <practice/right_brackets_multiple_types.hpp>

#include <bits/stdc++.h>
using namespace std;

TEST(right_brackets_one_type, empty) {
  EXPECT_TRUE(lec1::practice::right_brackets_multiple_types(""));
}

TEST(right_brackets_one_type, types_missmatch) {
  EXPECT_FALSE(lec1::practice::right_brackets_multiple_types("(][)"));
}
TEST(right_brackets_one_type, intersection) {
  EXPECT_FALSE(lec1::practice::right_brackets_multiple_types("([)]"));
}
TEST(right_brackets_one_type, one_open) {
  EXPECT_FALSE(lec1::practice::right_brackets_multiple_types("("));
}
TEST(right_brackets_one_type, one_closed) {
  EXPECT_FALSE(lec1::practice::right_brackets_multiple_types(")"));
}
TEST(right_brackets_one_type, nested) {
  EXPECT_TRUE(lec1::practice::right_brackets_multiple_types("{[()]}"));
}
TEST(right_brackets_one_type, adjacent) {
  EXPECT_TRUE(lec1::practice::right_brackets_multiple_types("[](){}"));
}
TEST(right_brackets_one_type, nested_adjacent) {
  EXPECT_TRUE(lec1::practice::right_brackets_multiple_types("[[](){}]([](){}){[](){}}"));
}