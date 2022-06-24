#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/shortest_paths_BFS.hpp>
using namespace lec5::practice;
#else
#include <include/shortest_paths_BFS.hpp>
using namespace lec5;
#endif

#include <bits/stdc++.h>
using namespace std;

/*
 *  a--->b--->c-->d
 */
TEST(shortestPathsBFS, simple_DAG) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  ShortestPathsBFS sp(g);

  sp.BFS('a');
  EXPECT_EQ(sp.get_dist('a','b'),1);
  EXPECT_EQ(sp.get_dist('a','c'),2);
  EXPECT_EQ(sp.get_dist('a','d'),3);

  vector<char> expected = {'a','b'};
  EXPECT_EQ(sp.get_shortest_path('a','b'),expected);
  expected = {'a','b','c'};
  EXPECT_EQ(sp.get_shortest_path('a','c'),expected);
  expected = {'a','b','c','d'};
  EXPECT_EQ(sp.get_shortest_path('a','d'),expected);
}

/*
 *  a---b c--d
 */
TEST(shortestPathsBFS, twoComponents) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','a');
  g.add('c','d');
  g.add('d','c');
  ShortestPathsBFS sp(g);

  sp.BFS('a');
  EXPECT_EQ(sp.get_dist('a','b'),1);
  EXPECT_EQ(sp.get_dist('a','c'),-1);
  EXPECT_EQ(sp.get_dist('a','d'),-1);

  sp.BFS('c');
  EXPECT_EQ(sp.get_dist('c','b'),-1);
  EXPECT_EQ(sp.get_dist('c','c'),0);
  EXPECT_EQ(sp.get_dist('c','d'),1);

}

/*
 *  a---b---c--d
 *   \---------/
 */
TEST(shortestPathsBFS, graphWithACycle) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','a');
  g.add('b','c');
  g.add('c','b');
  g.add('c','d');
  g.add('d','c');
  g.add('d','a');
  g.add('a','d');
  ShortestPathsBFS sp(g);
  sp.BFS('a');
  EXPECT_EQ(sp.get_dist('a', 'd'),1);
}

/*
 *  a--->b--->c-->d
 *   ^\---------/
 */
TEST(shortestPathsBFS, directedGraphWithACycle) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  g.add('d','a');
  ShortestPathsBFS sp(g);
  sp.BFS('a');
  EXPECT_EQ(sp.get_dist('a', 'd'),3);
}

/*
 *  a--->b--->c-->d
 *      ^\-------/
 */
TEST(shortestPathsBFS, graphWithACycleWithAPredPeriod) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  g.add('d','b');
  ShortestPathsBFS sp(g);
  sp.BFS('a');
  EXPECT_EQ(sp.get_dist('a', 'd'),3);
}

/*
 *  a--->b
 *   ^--/
 */
TEST(shortestPathsBFS, cycleWithTwoEdges) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','a');
  ShortestPathsBFS sp(g);
  sp.BFS('a');
  EXPECT_EQ(sp.get_dist('a', 'b'),1);
}

/*
 *          a
 *       /     \
 *
 *      b       c
 *     /  \    /  \
 *
 *    d    e  f    g
 */
TEST(shortestPathsBFS, tree) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','a');
  g.add('a','c');
  g.add('c','a');
  g.add('b','d');
  g.add('d','b');
  g.add('b','e');
  g.add('e','b');
  g.add('c','f');
  g.add('f','c');
  g.add('c','g');
  g.add('g','c');
  ShortestPathsBFS sp(g);
  sp.BFS('a');
  EXPECT_EQ(sp.get_dist('a', 'g'),2);
  EXPECT_EQ(sp.get_dist('a', 'f'),2);
  EXPECT_EQ(sp.get_dist('a', 'e'),2);
  EXPECT_EQ(sp.get_dist('a', 'd'),2);

  sp.BFS('b');
  EXPECT_EQ(sp.get_dist('b', 'g'),3);
  EXPECT_EQ(sp.get_dist('b', 'f'),3);
  EXPECT_EQ(sp.get_dist('b', 'e'),1);
  EXPECT_EQ(sp.get_dist('b', 'd'),1);
}

/*
 *      b
 *     /  \
 *
 *    d    e
 *
 *     \  /
 *      a
 */
TEST(shortestPathsBFS, diamond) {
  Graph<char> g;
  g.add('b','d');
  g.add('d','b');
  g.add('b','e');
  g.add('e','b');
  g.add('a','d');
  g.add('d','a');
  g.add('a','e');
  g.add('e','a');
  ShortestPathsBFS sp(g);
  sp.BFS('a');
  EXPECT_EQ(sp.get_dist('a', 'b'),2);
}