#include <gtest/gtest.h>

#include <bits/stdc++.h>

#ifdef PRACTICE
#include <practice/my_queue.hpp>
using namespace lec1::practice;
#else
#include <include/my_queue.hpp>
using namespace lec1;
#endif

using namespace std;

TEST(test_ring_queue, oneElement) {
  RingQueue<1> rq;
  for(int i = 1; i <= 9; ++i) {
    EXPECT_TRUE(rq.empty());
    rq.push(i);
    EXPECT_TRUE(rq.size()==1);
    EXPECT_EQ(rq.front(),i);
    EXPECT_TRUE(rq.full());
    rq.pop();
  }
}

TEST(test_ring_queue, pushThenPop) {
  int a[] = {1,2,3,4,5,6,7,8,9};
  RingQueue<size(a)> rq;
  for(auto v : a) {
    rq.push(v);
    EXPECT_EQ(rq.size(), v);
  }
  EXPECT_TRUE(rq.full());
  auto it = begin(a);
  while(!rq.empty()) {
    EXPECT_EQ(rq.front(),*it++);
    rq.pop();
  }
}

TEST(test_ring_queue, wrapAround) {
  RingQueue<4> rq;
  constexpr int N_OF_WRITES = 100;
  for(int i = 0; i < N_OF_WRITES; ++i) {
    rq.push(i);
    rq.push(i+1);
    rq.push(i+3);
    EXPECT_EQ(rq.size(),3);
    EXPECT_EQ(rq.front(),i);
    rq.pop();
    rq.pop();
    rq.pop();
    EXPECT_EQ(rq.size(),0);
    EXPECT_TRUE(rq.empty());
  }
}