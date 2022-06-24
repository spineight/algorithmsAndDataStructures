#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/find_function_root.hpp>
using namespace lec2::practice;
#else
#include <include/find_function_root.hpp>
#endif

using namespace lec2;

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// F(x)= X^3 + ax + b = с, где a > 0, b > 0, c > 0

TEST(find_function_root, hand_picked_coefficients) {
  const int expected_x = 3; // 27 + 3a + b = c, a = 3, b = 4, c = 27 + 9 + 4 = 40
  EXPECT_TRUE(expected_x == find_function_root(
                       3, 4, 40));
}

TEST(find_function_root, ground_truth_x_in_array) {
  vector<int> x_right, a, b, c(21);
  iota(begin(x_right), end(x_right), -10);
  iota(begin(a), end(a), 1);
  iota(begin(b), end(b), 1);

  auto getC = [](int a, int b, int x) { return x * x * x + a * x + b; };

  for (size_t i = 0; i < x_right.size(); ++i) {
    const int c = getC(a[i], b[i], x_right[i]);
    if (c <= 0)
      continue;
    EXPECT_TRUE(x_right[i] ==
                find_function_root(
                    a[i], b[i], c));
  }
}

TEST(find_function_root, ground_truth_x_random) {
  vector<int> a, b, c(21);
  iota(begin(a), end(a), 1);
  iota(begin(b), end(b), 1);

  int seed = 1272;
  mt19937 urng(seed);
  uniform_int_distribution<int> dist(-100, 100);

  auto getC = [](int a, int b, int x) { return x * x * x + a * x + b; };

  const int n_of_runs = a.size();
  for (int i = 0; i < n_of_runs; ++i) {
    int x_right = dist(urng);
    const int c = getC(a[i], b[i], x_right);
    if (c <= 0)
      continue;
    EXPECT_TRUE(x_right ==
                find_function_root(
                    a[i], b[i], c));
  }
}

TEST(find_function_root, ground_truth_x_random_coeffiecients_random) {
  int seed = 1272;
  mt19937 urng(seed);
  uniform_int_distribution<int> dist_x(-100, 100);
  uniform_int_distribution<int> dist_coeffiecients(1, 100);

  auto getC = [](int a, int b, int x) { return x * x * x + a * x + b; };

  const int n_of_runs = 21;
  for (int i = 0; i < n_of_runs; ++i) {
    int x_right = dist_x(urng);
    int a = dist_coeffiecients(urng);
    int b = dist_coeffiecients(urng);
    const int c = getC(a, b, x_right);
    if (c <= 0)
      continue;
    EXPECT_TRUE(
        x_right ==
        find_function_root(a, b, c));
  }
}