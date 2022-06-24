#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/line.hpp>
using namespace lec7::practice;
#else
#include <include/segment.hpp>
using namespace lec7;
#endif

#include <bits/stdc++.h>
using namespace std;

TEST(segment,hasPointMethod1) {
  Segment s0(0,0,3,3);
  EXPECT_TRUE(s0.hasPointMethod1(1,1));
  EXPECT_TRUE(s0.hasPointMethod1(1.111,1.111));
  EXPECT_TRUE(s0.hasPointMethod1(0,0));
  EXPECT_TRUE(s0.hasPointMethod1(3,3));
  EXPECT_FALSE(s0.hasPointMethod1(3.000000001,3.000000001));
  EXPECT_FALSE(s0.hasPointMethod1(-.000000001,-.000000001));
}

TEST(segment,hasPointMethod2) {
  Segment s0(0,0,3,3);
  EXPECT_TRUE(s0.hasPointMethod2(1,1));
  EXPECT_TRUE(s0.hasPointMethod2(1.111,1.111));
  EXPECT_TRUE(s0.hasPointMethod2(0,0));
  EXPECT_TRUE(s0.hasPointMethod2(3,3));
  EXPECT_FALSE(s0.hasPointMethod2(3.000000001,3.000000001));
  EXPECT_FALSE(s0.hasPointMethod2(-.000000001,-.000000001));
}