#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/big_int.hpp>
using namespace lec9::practice;
#else
#include <include/big_int.hpp>
using namespace lec9;
#endif

#include <vector>
#include <algorithm>
#include <random>
#include <sstream>

using namespace std;

TEST(adding_big_ints, simple) {
  BigInt<100,2> b0("10000");
  BigInt<100,2> b1("10000");
  std::stringstream ss;
  ss << (b0 + b1);
  EXPECT_EQ(ss.str(), "20000");
}

TEST(adding_big_ints, differentOrderSameResult) {
  BigInt<100,2> b0("12345");
  BigInt<100,2> b1("11111");
  std::stringstream ss;
  ss << (b0 + b1);
  EXPECT_EQ(ss.str(), "23456");

  ss.clear();
  ss.str("");
  ss << (b1 + b0);
  EXPECT_EQ(ss.str(), "23456");
}

TEST(adding_big_ints, different_length_small_first) {
  BigInt<100,2> b0("1");
  BigInt<100,2> b1("10000");
  std::stringstream ss;
  ss << (b0 + b1);
  EXPECT_EQ(ss.str(), "10001");
}

TEST(adding_big_ints, result_number_has_more_digits_than_added_numbers_0) {
  BigInt<100,2> b0("999");
  BigInt<100,2> b1("1");
  std::stringstream ss;
  ss << (b0 + b1);
  EXPECT_EQ(ss.str(), "1000");
}

TEST(adding_big_ints, result_number_has_more_digits_than_added_numbers_1) {
  BigInt<100,2> b0("1");
  BigInt<100,2> b1("999");
  std::stringstream ss;
  ss << (b0 + b1);
  EXPECT_EQ(ss.str(), "1000");
}

TEST(adding_big_ints, test_if_type_of_array_element_enough_to_keep_result) {
  BigInt<100,2> b0("999999999");
  BigInt<100,2> b1("999999999");
  std::stringstream ss;
  ss << (b0 + b1);
  EXPECT_EQ(ss.str(), "1999999998");
}
