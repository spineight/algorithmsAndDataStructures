#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/connected_components.hpp>
using namespace lec4::practice;
#else
#include <include/connected_components.hpp>
using namespace lec4;
#endif

#include <bits/stdc++.h>
using namespace std;

// 0---1---2
TEST(connectedComponents, oneComponent) {
  Graph<size_t> g;
  stringstream ss_in{"3 4  0 1  1 0    1 2   2 1"};
  ss_in >> g;
  ConnectedComponents cc(g);
  map<size_t, set<size_t>> expected = { {1,{0,1,2}} };
  EXPECT_EQ(cc.get_components(), expected);
}

// 0---1---2
//  \-----/
TEST(connectedComponents, oneComponentWithCycle) {
  Graph<size_t> g;
  stringstream ss_in{"3 6   0 1  1 0     1 2  2 1     2 0   0 2"};
  ss_in >> g;
  ConnectedComponents cc(g);
  map<size_t, set<size_t>> expected = { {1,{0,1,2}} };
  EXPECT_EQ(cc.get_components(), expected);
}

// 0---1   2---3   4---5
TEST(connectedComponents, multipleComponents) {
  Graph<size_t> g;
  stringstream ss_in{"6 6   0 1  1 0    2 3  3 2      4 5   5 4"};
  ss_in >> g;
  ConnectedComponents cc(g);
  map<size_t, set<size_t>> expected = { {1, { 4, 5 }}, {2, { 0, 1 }}, {3, { 2, 3 }} };
  EXPECT_EQ(cc.get_components(), expected);
}

//!          6    1
//!           *  *
//!         5** 0 **2
//!           *  *
//!          4     3
TEST(connectedComponents, one_vertex_has_multiple_edges) {
  Graph<size_t> g;
  stringstream ss_in{"7 12   0 1  1 0      0 2  2 0      0 3  3 0     0 4  4 0     0 5   5 0      0 6   6 0"};
  ss_in >> g;
  ConnectedComponents cc(g);
  map<size_t, set<size_t>> expected = { {1,{0,1,2,3,4,5,6}} };
  EXPECT_EQ(cc.get_components(), expected);
}