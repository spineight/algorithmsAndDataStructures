#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/line.hpp>
using namespace lec7::practice;
#else
#include <include/line.hpp>
using namespace lec7;
#endif

#include <bits/stdc++.h>
using namespace std;



TEST(line, distToOrigin) {
  // (1)
  double dy = 0;
  double dx = 2;
  double px = 0;
  double py = 2;
  Line l0(dx,dy,px,py);
  EXPECT_EQ(abs(l0.distToOrigin()), 2);

  // (2)
  dy = 2;
  dx = 0;
  px = 2;
  py = 0;
  Line l1(dx,dy,px,py);
  EXPECT_DOUBLE_EQ(abs(l1.distToOrigin()), 2);

  // (3)
  dy = 2;
  dx = 2;
  px = 0;
  py = 0;
  Line l2(dx,dy,px,py);
  EXPECT_DOUBLE_EQ(abs(l2.distToOrigin()), 0);

  // (4)
  dy = 2;
  dx = 2;
  px = -2;
  py = 0;
  Line l3(dx,dy,px,py);
  EXPECT_DOUBLE_EQ(abs(l3.distToOrigin()), sqrt(2));
}

TEST(line, has) {
  // (1)
  double dy = 0;
  double dx = 2;
  double px = 0;
  double py = 2;
  Line l0(dx,dy,px,py);
  EXPECT_TRUE(l0.has(0,2));
  EXPECT_TRUE(l0.has(-1,2));
  EXPECT_TRUE(l0.has(1,2));

  // (2)
  dy = 2;
  dx = 0;
  px = 2;
  py = 0;
  Line l1(dx,dy,px,py);
  EXPECT_TRUE(l1.has(2,0));
  EXPECT_TRUE(l1.has(2,1));
  EXPECT_TRUE(l1.has(2,-1));

  // (3)
  dy = 2;
  dx = 2;
  px = 0;
  py = 0;
  Line l2(dx,dy,px,py);
  EXPECT_TRUE(l2.has(0,0));
  EXPECT_TRUE(l2.has(1,1));
  EXPECT_TRUE(l2.has(-1,-1));


  // (4)
  dy = 2;
  dx = 2;
  px = -2;
  py = 0;
  Line l3(dx,dy,px,py);
  EXPECT_TRUE(l3.has(-2,0));
  EXPECT_TRUE(l3.has(-1,1));
  EXPECT_TRUE(l3.has(-3,-1));
}

TEST(line, distToPoint) {
  // (1)
  double dy = 0;
  double dx = 2;
  double px = 0;
  double py = 2;
  Line l0(dx,dy,px,py);
  EXPECT_EQ(abs(l0.distToPoint(0,0)), 2);
  EXPECT_EQ(abs(l0.distToPoint(0,2)), 0);
  EXPECT_EQ(abs(l0.distToPoint(-3,3)), 1);
  EXPECT_EQ(abs(l0.distToPoint(3,3)), 1);

  // (2)
  dy = 2;
  dx = 0;
  px = 2;
  py = 0;
  Line l1(dx,dy,px,py);
  EXPECT_DOUBLE_EQ(abs(l1.distToPoint(0,0)), 2);
  EXPECT_DOUBLE_EQ(abs(l1.distToPoint(2,0)), 0);
  EXPECT_DOUBLE_EQ(abs(l1.distToPoint(-3,3)), 5);
  EXPECT_DOUBLE_EQ(abs(l1.distToPoint(3,3)), 1);

  // (3)
  dy = 2;
  dx = 2;
  px = 0;
  py = 0;
  Line l2(dx,dy,px,py);
  EXPECT_DOUBLE_EQ(abs(l2.distToPoint(0,0)), 0);
  EXPECT_DOUBLE_EQ(abs(l2.distToPoint(1,1)), 0);
  EXPECT_DOUBLE_EQ(abs(l2.distToPoint(-3,3)), sqrt(2)* 3);
  EXPECT_DOUBLE_EQ(abs(l2.distToPoint(3,3)), 0);

  // (4)
  dy = 2;
  dx = 2;
  px = -2;
  py = 0;
  Line l3(dx,dy,px,py);
  EXPECT_DOUBLE_EQ(abs(l3.distToPoint(0,0)), sqrt(2));
  EXPECT_DOUBLE_EQ(abs(l3.distToPoint(-1,1)), 0);
  EXPECT_DOUBLE_EQ(abs(l3.distToPoint(-3,3)), sqrt(2) * 2);
  EXPECT_DOUBLE_EQ(abs(l3.distToPoint(3,3)), sqrt(2));
}

TEST(line, intersects) {
  // (1)
  double dy = 0;
  double dx = 2;
  double px = 0;
  double py = 2;
  Line l0(dx, dy, px, py);

  dy = 2;
  dx = 0;
  px = 2;
  py = 0;
  Line l1(dx,dy,px,py);

  dy = 2;
  dx = 2;
  px = 0;
  py = 0;
  Line l2(dx,dy,px,py);

  dy = 2;
  dx = 2;
  px = -2;
  py = 0;
  Line l3(dx,dy,px,py);

  auto intersectionPoint = l0.intersects(l1);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(2.,2.));
  intersectionPoint = l1.intersects(l0);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(2.,2.));

  intersectionPoint = l0.intersects(l2);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(2.,2.));
  intersectionPoint = l2.intersects(l0);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(2.,2.));

  intersectionPoint = l0.intersects(l3);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(0.,2.));
  intersectionPoint = l3.intersects(l0);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(0.,2.));

  intersectionPoint = l1.intersects(l2);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(2.,2.));
  intersectionPoint = l2.intersects(l1);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(2.,2.));

  intersectionPoint = l1.intersects(l3);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(2.,4.));
  intersectionPoint = l3.intersects(l1);
  EXPECT_TRUE(intersectionPoint.has_value());
  EXPECT_EQ(intersectionPoint.value(), std::make_pair(2.,4.));

  intersectionPoint = l2.intersects(l3);
  EXPECT_FALSE(intersectionPoint.has_value());
}

