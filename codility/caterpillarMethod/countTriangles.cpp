//! https://app.codility.com/programmers/lessons/15-caterpillar_method/count_triangles/
/*


An array A consisting of N integers is given. A triplet (P, Q, R) is triangular if it is possible to build a triangle with sides of lengths A[P], A[Q] and A[R]. In other words, triplet (P, Q, R) is triangular if 0 ≤ P < Q < R < N and:

        A[P] + A[Q] > A[R],
        A[Q] + A[R] > A[P],
        A[R] + A[P] > A[Q].

For example, consider array A such that:
  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 12

There are four triangular triplets that can be constructed from elements of this array, namely (0, 2, 4), (0, 2, 5), (0, 4, 5), and (2, 4, 5).

Write a function:

    int solution(vector<int> &A);

that, given an array A consisting of N integers, returns the number of triangular triplets in this array.

For example, given array A such that:
  A[0] = 10    A[1] = 2    A[2] = 5
  A[3] = 1     A[4] = 8    A[5] = 12

the function should return 4, as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [0..1,000];
        each element of array A is an integer within the range [1..1,000,000,000].
 */

//! Implementation is based on 13-CaterpillarMethod
#include <algorithm>
int solution(vector<int> &A) {
  const size_t n{A.size()};
  sort(begin(A), end(A));
  size_t res{0};
  for(size_t x = 0; x < n; ++x) {
    size_t z = x + 2;
    for(size_t y = x + 1; y < n; ++y) {
      while(z < n && A[x]+A[y] > A[z]) ++z;
      res += z-y-1;
    }
  }
  return res;
}