#include <gtest/gtest.h>

#include <bits/stdc++.h>

#ifdef PRACTICE
#include <practice/my_static_list.hpp>
using namespace lec1::practice;
#else
#include <include/StaticSingleLinkedList.hpp>
using namespace lec1;
#endif

using namespace std;

// Добавление одного элемента в начало пустого списка и добавление в конец пустого списка - один и тот же список должен получаться
TEST(StaticSingleLinkedList, sameListIfAddedFrontBack) {
  StaticSingleLinkedList<10> list0, list1;

  list0.add_front(100);
  list1.add_back(100);

  while(!list0.empty()) {
    EXPECT_EQ(list0.front(), list1.front());
    list0.pop_front();
    list1.pop_front();
  }
  EXPECT_TRUE(list1.empty());
}

TEST(StaticSingleLinkedList, addBackTillFull) {
  constexpr int MAX_N = 10;
  StaticSingleLinkedList<MAX_N> list;

  vector<int> a(MAX_N);
  iota(begin(a), end(a),0);
  for(auto v : a)
    list.add_back(v);

  int idx{0};
  while(!list.empty()) {
    EXPECT_EQ(list.front(), idx++);
    list.pop_front();
  }
}

TEST(StaticSingleLinkedList, addFrontTillFull) {
  constexpr int MAX_N = 10;
  StaticSingleLinkedList<MAX_N> list;

  vector<int> a(MAX_N);
  iota(begin(a), end(a),0);
  for(auto v : a)
    list.add_front(v);


  int idx{0};
  while(!list.empty()) {
    EXPECT_EQ(list.front(), MAX_N-1-idx);
    ++idx;
    list.pop_front();
  }
}

TEST(StaticSingleLinkedList, empty) {
  constexpr int MAX_N = 10;
  StaticSingleLinkedList<MAX_N> list;
  EXPECT_TRUE(list.empty());

  list.add_front(1);
  EXPECT_TRUE(!list.empty());
  list.pop_front();
  EXPECT_TRUE(list.empty());

  list.add_back(1);
  EXPECT_TRUE(!list.empty());
  list.pop_front();
  EXPECT_TRUE(list.empty());
}

TEST(StaticSingleLinkedList, removeAfter) {
  int a[] = {1,2,3,4,5,6,7,8,9};
  constexpr int MAX_N = size(a)*2;
  StaticSingleLinkedList<MAX_N> list;

  for(auto v : a)
    list.add_front(v);

  while(!list.empty()) {
    list.remove_after(list.head);
  }
  for(auto v : a)
    list.add_back(v*2);

  int idx{0};
  while(!list.empty()) {
    EXPECT_EQ(list.front(), a[idx] * 2);
    ++idx;
    list.pop_front();
  }
}


TEST(StaticSingleLinkedList, addFrontAddBackInterleaved) {
  int a[] = {1,2,3,4,5,6,7,8,9};
  StaticSingleLinkedList<size(a)> list;

  for(size_t i = 0; i < size(a); ++i) {
    if(i & 1)
      list.add_back(a[i]);
    else
        list.add_front(a[i]);
  }


  int expected[] = {9,7,5,3,1,2,4,6,8};
  int idx{0};
  while(!list.empty()) {
    EXPECT_EQ(list.front(), expected[idx]);
    ++idx;
    list.pop_front();
  }
}