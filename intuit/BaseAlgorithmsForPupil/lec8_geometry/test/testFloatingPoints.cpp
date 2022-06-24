#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/floating_points.hpp>
using namespace lec8::practice;
#else
#include <include/floating_points.hpp>
using namespace lec8;
#endif

#include <bits/stdc++.h>
using namespace std;
TEST(floatingPoints, testComparision) {
  double Epsilon = 1e-9;
  double a = 1234.56789;
  EXPECT_TRUE(equalDouble(a + Epsilon / 10, a,Epsilon));
  EXPECT_TRUE(lessDouble(a - Epsilon*1.1, a,Epsilon));
  EXPECT_TRUE(greaterDouble(a, a - Epsilon*1.1,Epsilon));
}