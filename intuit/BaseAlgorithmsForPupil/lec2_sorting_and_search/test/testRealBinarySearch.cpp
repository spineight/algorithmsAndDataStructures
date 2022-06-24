#include <gtest/gtest.h>

#ifdef PRACTICE
#include <practice/PreciseRealBinarySearch.hpp>
using namespace lec2::practice;
#else
#include <include/PreciseRealBinarySearch.hpp>
#endif

using namespace lec2;

#include <vector>
#include <algorithm>
#include <random>

using namespace std;

TEST(real_binary_search, find_root_of_equation) {
  // Важно (x-3) * (x-3) - не подойдет, так как это не монотонная функция
  auto fn = [](double x) { return (x - 3) * (x - 3) * (x - 3); };
  double res =
      real_binary_search_ver(fn, 0);
  EXPECT_DOUBLE_EQ(res, 3.);
}