#include <gtest/gtest.h>

#include <bits/stdc++.h>

#ifdef PRACTICE
#include <practice/StaticSingleLinkedList.hpp>
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

  EXPECT_EQ(list0.head, list1.head);
  EXPECT_EQ(list0.tail, list1.tail);
  EXPECT_EQ(list0.free, list1.free);

  for(size_t i = 0; i < sizeof(list0.val) / sizeof(list0.val[0]); ++i) {
    EXPECT_EQ(list0.val[i], list1.val[i]);
    EXPECT_EQ(list0.next[i], list1.next[i]);
  }
}

TEST(StaticSingleLinkedList, addBackTillFull) {
  constexpr int MAX_N = 10;
  StaticSingleLinkedList<MAX_N> list;

  vector<int> a(MAX_N);
  iota(begin(a), end(a),0);
  for(auto v : a)
    list.add_back(v);

  int i = list.next[list.head];
  int j = 0;
  while(i != 0) {
    EXPECT_EQ(list.val[i], a[j++]);
    i = list.next[i];
  }
}

TEST(StaticSingleLinkedList, addFrontTillFull) {
  constexpr int MAX_N = 10;
  StaticSingleLinkedList<MAX_N> list;

  vector<int> a(MAX_N,-1);
  iota(begin(a), end(a),0);
  for(auto v : a)
    list.add_front(v);

  int i = list.next[list.head];
  int j = MAX_N-1;
  while(i != 0) {
    EXPECT_EQ(list.val[i], a[j--]);
    i = list.next[i];
  }
}

TEST(StaticSingleLinkedList, empty) {
  constexpr int MAX_N = 10;
  StaticSingleLinkedList<MAX_N> list;
  EXPECT_TRUE(list.empty());

  list.add_front(1);
  EXPECT_TRUE(!list.empty());
  list.remove_after(list.head);
  EXPECT_TRUE(list.empty());

  list.add_back(1);
  EXPECT_TRUE(!list.empty());
  list.remove_after(list.head);
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

  int i = list.next[list.head];
  int j = 0;
  while(i != 0) {
    EXPECT_EQ(list.val[i], a[j]*2);
    ++j;
    i = list.next[i];
  }
}

TEST(StaticSingleLinkedList, addAfter) {
  int a[] = {1, 2, 3, 4, 5};
  constexpr int MAX_N = size(a) * 2;
  StaticSingleLinkedList<MAX_N> list;
  list.add_back(1);
  list.add_after(list.next[list.head],4);
  list.add_back(5);
  list.add_after(list.next[list.head],3);
  list.add_after(list.next[list.head],2);
  int i = list.next[list.head];
  int j = 0;
  while(i != 0) {
    EXPECT_EQ(list.val[i], a[j]);
    ++j;
    i = list.next[i];
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


  int i = list.next[list.head];
  int j = 0;
  int expected[] = {9,7,5,3,1,2,4,6,8};
  while(i != 0) {
    EXPECT_EQ(list.val[i], expected[j]);
    i = list.next[i];
    ++j;
  }
}