#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/ray.hpp>
using namespace lec7::practice;
#else
#include <include/ray.hpp>
using namespace lec7;
#endif

#include <bits/stdc++.h>
using namespace std;

TEST(ray, hasPoint) {
  Ray r0(2,0,0,2);
  EXPECT_TRUE(r0.has(0,2));
  EXPECT_TRUE(r0.has(1.1,2));
  EXPECT_TRUE(r0.has(1.1111,2.));
  EXPECT_FALSE(r0.has(-1,2));
  EXPECT_FALSE(r0.has(-1.1111,2));

  Ray r1(1,1,0,0);
  EXPECT_TRUE(r1.has(2,2));
  EXPECT_TRUE(r1.has(3.333333333,3.333333333));
  EXPECT_TRUE(r1.has(4.333333333,4.333333333));
  EXPECT_FALSE(r1.has(3.333333331,3.333333333));
  EXPECT_FALSE(r1.has(-4,-4));
}