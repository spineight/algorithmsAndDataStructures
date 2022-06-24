#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/binary_search.hpp>
using namespace lec2::practice;
#else
#include <include/binary_search.hpp>
#endif

using namespace lec2;

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

TEST(findFirst, empty_array) {
  vector<int> a;
  EXPECT_TRUE(-1 == findFirst(a, 1));
}

TEST(findFirst, single_non_matching_element) {
  vector<int> a = { 0 };
  EXPECT_TRUE(-1 == findFirst(a, 1));
}

TEST(findFirst, single_matching_element) {
  vector<int> a = { 1 };
  EXPECT_TRUE(0 == findFirst(a, 1));
}

TEST(findFirst, handPickedTest) {
  vector<int> a = { 9,5,7,6,8,3,2,1 };
  EXPECT_EQ(0 , findFirst(a, 1));
}

// https://en.cppreference.com/w/cpp/algorithm/lower_bound
// Returns an iterator pointing to the first element in the range [first, last) that is not less than (i.e. greater or equal to) value,
// or last if no such element is found.
//
// The range [first, last) must be partitioned with respect to the expression element < value or comp(element, value),
// i.e., all elements for which the expression is true must precede all elements for which the expression is false.
// A fully-sorted range meets this criterion.
//
//The first version uses operator< to compare the elements, the second version uses the given comparison function comp.
TEST(findFirst, cross_validate_using_STL_algo) {
  vector<int> a = { 3,1,2,5,4,6,7,8,9 };
  const int n = a.size();
  for (int i = 0; i < n; ++i) {
    int x = a[i];
    partition(begin(a), end(a), [x](int val){return val < x;});
    EXPECT_EQ(lower_bound(begin(a), end(a), x) - begin(a),findFirst(a, x));
  }
}

TEST(findFirst, cross_validate_using_STL_algo_random_array) {
  vector<int> a(100);
  int seed = 1272;
  mt19937 urng(seed);
  const int n = a.size();
  uniform_int_distribution<int> dist(0,100);
  generate(begin(a), end(a), bind(dist,urng));
  for (int i = 0; i < n; ++i) {
    const int x = a[i];
    partition(begin(a), end(a), [x](int val){return val < x;});
    auto it = lower_bound(begin(a), end(a), x);
    if(it != end(a))
      EXPECT_EQ( it - begin(a) , findFirst(a, x));
    else
      EXPECT_EQ(-1, findFirst(a, x));
  }
}

TEST(findFirst, cross_validate_using_STL_algo_random_array_random_x) {
  vector<int> a(100);
  int seed = 1272;
  mt19937 urng(seed);
  const int n = a.size();
  uniform_int_distribution<int> dist(0,1000);
  generate(begin(a), end(a), bind(dist, urng));

  for (int i = 0; i < n; ++i) {
    auto x = dist(urng);
    partition(begin(a), end(a), [x](int val){return val < x;});
    auto it = lower_bound(begin(a), end(a), x);
    if (it == end(a))
      EXPECT_EQ(-1 , findFirst(a, x));
    else if (*it == x) {
      EXPECT_EQ(it - begin(a) , findFirst(a, x));
    }
  }
}

// using binary_searchDeathTest = binary_search;

// https://stackoverflow.com/questions/3756422/how-to-catch-an-assert-with-google-test
TEST(findFirstDeathTest, non_partitioned_array) {
  vector<int> a = { 9, 8, 7, 1, 3, 2 };
  EXPECT_DEBUG_DEATH(findFirst(a, 2),
                     "array should be partitioned with respect to x");
}