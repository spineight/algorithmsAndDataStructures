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

TEST(substruct_big_ints, simple) {
  BigInt<100,2> b0("10000");
  BigInt<100,2> b1("10000");
  std::stringstream ss;
  ss << (b0 - b1);
  EXPECT_EQ(ss.str(), "0");
}

TEST(substruct_big_ints, different_length_small_second) {
  BigInt<100,2> b0("10000");
  BigInt<100,2> b1("1");
  std::stringstream ss;
  ss << (b0 - b1);
  EXPECT_EQ(ss.str(), "9999");
}

TEST(substruct_big_ints, carry) {
  BigInt<10,1> b0("100");
  BigInt<10,1> b1("23");
  std::stringstream ss;
  ss << (b0 - b1);
  EXPECT_EQ(ss.str(), "77");

  BigInt<100,2> b2("100");
  BigInt<100,2> b3("2");
  ss.clear();
  ss.str(std::string());
  ss << (b2 - b3);
  EXPECT_EQ(ss.str(), "98");
}

TEST(substruct_big_ints, result_number_has_less_digits_than_added_numbers_0) {
  BigInt<100,2> b0("1000");
  BigInt<100,2> b1("1");
  std::stringstream ss;
  ss << (b0 - b1);
  EXPECT_EQ(ss.str(), "999");
}