#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/topological_sort.hpp>
using namespace lec5::practice;
#else
#include <include/topological_sort.hpp>
using namespace lec5;
#endif

#include <bits/stdc++.h>
using namespace std;

/*
 *  a--->b--->c-->d
 */
TEST(topSort, simple_DAG) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  TopSort ts(g);
  EXPECT_TRUE(ts.topSort());
  vector<char> expected = {'a', 'b', 'c', 'd'};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *  a--->b    c-->d
 */
TEST(topSort, multipleComponents_DAG) {
  Graph<char> g;
  g.add('a','b');
  g.add('c','d');
  TopSort ts(g);
  EXPECT_TRUE(ts.topSort());
  vector<char> expected = {'a', 'b', 'c', 'd'};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *  a    c
 */
TEST(DISABLED_topSort, severalIsolatedVertixes_DAG) {
  Graph<char> g;
  g.add('a','a');
  g.add('c','c');
  TopSort ts(g);
  EXPECT_TRUE(ts.topSort());
  vector<char> expected = {'a', 'c'};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *  a--->b--->c-->d
 *   ^\----------/
 */
TEST(topSort, graphWithACycle) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  g.add('d','a');
  TopSort ts(g);
  EXPECT_FALSE(ts.topSort());
  vector<char> expected = {};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *  a--->b--->c-->d
 *      ^\-------/
 */
TEST(topSort, graphWithACycleWithAPredPeriod) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  g.add('d','b');
  TopSort ts(g);
  EXPECT_FALSE(ts.topSort());
  vector<char> expected = {};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *          a
 *       /     \
 *      V       v
 *      b       c
 *     /  \    /  \
 *    v    v  v    v
 *    d    e  f    g
 */
TEST(topSort, tree) {
  Graph<char> g;
  g.add('a','b');
  g.add('a','c');
  g.add('b','d');
  g.add('b','e');
  g.add('c','f');
  g.add('c','g');
  TopSort ts(g);
  EXPECT_TRUE(ts.topSort());
  vector<char> expected = {'a', 'b', 'e', 'd', 'c', 'g','f'};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *      b       c
 *     /  \    /  \
 *    v    v  v    v
 *    d    e  f    g
 */
TEST(topSort, forest) {
  Graph<char> g;
  g.add('b','d');
  g.add('b','e');
  g.add('c','f');
  g.add('c','g');
  TopSort ts(g);
  EXPECT_TRUE(ts.topSort());
  vector<char> expected = {'b', 'e', 'd', 'c', 'g','f'};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *      b
 *     /  \
 *    v    v
 *    d    e
 *    ^    ^
 *     \  /
 *      a
 */
TEST(topSort, diamond) {
  Graph<char> g;
  g.add('b','d');
  g.add('b','e');
  g.add('a','d');
  g.add('a','e');
  TopSort ts(g);
  EXPECT_TRUE(ts.topSort());
  vector<char> expected = {'b', 'a', 'e', 'd'};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *  a--->b
 */
TEST(topSort, oneEdge) {
  Graph<char> g;
  g.add('a','b');
  TopSort ts(g);
  EXPECT_TRUE(ts.topSort());
  vector<char> expected = {'a', 'b'};
  EXPECT_EQ(ts.getTopSort(), expected);
}

/*
 *   f< \   >g
 *       \ /
 *   e<--- a--->b
 *       / \
 *      V   V
 *      d   c
 *
 */

TEST(topSort, start) {
  Graph<char> g;
  g.add('a','b');
  g.add('a','c');
  g.add('a','d');
  g.add('a','e');
  g.add('a','f');
  g.add('a','g');
  TopSort ts(g);
  EXPECT_TRUE(ts.topSort());
  vector<char> expected = {'a', 'g', 'f', 'e', 'd', 'c', 'b'};
  EXPECT_EQ(ts.getTopSort(), expected);
}