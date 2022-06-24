#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/MST_Kruskal.hpp>
using namespace lec6::practice;
#else
#include <include/MST_Kruskal.hpp>
using namespace lec6;
#endif

#include <bits/stdc++.h>
using namespace std;

/*    1    2    3
 *  a---b---c---d
 */
TEST(MST_Kruskal, simple) {
  WeightedGraph<char> g;
  g.add('a','b',1);
  g.add('b','a',1);

  g.add('b','c',2);
  g.add('c','b',2);

  g.add('c','d',3);
  g.add('d','c',3);
  MST_Kruskal mst(g);
  vector<pair<char,char>> expected = {{'a','b'}, {'b','c'}, {'c','d'}};
  EXPECT_EQ(mst.getMST(),expected);
}

/*    1   2  3
 *  a---b---c--d
 *   \---------/
 *       2
 */
TEST(MST_Kruskal, cycle) {
  WeightedGraph<char> g;
  g.add('a','b',1);
  g.add('b','a',1);
  g.add('b','c',2);
  g.add('c','b',2);
  g.add('c','d',3);
  g.add('d','c',3);
  g.add('d','a',2);
  g.add('a','d',2);
  MST_Kruskal mst(g);
  vector<pair<char,char>> expected = {{'a','b'}, {'a','d'}, {'b','c'}};
  EXPECT_EQ(mst.getMST(),expected);
}


/*
 *       b
 *    1 /  \ 4
 *
 *     d    e
 *
 *     3\  / 1
 *       a
 */
TEST(MST_Kruskal, diamond) {
  WeightedGraph<char> g;
  g.add('b','d',1);
  g.add('d','b',1);
  g.add('b','e',4);
  g.add('e','b',4);
  g.add('a','d',3);
  g.add('d','a',3);
  g.add('a','e',1);
  g.add('e','a',1);
  MST_Kruskal mst(g);
  vector<pair<char,char>> expected = {{'a','e'}, {'b','d'}, {'a','d'}};
  EXPECT_EQ(mst.getMST(),expected);
}