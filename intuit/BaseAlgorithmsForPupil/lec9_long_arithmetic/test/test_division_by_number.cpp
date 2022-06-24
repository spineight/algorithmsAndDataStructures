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

TEST(division_by_number, simple) {
  BigInt<10,1> b0{"9"};
  EXPECT_EQ((string)(b0/3), "3");
  EXPECT_EQ((string)(b0/9), "1");
  EXPECT_EQ((string)(b0/1), "9");
}