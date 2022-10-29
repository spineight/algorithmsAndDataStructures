//! https://app.codility.com/programmers/lessons/15-caterpillar_method/count_distinct_slices/

/*


An integer M and a non-empty array A consisting of N non-negative integers are given. All integers in array A are less than or equal to M.

A pair of integers (P, Q), such that 0 ≤ P ≤ Q < N, is called a slice of array A. The slice consists of the elements A[P], A[P + 1], ..., A[Q]. A distinct slice is a slice consisting of only unique numbers. That is, no individual number occurs more than once in the slice.

For example, consider integer M = 6 and array A such that:
    A[0] = 3
    A[1] = 4
    A[2] = 5
    A[3] = 5
    A[4] = 2

There are exactly nine distinct slices: (0, 0), (0, 1), (0, 2), (1, 1), (1, 2), (2, 2), (3, 3), (3, 4) and (4, 4).

The goal is to calculate the number of distinct slices.

Write a function:

    int solution(int M, vector<int> &A);

that, given an integer M and a non-empty array A consisting of N integers, returns the number of distinct slices.

If the number of distinct slices is greater than 1,000,000,000, the function should return 1,000,000,000.

For example, given integer M = 6 and array A such that:
    A[0] = 3
    A[1] = 4
    A[2] = 5
    A[3] = 5
    A[4] = 2

the function should return 9, as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..100,000];
        M is an integer within the range [0..100,000];
        each element of array A is an integer within the range [0..M].
 */

//! Based on this:
//! https://stackoverflow.com/questions/64728599/how-to-solve-countdistinctslices-codility-question

#include <unordered_set>
int solution(int M, vector<int> &A) {
  const size_t n{A.size()};
  std::unordered_set<int> inSlice;
  size_t res{0};
  size_t l{0};
  for(size_t r = 0; r < n && l < n; ++r) {
    while(inSlice.count(A[r])) {
      inSlice.erase(A[l]);
      ++l;
    }
    inSlice.insert(A[r]);
    res += r-l+1;
    if(res > 1'000'000'000) return 1'000'000'000;
  }
  return res;
}