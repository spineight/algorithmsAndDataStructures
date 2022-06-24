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

TEST(comapre_big_ints, first_smaller) {
BigInt<100,2> b0("1");
BigInt<100,2> b1("10000");
EXPECT_TRUE(b0 < b1);
}

TEST(comapre_big_ints, _small_second) {
BigInt<100,2> b0("10000");
BigInt<100,2> b1("1");
EXPECT_TRUE(b1 < b0);
}

TEST(comapre_big_ints, equal) {
BigInt<100,2> b0("1000");
BigInt<100,2> b1("1000");
EXPECT_TRUE(!(b0<b1) && !(b1<b0));
}

TEST(comapre_big_ints, equal_length) {
  BigInt<100,2> b0("1100");
  BigInt<100,2> b1("1010");
  EXPECT_FALSE(b0<b1);
}

TEST(comapre_big_ints, same_length_first_greater) {
  BigInt<100,2> b0("223456781");
  BigInt<100,2> b1("123456789");
  EXPECT_FALSE(b0<b1);
}