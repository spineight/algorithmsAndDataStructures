#include <gtest/gtest.h>

#include <bits/stdc++.h>

#ifdef PRACTICE
#include <practice/StaticMultiLists.hpp>
using namespace lec1::practice;
#else
#include <include/StaticMultiLists.hpp>
using namespace lec1;
#endif

using namespace std;

TEST(StaticMultilists, smallestPossible) {
  MultiLists<1, 100> list;
  for(int i = 0; i < 100; ++i) {
    list.add_to_tail(0,i);
    EXPECT_EQ(list.pop_front(0),i);
    EXPECT_TRUE(list.empty(0));
  }
}

TEST(StaticMultilists, twoStacks) {
  constexpr int N_OF_ELEMENTS = 4;
  MultiLists<2, N_OF_ELEMENTS> list;
  for(int i = 0; i < N_OF_ELEMENTS / 2; ++i) {
    list.add_to_tail(0,i);
    list.add_to_tail(1,i);
    EXPECT_EQ(list.pop_front(0),i);
    EXPECT_EQ(list.pop_front(1),i);
    EXPECT_TRUE(list.empty(0));
    EXPECT_TRUE(list.empty(1));
  }
}

TEST(StaticMultilists, multipleStacksAddRemoveOneElementToEach) {
  constexpr int N_OF_ELEMENTS = 40;
  constexpr int N_OF_STACKS = 10;
  MultiLists<N_OF_STACKS, N_OF_ELEMENTS> list;
  for(int i = 0; i < N_OF_ELEMENTS / N_OF_STACKS; ++i) {
    for(int stackIdx = 0; stackIdx < N_OF_STACKS; ++stackIdx) {
      list.add_to_tail(stackIdx,i);
      EXPECT_EQ(list.pop_front(stackIdx),i);
      EXPECT_TRUE(list.empty(stackIdx));
    }
  }
}

TEST(StaticMultilists, multipleStacksAddTillFullThenEmpty) {
  constexpr int N_OF_ELEMENTS = 20;
  constexpr int N_OF_STACKS = 4;
  MultiLists<N_OF_STACKS, N_OF_ELEMENTS> list;
  for(int i = 0; i < N_OF_ELEMENTS / N_OF_STACKS; ++i) {
    for(int stackIdx = 0; stackIdx < N_OF_STACKS; ++stackIdx) {
      list.add_to_tail(stackIdx,i);
    }
  }

  for(int stackIdx = 0; stackIdx < N_OF_STACKS; ++stackIdx) {
    int i = 0;
    while(!list.empty(stackIdx)) {
      EXPECT_EQ(list.pop_front(stackIdx) , i);
      ++i;
    }
  }
}