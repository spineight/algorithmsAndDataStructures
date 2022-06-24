#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/adjacency_lists.hpp>
using namespace lec4::practice;
#else
#include <include/adjacency_lists.hpp>
using namespace lec4;
#endif

#include <bits/stdc++.h>
using namespace std;

// 1---2---3
//
// 1---2
// 2---1
// 2---3
// 3---2
TEST(adjacency_lists, connected_graph) {
  Graph<3> g;
  stringstream ss_in{"3 2 1 2 2 3"};
  ss_in >> g;

  stringstream  ss_out;
  ss_out << g;
  EXPECT_EQ(ss_out.str(), "1:2, 2:3,1, 3:2, ");
}


// 1---2---3
//  \-----/
//
// 1---2---3
// 2---1
// 2---3
// 3---2---1
TEST(adjacency_lists, fully_connected_graph) {
  Graph<3> g;
  stringstream ss_in{"3 3 1 2 2 3 3 1"};
  ss_in >> g;

  stringstream  ss_out;
  ss_out << g;
  EXPECT_EQ(ss_out.str(), "1:3,2, 2:3,1, 3:1,2, ");
}

// 1---2   3---4   5---6
//
//

TEST(adjacency_lists, multiple_components_graph) {
  Graph<6> g;
  stringstream ss_in{"6 3 1 2 3 4 5 6"};
  ss_in >> g;

  stringstream  ss_out;
  ss_out << g;
  EXPECT_EQ(ss_out.str(), "1:2, 2:1, 3:4, 4:3, 5:6, 6:5, ");
}


// 1---2   5---6
// |   |   |   |
// 3---4   7---8
TEST(adjacency_lists, multiple_components_graph1) {
  Graph<8> g;
  stringstream ss_in{"8 8 1 2 2 4 4 3 3 1 5 6 6 8 8 7 7 5"};
  ss_in >> g;

  stringstream  ss_out;
  ss_out << g;
  EXPECT_EQ(ss_out.str(), "1:3,2, 2:4,1, 3:1,4, 4:3,2, 5:7,6, 6:8,5, 7:5,8, 8:7,6, ");
}

//!          7    2
//!           *  *
//!         6** 1 **3
//!           *  *
//!          5     4
TEST(adjacency_lists, one_vertex_has_multiple_edges) {
  Graph<7> g;
  stringstream ss_in{"7 6 1 2 1 3 1 4 1 5 1 6 1 7"};
  ss_in >> g;

  stringstream  ss_out;
  ss_out << g;
//  cout << ss_out.str() << '\n';
  EXPECT_EQ(ss_out.str(), "1:7,6,5,4,3,2, 2:1, 3:1, 4:1, 5:1, 6:1, 7:1, ");
}