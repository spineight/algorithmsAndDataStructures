//! https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_double_slice_sum/
/*


A non-empty array A consisting of N integers is given.

A triplet (X, Y, Z), such that 0 ≤ X < Y < Z < N, is called a double slice.

The sum of double slice (X, Y, Z) is the total of A[X + 1] + A[X + 2] + ... + A[Y − 1] + A[Y + 1] + A[Y + 2] + ... + A[Z − 1].

For example, array A such that:
    A[0] = 3
    A[1] = 2
    A[2] = 6
    A[3] = -1
    A[4] = 4
    A[5] = 5
    A[6] = -1
    A[7] = 2

contains the following example double slices:

        double slice (0, 3, 6), sum is 2 + 6 + 4 + 5 = 17,
        double slice (0, 3, 7), sum is 2 + 6 + 4 + 5 − 1 = 16,
        double slice (3, 4, 5), sum is 0.

The goal is to find the maximal sum of any double slice.

Write a function:

    int solution(vector<int> &A);

that, given a non-empty array A consisting of N integers, returns the maximal sum of any double slice.

For example, given:
    A[0] = 3
    A[1] = 2
    A[2] = 6
    A[3] = -1
    A[4] = 4
    A[5] = 5
    A[6] = -1
    A[7] = 2

the function should return 17, because no double slice of array A has a sum of greater than 17.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [3..100,000];
        each element of array A is an integer within the range [−10,000..10,000].
 */

int solution(vector<int> &A) {
  const size_t n{A.size()};
  vector<int> maxSumEnding(n,0), maxSumStarting(n,0);
  for(size_t i = 1; i < n-1; ++i)
    maxSumEnding[i] = max(maxSumEnding[i-1] + A[i], 0);
  for(int i = n-2; i > 0; --i)
    maxSumStarting[i] = max(maxSumStarting[i+1] + A[i], 0);

  int best{0};
  for(size_t i = 1; i < n-1; ++i) {
    best = max(best, maxSumEnding[i-1] + maxSumStarting[i+1]);
  }
  return best;
}

//! 16/11/2023
//! I looked at my previous solution
//! Improved it a little bit: we can calculate maxSums in one loop
int solution(vector<int> &A) {
  const int n = A.size();
  vector<int> maxSumEndingHere(n, 0);
  vector<int> maxSumStartingHere(n,0);
  for(int i = 1; i < n; ++i) {
    //! we could replace by 0 if place delimeters L,M close to each other
    //! this will result in empty left part, sum of which is 0
    maxSumEndingHere[i] = max(0, maxSumEndingHere[i-1] + A[i]);
    maxSumStartingHere[n-1-i] = max(0, maxSumStartingHere[n-i] + A[n-1-i]);
  }
  int best{0};
  //! select where to put middle delemiter, to maximize the total result
  for(int m = 1; m + 1 < n; ++m) {
    best = max(best, maxSumEndingHere[m-1] + maxSumStartingHere[m+1]);
  }
  return best;
}