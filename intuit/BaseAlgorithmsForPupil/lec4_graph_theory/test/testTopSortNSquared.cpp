#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/topSortNsquared.hpp>
using namespace lec4::practice;
#else
#include <include/topSortNsquared.hpp>
using namespace lec4;
#endif

#include <bits/stdc++.h>
using namespace std;

// a-->b-->c
TEST(topSortNSquared, simple_line) {
  Graph<char> g;
  stringstream ss_in{"3 2 a b b c"};
  ss_in >> g;
  TopSortNSquared topSortNSquared(g);
  auto topSort = topSortNSquared.topSort();
  vector<char> expected = {'a', 'b', 'c'};
  EXPECT_EQ(topSort, expected);
}

// a-->b-->c
//   \>d-->e
TEST(topSortNSquared, two_lines) {
  Graph<char> g;
  stringstream ss_in{"5 4 a b b c a d d e"};
  ss_in >> g;
  TopSortNSquared topSortNSquared(g);
  auto topSort = topSortNSquared.topSort();
  vector<char> expected = {'a', 'b', 'c', 'd', 'e'};
  EXPECT_EQ(topSort, expected);
}


//
//
//    a-->b-->c
//    d-->e-->f
//
TEST(topSortNSquared, multiple_components) {
  Graph<char> g;
  stringstream ss_in{"6 4 a b b c d e e f"};
  ss_in >> g;
  TopSortNSquared topSortNSquared(g);
  auto topSort = topSortNSquared.topSort();
  vector<char> expected = {'a', 'd', 'e', 'f', 'b', 'c'};
  EXPECT_EQ(topSort, expected);
}