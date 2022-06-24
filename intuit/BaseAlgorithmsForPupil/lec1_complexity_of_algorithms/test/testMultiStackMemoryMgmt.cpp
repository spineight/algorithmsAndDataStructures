#include <gtest/gtest.h>

#include <bits/stdc++.h>

#ifdef PRACTICE
#include <practice/MultiStackMemoryMgmt.hpp>
using namespace lec1::practice;
#else
#include <include/MultiStackMemoryMgmt.hpp>
using namespace lec1;
#endif

using namespace std;

TEST(MultiStackMemoryMgmt, smallestPossible) {
  MultiStackMemoryMgmt<2,2> s;
  for(int i = 0; i < 100; ++i) {
    s.push(1,i);
    EXPECT_EQ(s.pop(1),i);
    EXPECT_TRUE(s.empty(1));
  }
}

TEST(MultiStackMemoryMgmt, twoStacks) {
  constexpr int N_OF_ELEMENTS = 4;
  MultiStackMemoryMgmt<1+2, N_OF_ELEMENTS> list; // 1 - стек свободных индексов, + 2 - стеки с данными
  for(int i = 0; i < N_OF_ELEMENTS / 2; ++i) {
    list.push(1,i);
    list.push(2,i);
    EXPECT_EQ(list.pop(1),i);
    EXPECT_EQ(list.pop(2),i);
    EXPECT_TRUE(list.empty(1));
    EXPECT_TRUE(list.empty(2));
  }
}

TEST(MultiStackMemoryMgmt, multipleStacksAddRemoveOneElementToEach) {
  constexpr int N_OF_ELEMENTS = 40;
  constexpr int N_OF_STACKS = 10;
  MultiStackMemoryMgmt<N_OF_STACKS+1, N_OF_ELEMENTS> list;
  for(int i = 0; i < N_OF_ELEMENTS / N_OF_STACKS; ++i) {
    for(int stackIdx = 1; stackIdx <= N_OF_STACKS; ++stackIdx) {
      list.push(stackIdx,i);
      EXPECT_EQ(list.pop(stackIdx),i);
      EXPECT_TRUE(list.empty(stackIdx));
    }
  }
}

TEST(MultiStackMemoryMgmt, multipleStacksAddTillFullThenEmpty) {
  constexpr int N_OF_ELEMENTS = 20;
  constexpr int N_OF_STACKS = 4;
  MultiStackMemoryMgmt<N_OF_STACKS+1, N_OF_ELEMENTS> list;
  for(int i = 0; i < N_OF_ELEMENTS / N_OF_STACKS; ++i) {
    for(int stackIdx = 1; stackIdx <= N_OF_STACKS; ++stackIdx) {
      list.push(stackIdx,i);
    }
  }

  for(int stackIdx = 1; stackIdx <= N_OF_STACKS; ++stackIdx) {
    int i = N_OF_ELEMENTS / N_OF_STACKS-1;
    while(!list.empty(stackIdx)) {
      EXPECT_EQ(list.pop(stackIdx) , i);
      --i;
    }
  }
}