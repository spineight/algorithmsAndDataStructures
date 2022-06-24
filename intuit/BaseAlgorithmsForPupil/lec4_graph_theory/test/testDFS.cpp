#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/dfs.hpp>
using namespace lec4::practice;
#else
#include <include/dfs.hpp>
using namespace lec4;
#endif

#include <bits/stdc++.h>
using namespace std;

// 0---1---2
TEST(testDFS, oneComponent) {
  Graph<size_t> g;
  stringstream ss_in{"3 4   0 1     1 0     1 2      2 1"};
  ss_in >> g;
  vector<size_t> expected = {0,1,2};
  DFS dfs(g);
  EXPECT_EQ(dfs.get_dfs(0),expected);
}

// 0-->1
TEST(testDFS, oneComponentDirectedGraph) {
  Graph<size_t> g;
  stringstream ss_in{"2 1   0 1"};
  ss_in >> g;
  vector<size_t> expected = {0,1};
  DFS dfs(g);
  EXPECT_EQ(dfs.get_dfs(0),expected);
}

// 0---1---2
//  \-----/
TEST(testDFS, oneComponentWithCycle) {
  Graph<size_t> g;
  stringstream ss_in{"3 6   0 1   1 0      1 2    2 1      2 0   0 2"};
  ss_in >> g;
  DFS dfs(g);
  vector<size_t> expected = {0,1,2};
  EXPECT_EQ(dfs.get_dfs(0),expected);
}

// 0---1   2---3   4---5
TEST(testDFS, multipleComponents) {
  Graph<size_t> g;
  stringstream ss_in{"6 6     0 1   1 0     2 3  3 2     4 5   5 4"};
  ss_in >> g;
  DFS dfs(g);
  vector<size_t> expected = {0,1};
  EXPECT_EQ(dfs.get_dfs(0),expected);
  expected = {2,3};
  EXPECT_EQ(dfs.get_dfs(2),expected);
  expected = {4,5};
  EXPECT_EQ(dfs.get_dfs(4),expected);
}

//!          6    1
//!           *  *
//!         5** 0 **2
//!           *  *
//!          4     3
TEST(testDFS, one_vertex_has_multiple_edges) {
  Graph<size_t> g;
  stringstream ss_in{"7 12  0 1  1 0    0 2  2 0     0 3  3 0    0 4  4 0     0 5  5 0     0 6    6 0"};
  ss_in >> g;
  DFS dfs(g);
  vector<size_t> expected = {0,1,2,3,4,5,6};
  EXPECT_EQ(dfs.get_dfs(0), expected);
}