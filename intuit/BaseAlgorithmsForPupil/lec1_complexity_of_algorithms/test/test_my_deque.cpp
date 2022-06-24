#include <gtest/gtest.h>

#include <bits/stdc++.h>

#ifdef PRACTICE
#include <practice/my_deque.hpp>
using namespace lec1::practice;
#else
#include <include/my_deque.hpp>
using namespace lec1;
#endif

using namespace std;

TEST(test_dequeue, oneElement) {
  RingDeque<1> rd;
  EXPECT_TRUE(rd.size()==0);
  for(int i = 1; i <= 100; ++i) {
    rd.push_back(i);
    EXPECT_EQ(rd.size(),1);
    EXPECT_EQ(rd.front(), i);
    rd.pop_front();
    EXPECT_EQ(rd.size(),0);
  }

  for(int i = 1; i <= 100; ++i) {
    rd.push_front(i);
    EXPECT_EQ(rd.size(),1);
    EXPECT_EQ(rd.front(), i);
    rd.pop_front();
    EXPECT_EQ(rd.size(),0);
  }

  for(int i = 1; i <= 100; ++i) {
    rd.push_back(i);
    EXPECT_EQ(rd.size(),1);
    EXPECT_EQ(rd.front(), i);
    rd.pop_back();
    EXPECT_EQ(rd.size(),0);
  }

  for(int i = 1; i <= 100; ++i) {
    rd.push_front(i);
    EXPECT_EQ(rd.size(),1);
    EXPECT_EQ(rd.front(), i);
    rd.pop_back();
    EXPECT_EQ(rd.size(),0);
  }
}

TEST(test_ring_queue, wrapAround0) {
  RingDeque<4> rd;
  constexpr int N_OF_WRITES = 100;
  for(int i = 0; i < N_OF_WRITES; ++i) {
    rd.push_back(i);
    rd.push_back(i+1);
    rd.push_back(i+2);
    EXPECT_EQ(rd.size(),3);
    EXPECT_EQ(rd.front(),i);
    rd.pop_front();
    rd.pop_front();
    rd.pop_front();
    EXPECT_EQ(rd.size(),0);
  }
}
TEST(test_ring_queue, wrapAround1) {
  RingDeque<4> rd;
  constexpr int N_OF_WRITES = 100;
  for(int i = 0; i < N_OF_WRITES; ++i) {
    rd.push_back(i);
    rd.push_back(i+1);
    rd.push_back(i+2);
    EXPECT_EQ(rd.size(),3);
    EXPECT_EQ(rd.front(),i);
    rd.pop_back();
    rd.pop_back();
    rd.pop_back();
    EXPECT_EQ(rd.size(),0);
  }
}

TEST(test_ring_queue, wrapAround2) {
  RingDeque<4> rd;
  constexpr int N_OF_WRITES = 100;
  for(int i = 0; i < N_OF_WRITES; ++i) {
    rd.push_front(i);
    rd.push_front(i+1);
    rd.push_front(i+2);
    EXPECT_EQ(rd.size(),3);
    EXPECT_EQ(rd.front(),i+2);
    rd.pop_back();
    rd.pop_back();
    rd.pop_back();
    EXPECT_EQ(rd.size(),0);
  }
}

TEST(test_ring_queue, wrapAround3) {
  RingDeque<4> rd;
  constexpr int N_OF_WRITES = 100;
  for(int i = 0; i < N_OF_WRITES; ++i) {
    rd.push_front(i);
    rd.push_front(i+1);
    rd.push_front(i+2);
    EXPECT_EQ(rd.size(),3);
    EXPECT_EQ(rd.front(),i+2);
    rd.pop_front();
    rd.pop_front();
    rd.pop_front();
    EXPECT_EQ(rd.size(),0);
  }
}