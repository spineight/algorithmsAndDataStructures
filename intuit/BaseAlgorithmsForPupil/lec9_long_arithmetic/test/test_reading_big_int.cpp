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

using namespace std;

TEST(reading_big_int, simple) {
  BigInt b0("10000");
  EXPECT_EQ(b0.lnum.back(), 10'000);

  BigInt b1("10000000000"); // 10 000 000 000
  std::vector<int> b1_ground_truth = {0,10};
  EXPECT_EQ(b1.lnum, b1_ground_truth);

  BigInt<10,1> b2("123456789");
  std::vector<int> b2_ground_truth = {9,8,7,6,5,4,3,2,1};
  EXPECT_EQ(b2.lnum,b2_ground_truth);
}
