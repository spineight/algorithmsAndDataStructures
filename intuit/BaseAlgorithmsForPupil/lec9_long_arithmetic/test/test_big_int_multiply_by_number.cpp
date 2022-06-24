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

TEST(multiply_by_a_number, multiply_by_zero) {
  BigInt<100,2> b0("123456789");
  stringstream ss;
  ss << (b0 * 0);
  EXPECT_EQ(ss.str(), "0");
}

TEST(multiply_by_a_number, multiply_by_max_int) {
  BigInt<1000*1000*1000,9> b0("123456789");
  stringstream ss;
  ss << (b0 * numeric_limits<int>::max());
  EXPECT_EQ(ss.str(), "265121435488629483");
}

TEST(multiply_by_a_number, multiply_multiple_digits_number_by_max_int) {
  BigInt<1000*1000*1000,9> b0("123456789123456789123456789123456789");
  stringstream ss;
  ss << (b0 * numeric_limits<int>::max());
  EXPECT_EQ(ss.str(), "265121435753750918753750918753750918488629483");
}

TEST(multiply_by_a_number, multiply_multiple_digits_number_by_one) {
  BigInt<1000*1000*1000,9> b0("123456789123456789123456789123456789");
  stringstream ss;
  ss << (b0 * 1);
  EXPECT_EQ(ss.str(), "123456789123456789123456789123456789");
}