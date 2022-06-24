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

TEST(big_ints_multiplication, multiply_by_zero) {
  BigInt<100,2> b0("123456789");
  BigInt<100,2> b1("0");
  stringstream ss;
  ss << (b0 * b1);
  EXPECT_EQ(ss.str(), "0");
}

TEST(big_ints_multiplication, multiply_by_max_int) {
  BigInt<1000*1000*1000,9> b0("123456789");
  BigInt<1000*1000*1000,9> b1("2147483647");
  stringstream ss;
  ss << (b0 * b1);
  EXPECT_EQ(ss.str(), "265121435488629483");
}

TEST(big_ints_multiplication, multiply_multiple_digits_number_by_max_int) {
  BigInt<1000*1000*1000,9> b0("123456789123456789123456789123456789");
  BigInt<1000*1000*1000,9> b1("2147483647");
  stringstream ss;
  ss << (b0 * b1);
  EXPECT_EQ(ss.str(), "265121435753750918753750918753750918488629483");
}

TEST(big_ints_multiplication, multiply_multiple_digits_number_by_one) {
  BigInt<1000*1000*1000,9> b0("123456789123456789123456789123456789");
  BigInt<1000*1000*1000,9> b1("1");
  stringstream ss;
  ss << (b0 * b1);
  EXPECT_EQ(ss.str(), "123456789123456789123456789123456789");
}

// I did check in Python
TEST(big_ints_multiplication, multiply_two_multiple_digits_numbers) {
  BigInt<1000*1000*1000,9> b0("123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789");
  BigInt<1000*1000*1000,9> b1("123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789123456789");
  stringstream ss;
  ss << (b0 * b1);
  EXPECT_EQ(ss.str(), "15241578780673678546105778311537878076969977842402077607834177373266277138698376904130476669562576434994676200426775965858875731290975496723075231672017466239917700807817935375718169943618404511518639079418873647319108215219342783119577351019811918920046486820281054720515622620750190521");
}

TEST(big_ints_multiplication, smaller_by_larger) {
  BigInt<1000*1000*1000,9> b0("123456789123456789123456789123456789");
  BigInt<1000*1000*1000,9> b1("2147483647");
  stringstream ss;
  ss << (b1 * b0);
  EXPECT_EQ(ss.str(), "265121435753750918753750918753750918488629483");
}