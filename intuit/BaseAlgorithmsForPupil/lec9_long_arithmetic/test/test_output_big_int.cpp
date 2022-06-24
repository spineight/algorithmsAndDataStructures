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

TEST(output_big_ints, simple) {
  BigInt<10,1> b0("123456789");
  std::stringstream ss;
  ss << b0;
  EXPECT_EQ(ss.str(), "123456789");

  BigInt<100,2> b1("123456789");
  ss.clear();
  ss.str(std::string());
  ss << b1;
  EXPECT_EQ(ss.str(), "123456789");

  BigInt<1000,3> b3("123456789");
  ss.clear();
  ss.str(std::string());
  ss << b1;
  EXPECT_EQ(ss.str(), "123456789");
}

TEST(output_big_ints, withZeros) {
  BigInt<100,2> b0("10000");
  std::stringstream ss;
  ss << b0;
  EXPECT_EQ(ss.str(), "10000");
}