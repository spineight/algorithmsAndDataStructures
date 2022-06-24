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

TEST(division_by_number_remainder, simple) {
  BigInt<10,1> b0{"9"};
  EXPECT_EQ(b0%3, std::make_pair(BigInt<10,1>("3"),0ll));
  EXPECT_EQ(b0%9, std::make_pair(BigInt<10,1>("1"),0ll));
  EXPECT_EQ(b0%1, std::make_pair(BigInt<10,1>("9"),0ll));

  EXPECT_EQ(b0%2, std::make_pair(BigInt<10,1>("4"),1ll));
  EXPECT_EQ(b0%4, std::make_pair(BigInt<10,1>("2"),1ll));
  EXPECT_EQ(b0%5, std::make_pair(BigInt<10,1>("1"),4ll));
}

TEST(division_by_number_remainder, complex) {
  BigInt<10,1> b0{"99"};
  EXPECT_EQ(b0%3, std::make_pair(BigInt<10,1>("33"),0ll));
  EXPECT_EQ(b0%9, std::make_pair(BigInt<10,1>("11"),0ll));
  EXPECT_EQ(b0%1, std::make_pair(BigInt<10,1>("99"),0ll));

  EXPECT_EQ(b0%2, std::make_pair(BigInt<10,1>("49"),1ll));
  EXPECT_EQ(b0%4, std::make_pair(BigInt<10,1>("24"),3ll));
  EXPECT_EQ(b0%5, std::make_pair(BigInt<10,1>("19"),4ll));
}