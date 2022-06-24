#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/euler_cycle.hpp>
using namespace lec6::practice;
#else
#include <include/euler_cycle.hpp>
using namespace lec6;
#endif

#include <bits/stdc++.h>
using namespace std;

// a---b
// |   |
// c---d
TEST(euler_cycle, basic) {
  Graph<char> g;
  g.add('a','b');
  g.add('b','a');

  g.add('b','d');
  g.add('d','b');

  g.add('d','c');
  g.add('c','d');

  g.add('a','c');
  g.add('c','a');

  EulerCycle ec(g);

  vector<pair<char,char>> expected = { {'c', 'd'}, {'d','b'}, {'b','a'}, {'a','c'} };
  EXPECT_EQ(ec.getCycle(), expected);
}