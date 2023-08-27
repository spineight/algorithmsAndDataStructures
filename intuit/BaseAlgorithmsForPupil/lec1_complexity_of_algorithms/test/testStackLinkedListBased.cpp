#include <gtest/gtest.h>

#include <bits/stdc++.h>

#ifdef PRACTICE
#include <practice/my_static_list.hpp>
using namespace lec1::practice;
#else
#include <include/StackLinkedListBased.hpp>
using namespace lec1;
#endif

using namespace std;

TEST(StackLinkedListBased, oneElement) {
  // Так как у нас индексы не высвобождаются,
  // то количество элементов должно быть = количеству операций добавления
  StackLinkedListBased<2> s;
  EXPECT_TRUE(s.empty());
  s.push(1);
  EXPECT_EQ(s.back(),1);
  s.pop();
  s.push(2);
  EXPECT_EQ(s.back(),2);
  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(StackLinkedListBased, multiple_pushes_followed_by_pop) {
  int a[] = {1,2,3,4,5,6,7,8,9,10};
  StackLinkedListBased<size(a)> s;
  for(auto v : a) {
    s.push(v);
  }
  auto it = rbegin(a);
  while(!s.empty()) {
    EXPECT_EQ(s.back(), *it++);
    s.pop();
  }
}