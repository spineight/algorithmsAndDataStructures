#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/turtle.hpp>
using namespace lec3::practice;
#else
#include <include/turtle.hpp>
using namespace lec3;
#endif

TEST(turtle, n_of_ways_to_get) {
  //   (0,0)
  //    0     1     2     3
  // 0  *     *     *     *
  // 1  *     *     *     *
  // 2  *     *     *     *
  // 3  *     *     *     *
  //       (2,3)
  EXPECT_EQ(turtle(2,2), 6);
  EXPECT_EQ(turtle(0,0), 1);
  EXPECT_EQ(turtle(0,1), 1);
  EXPECT_EQ(turtle(0,2), 1);
  EXPECT_EQ(turtle(1,0), 1);
  EXPECT_EQ(turtle(2,0), 1);
  EXPECT_EQ(turtle(1,1), 2);
  EXPECT_EQ(turtle(1,2), 3);
  EXPECT_EQ(turtle(1,3), 4);
  EXPECT_EQ(turtle(2,3), 10);
  EXPECT_EQ(turtle(2,1), 3);
  EXPECT_EQ(turtle(3,0), 1);
  EXPECT_EQ(turtle(3,1), 4);
  EXPECT_EQ(turtle(3,2), 10);
  EXPECT_EQ(turtle(3,3), 20);
}

TEST(turtle, max_money) {
  vector<pair<int,int>> res = { {0,0}, {1,0}, {2,0}, {3,0}, {3,1}, {3,2}, {3,3} };
  EXPECT_EQ(turtle_and_money(3,3, {
          {0,0,0,0},
          {1,0,0,0},
          {1,0,0,0},
          {1,1,1,1}
  }), res);

  res = { {0,0}, {0,1}, {0,2}, {0,3}, {1,3}, {2,3}, {3,3} };
  EXPECT_EQ(turtle_and_money(3,3, {
          {0,1,1,1},
          {0,0,0,1},
          {0,0,0,1},
          {0,0,0,1}
  }), res);

  res = { {0,0}, {0,1}, {0,2}, {0,3}, {1,3}, {2,3}, {3,3} };
  EXPECT_EQ(turtle_and_money(3,3, {
          {0,1,1,1},
          {1,0,0,2},
          {1,0,0,1},
          {1,1,1,1}
  }), res);

  res = { {0,0}, {1,0}, {2,0}, {3,0}, {3,1}, {3,2}, {3,3} };
  EXPECT_EQ(turtle_and_money(3,3, {
          {0,1,1,1},
          {1,0,0,1},
          {1,0,0,1},
          {1,2,1,1}
  }), res);

  res = { {0,0}, {0,1}, {0,2}, {1,2}, {1,3}, {2,3}, {3,3} };
  EXPECT_EQ(turtle_and_money(3,3, {
          {0, 1,1,1},
          {4,-4,5,5},
          {1,-4,0,1},
          {1, 2,1,1}
  }), res);
}

TEST(turtle, negative_money) {
  vector<pair<int, int>> res = {{0, 0},
                                {1, 0},
                                {2, 0},
                                {3, 0},
                                {3, 1},
                                {3, 2},
                                {3, 3}};
  EXPECT_EQ(turtle_and_money(3, 3, {
          {0, 0, 0,  0},
          {0, 0, 0,  0},
          {0, 0, 0,  -2},
          {0, 0, -1, 0}
  }), res);
}