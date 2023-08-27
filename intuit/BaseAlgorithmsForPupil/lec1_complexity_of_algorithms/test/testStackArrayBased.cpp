#include <gtest/gtest.h>

#include <bits/stdc++.h>

#ifdef PRACTICE
#include <practice/my_stack.hpp>
using namespace lec1::practice;
#else
#include <include/StackArrayBased.hpp>
using namespace lec1;
#endif

using namespace std;

TEST(right_brackets_one_type, oneElement) {
  StackArrayBased<1> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(),0);
  s.push(1);
  EXPECT_EQ(s.size(),1);
  EXPECT_EQ(s.back(),1);
  s.pop();
  s.push(2);
  EXPECT_EQ(s.back(),2);
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(right_brackets_one_type, multiple_pushes_followed_by_pop) {
  int a[] = {1,2,3,4,5,6,7,8,9,10};
  StackArrayBased<size(a)> s;
  for(auto v : a) {
    s.push(v);
    EXPECT_EQ(s.size(),v);
  }
  auto it = rbegin(a);
  while(s.size() > 0) {
    EXPECT_EQ(s.back(), *it++);
    s.pop();
  }
  EXPECT_EQ(s.size(),0);
}