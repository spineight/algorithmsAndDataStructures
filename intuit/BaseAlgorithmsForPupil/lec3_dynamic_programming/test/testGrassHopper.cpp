#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/grasshopper.hpp>
using namespace lec3::practice;
#else
#include <include/grasshopper.hpp>
using namespace lec3
#endif

TEST(grassHopper, jumps_1_2) {
  // n = 3
  // #
  // 0    1    2    3
  //    1    1    1
  //    1    2
  //    2    1
  EXPECT_EQ(grasshopper_1_2(3),3);

  // n = 4
  // 1 1 1 1
  // 1 1 2
  // 1 2 1
  // 2 1 1
  // 2 2
  EXPECT_EQ(grasshopper_1_2(4),5);

  EXPECT_EQ(grasshopper_1_2(5),8);

  EXPECT_EQ(grasshopper_1_2(2),2);
  EXPECT_EQ(grasshopper_1_2(1),1);
  EXPECT_EQ(grasshopper_1_2(0),1);
}

TEST(grassHopper, jumps_k) {
  EXPECT_EQ(grasshopper(3,2),3);

  // n = 4
  // 1 1 1 1
  // 1 1 2
  // 1 2 1
  // 2 1 1
  // 2 2
  EXPECT_EQ(grasshopper(4,2),5);

  // n = 4
  // 1 1 1 1
  // 1 1 2
  // 1 2 1
  // 1 3
  // 2 1 1
  // 2 2
  // 3 1
  EXPECT_EQ(grasshopper(4,3),7);
  EXPECT_EQ(grasshopper(4,4),8);
  EXPECT_EQ(grasshopper(4,10),8);

  EXPECT_EQ(grasshopper(4,1),1);

  EXPECT_EQ(grasshopper(5,2),8);

  EXPECT_EQ(grasshopper(2,2),2);
  EXPECT_EQ(grasshopper(1,2),1);
  EXPECT_EQ(grasshopper(0,2),1);

}

TEST(grassHopper, frogs) {
  EXPECT_EQ(grasshopper_and_frogs(4,3,{0,0,1,0,0}),3);
  EXPECT_EQ(grasshopper_and_frogs(4,3,{0,0,0,0,0}),7);
}

TEST(grassHopper, first_cell_occupied_by_frog) {
  EXPECT_EQ(grasshopper_and_frogs(4,3,{1,0,0,0,0}),0);
  EXPECT_EQ(grasshopper_and_frogs(4,3,{0,0,1,0,0}),3);
  EXPECT_EQ(grasshopper_and_frogs(4,3,{0,0,0,0,0}),7);
}

TEST(grassHopper, money) {
  EXPECT_EQ(grasshopper_and_money(5,2,{0,2,-5,-1,3,0}),4);
  EXPECT_EQ(grasshopper_and_money(5,10,{0,2,2,2,2,0}),8);
  EXPECT_EQ(grasshopper_and_money(5,10,{0,-2,-2,-2,-2,0}),0);
  EXPECT_EQ(grasshopper_and_money(5,1,{0,-2,-2,-2,-2,0}),-8);
  EXPECT_EQ(grasshopper_and_money(5,2,{0,-2,2,-2,2,0}),4);
}

TEST(grassHopper, money_restore_sequence) {
  vector<size_t> res = {0,2,4,5};
  EXPECT_EQ(grasshopper_and_money_restoring_sequence_of_jumps(5,10,{0,-1,1,-2,2,0}), res);
  res = {0,1,2,3,4,5};
  EXPECT_EQ(grasshopper_and_money_restoring_sequence_of_jumps(5,10,{0,1,1,1,1,0}), res);
  res = {0,1,2,3,4,5};
  EXPECT_EQ(grasshopper_and_money_restoring_sequence_of_jumps(5,1,{0,-1,1,-1,1,0}), res);
}