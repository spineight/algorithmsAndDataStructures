#include <bits/stdc++.h>
using namespace std;

//! BIT (BinaryIndexedTree or Fenwick tree)
//! https://github.com/spineight/AlgorithmsWilliamFiset/tree/master/src/main/java/com/williamfiset/algorithms/datastructures/fenwicktree
//! https://github.com/spineight/AlgorithmsWilliamFiset/blob/master/src/test/java/com/williamfiset/algorithms/datastructures/fenwicktree/FenwickTreeRangeQueryPointUpdateTest.java
//! https://github.com/spineight/AlgorithmsWilliamFiset/blob/master/src/test/java/com/williamfiset/algorithms/datastructures/fenwicktree/FenwickTreeRangeUpdatePointQueryTest.java

struct FenwickTree {
  vector<long long> tree_;
  FenwickTree(size_t n) : tree_(n+1, 0) {}
  FenwickTree(const vector<int>& values) : FenwickTree(values.size()+1) {
    for(int i = 1; i < tree_.size(); ++i)
      tree_[i] = values[i-1];

    for(int i = 1; i < tree_.size(); ++i) {
      int j = i + LSB(i);
      if(j < tree_.size()) tree_[j] += tree_[i];
    }

  }
  //! Get Least Significant Bit
  long long LSB(long long idx) const {
    return idx & -idx;
  }
  //! returns commulative sum of all elements up to k-th including it
  long long prefixSum(size_t k) {
    int idx = k;
    long long sum{0};
    while(idx > 0) {
      sum += tree_[idx];
      idx -= LSB(idx);
    }
    return sum;
  }

  //! sum of elements with indexes in the range [a,b]
  long long sum(size_t a, size_t b) {
    return prefixSum(b) - prefixSum(a-1);
  }
  //! changes idx element by d and adjust tree elements accordingly
  void update(size_t idx, long long d) {
    while(idx < tree_.size()) {
      tree_[idx] += d;
      idx += LSB(idx);
    }
  }
};

void testIntervalSumPositiveValues() {
  vector<int> ar = {1, 2, 3, 4, 5, 6};
  FenwickTree ft(ar);
  assert(ft.sum(1, 6) == 21);
  assert(ft.sum(1, 5) == 15);
  assert(ft.sum(1, 4) == 10);
  assert(ft.sum(1, 3) == 6);
  assert(ft.sum(1, 2) == 3);
  assert(ft.sum(1, 1) == 1);
  assert(ft.sum(1, 0) == 0);

  assert(ft.sum(3, 4) == 7);
  assert(ft.sum(2, 6) == 20);
  assert(ft.sum(4, 5) == 9);
  assert(ft.sum(6, 6) == 6);
  assert(ft.sum(5, 5) == 5);
  assert(ft.sum(4, 4) == 4);
  assert(ft.sum(3, 3) == 3);
  assert(ft.sum(2, 2) == 2);
  assert(ft.sum(1, 1) == 1);
}

void testIntervalSumNegativeValues() {

  vector<int> ar = {-1, -2, -3, -4, -5, -6};
  FenwickTree ft(ar);

  assert(ft.sum(1, 6) == -21);
  assert(ft.sum(1, 5) == -15);
  assert(ft.sum(1, 4) == -10);
  assert(ft.sum(1, 3) == -6);
  assert(ft.sum(1, 2) == -3);
  assert(ft.sum(1, 1) == -1);

  assert(ft.sum(6, 6) == -6);
  assert(ft.sum(5, 5) == -5);
  assert(ft.sum(4, 4) == -4);
  assert(ft.sum(3, 3) == -3);
  assert(ft.sum(2, 2) == -2);
  assert(ft.sum(1, 1) == -1);
}

void testIntervalSumNegativeValues2() {

  vector<int> ar = {-76871, -164790};
  FenwickTree ft(ar);
  for (int i = 0; i < 1000; i++) {
    assert(ft.sum(1, 1) == -76871);
    assert(ft.sum(1, 1) == -76871);
    assert(ft.sum(1, 2) == -241661);
    assert(ft.sum(1, 2) == -241661);
    assert(ft.sum(1, 2) == -241661);
    assert(ft.sum(2, 2) == -164790);
    assert(ft.sum(2, 2) == -164790);
    assert(ft.sum(2, 2) == -164790);
  }
}

vector<int> genRandomVector(size_t n) {
  vector<int> res(n);
  random_device rd;
  mt19937 urng(rd());
  uniform_int_distribution<int> distVals(numeric_limits<int>::min(), numeric_limits<int>::max());
  generate(begin(res), end(res), bind(distVals, ref(urng)));
  return res;
}

void doRandomRangeQuery(vector<int>& nums, FenwickTree& ft) {
  const int n = nums.size();
  const int low = max(1,rand() % n);
  const int high = min(low + (rand() % n), n);

  long long rangeSum{0};
  for(int i = low; i <= high; ++i)
     rangeSum += nums[i-1];
  assert(rangeSum == ft.sum(low,high));
}

void testRandomizedStaticSumQueries() {

  for (int i = 1; i <= 1000; i++) {

    auto nums = genRandomVector(i);
    FenwickTree ft(nums);

    for (int j = 0; j < 100; j++) {
      doRandomRangeQuery(nums, ft);
    }
  }
}

int main() {
  testIntervalSumPositiveValues();
  testIntervalSumNegativeValues();
  testIntervalSumNegativeValues2();

  testRandomizedStaticSumQueries();

  return 0;
}