#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/cycle_detection.hpp>
using namespace lec5::practice;
#else
#include <include/cycle_detection.hpp>
using namespace lec5;
#endif

#include <bits/stdc++.h>
using namespace std;

/*
 *  a--->b--->c-->d
 */
TEST(cycleDetection, simple_DAG) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  CycleDetection cd(g);
  EXPECT_FALSE(cd.isCycle());
  vector<char> expected = {};
  EXPECT_EQ(cd.get_cycle(), expected);
}

/*
 *  a--->b--->c-->d
 *   ^\----------/
 */
TEST(cycleDetection, graphWithACycle) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  g.add('d','a');
  CycleDetection cd(g);
  EXPECT_TRUE(cd.isCycle());
  vector<char> expected = {'d','a','b','c'};
  EXPECT_EQ(cd.get_cycle(), expected);
}

/*
 *  a--->b--->c-->d
 *      ^\-------/
 */
TEST(cycleDetection, graphWithACycleWithAPredPeriod) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','c');
  g.add('c','d');
  g.add('d','b');
  CycleDetection cd(g);
  EXPECT_TRUE(cd.isCycle());
  vector<char> expected = {'d','b','c'};
  EXPECT_EQ(cd.get_cycle(), expected);
}

/*
 *  a--->b
 *   ^--/
 */
TEST(cycleDetection, cycleWithTwoEdges) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','a');
  CycleDetection cd(g);
  EXPECT_TRUE(cd.isCycle());
  vector<char> expected = {'b','a'};
  EXPECT_EQ(cd.get_cycle(), expected);
}

/*
 *  a---b
 *   --/
 */
TEST(cycleDetection, undirectedGraphNoCycle) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','a');
  constexpr size_t IS_DIRECTED_GRAPH = 0;
  CycleDetection<char, IS_DIRECTED_GRAPH> cd(g);
  EXPECT_FALSE(cd.isCycle());
  vector<char> expected = {};
  EXPECT_EQ(cd.get_cycle(), expected);
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
TEST(cycleDetection, tree) {
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
  constexpr size_t IS_DIRECTED_GRAPH = 0;
  CycleDetection<char, IS_DIRECTED_GRAPH> cd(g);
  EXPECT_FALSE(cd.isCycle());
  vector<char> expected = {};
  EXPECT_EQ(cd.get_cycle(), expected);
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
TEST(cycleDetection, diamond) {
  Graph<char> g;
  g.add('b','d');
  g.add('d','b');
  g.add('b','e');
  g.add('e','b');
  g.add('a','d');
  g.add('d','a');
  g.add('a','e');
  g.add('e','a');
  constexpr size_t IS_DIRECTED_GRAPH = 0;
  CycleDetection<char,IS_DIRECTED_GRAPH> cd(g);
  EXPECT_TRUE(cd.isCycle());
  vector<char> expected = {'a','d','b','e'};
  EXPECT_EQ(cd.get_cycle(), expected);
}