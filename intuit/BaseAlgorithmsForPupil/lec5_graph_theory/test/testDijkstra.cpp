#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/Dijkstra.hpp>
using namespace lec5::practice;
#else
#include <include/Dijkstra.hpp>
using namespace lec5;
#endif

#include <bits/stdc++.h>
using namespace std;

/*    1    2    3
 *  a--->b--->c-->d
 */
TEST(Dijkstra, simple) {
  WeightedGraph<char> g;
  g.add('a','b',1);
  g.add('b','c',2);
  g.add('c','d',3);
  ShortestPathsDijkstra sp(g);
  sp.Dijkstra('a');
  EXPECT_EQ(sp.getShortestPathLen('d'), 6);
}

/*    1     2
 *  a---b c--d
 */
TEST(Dijkstra, twoComponents) {
  WeightedGraph<char> g;
  g.add('a','b',1);
  g.add('b','a',1);
  g.add('c','d',2);
  g.add('d','c',2);
  ShortestPathsDijkstra sp(g);
  sp.Dijkstra('a');
  EXPECT_EQ(sp.getShortestPathLen('d'), -1);
  EXPECT_EQ(sp.getShortestPathLen('c'), -1);
  EXPECT_EQ(sp.getShortestPathLen('b'), 1);

  sp.Dijkstra('c');
  EXPECT_EQ(sp.getShortestPathLen('d'), 2);
  EXPECT_EQ(sp.getShortestPathLen('c'), 0);
  EXPECT_EQ(sp.getShortestPathLen('b'), -1);
}


/*    1   2  3
 *  a---b---c--d
 *   \---------/
 *       3
 */
TEST(Dijkstra, graphWithACycle) {
  WeightedGraph<char> g;
  g.add('a','b',1);
  g.add('b','a',1);
  g.add('b','c',2);
  g.add('c','b',2);
  g.add('c','d',3);
  g.add('d','c',3);
  g.add('d','a',3);
  g.add('a','d',3);
  ShortestPathsDijkstra sp(g);
  sp.Dijkstra('a');
  EXPECT_EQ(sp.getShortestPathLen('d'), 3);
  EXPECT_EQ(sp.getShortestPathLen('c'), 3);
  EXPECT_EQ(sp.getShortestPathLen('b'), 1);
  vector<char> expected = {'a','b','c'};
  EXPECT_EQ(sp.getShortestPath('c'),expected);
  expected = {'a','d'};
  EXPECT_EQ(sp.getShortestPath('d'),expected);
}


/*    1    2    3
 *  a--->b--->c-->d
 *   ^\---------/
 *        4
 */
TEST(Dijkstra, directedGraphWithACycle) {
  WeightedGraph<char> g;
  g.add('a','b',1);
  g.add('b','c',2);
  g.add('c','d',3);
  g.add('d','a',4);
  ShortestPathsDijkstra sp(g);
  sp.Dijkstra('a');
  EXPECT_EQ(sp.getShortestPathLen('d'), 6);
  vector<char> expected = {'a','b', 'c', 'd'};
  EXPECT_EQ(sp.getShortestPath('d'),expected);
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
TEST(Dijkstra, diamond) {
  WeightedGraph<char> g;
  g.add('b','d',1);
  g.add('d','b',1);
  g.add('b','e',4);
  g.add('e','b',4);
  g.add('a','d',3);
  g.add('d','a',3);
  g.add('a','e',1);
  g.add('e','a',1);
  ShortestPathsDijkstra sp(g);
  sp.Dijkstra('a');
  EXPECT_EQ(sp.getShortestPathLen('b'), 4);
  vector<char> expected = {'a','d', 'b'};
  EXPECT_EQ(sp.getShortestPath('b'),expected);
}