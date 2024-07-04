//! https://app.codility.com/programmers/lessons/6-sorting/max_product_of_three/

/*


A non-empty array A consisting of N integers is given. The product of triplet (P, Q, R) equates to A[P] * A[Q] * A[R] (0 ≤ P < Q < R < N).

For example, array A such that:
  A[0] = -3
  A[1] = 1
  A[2] = 2
  A[3] = -2
  A[4] = 5
  A[5] = 6

contains the following example triplets:

        (0, 1, 2), product is −3 * 1 * 2 = −6
        (1, 2, 4), product is 1 * 2 * 5 = 10
        (2, 4, 5), product is 2 * 5 * 6 = 60

Your goal is to find the maximal product of any triplet.

Write a function:

    int solution(vector<int> &A);

that, given a non-empty array A, returns the value of the maximal product of any triplet.

For example, given array A such that:
  A[0] = -3
  A[1] = 1
  A[2] = 2
  A[3] = -2
  A[4] = 5
  A[5] = 6

the function should return 60, as the product of triplet (2, 4, 5) is maximal.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [3..100,000];
        each element of array A is an integer within the range [−1,000..1,000].


 */

#include <algorithm>
int solution(vector<int> &A) {
  sort(begin(A), end(A));
  const size_t n{A.size()};
  return max(A[0]*A[1]*A[n-1], A[n-1] * A[n-2] * A[n-3]);
}

//! 14/11/2023
int solution(vector<int> &A) {
  //! Non working solution:
  //! (for example: -2 -1 0 1 2)
  // const int n = A.size();
  // int best {A[0] * A[1] * A[2]};
  // sort(begin(A), end(A));
  // for(int i = 0; i + 2 < n; ++i) {
  //     const int soFar = A[i] * A[i+1] * A[i+2];
  //     best = max(best, soFar);
  // }
  // return best;
  sort(begin(A), end(A));
  const int n = A.size();
  return max({A[0] * A[1] * A[2], A[0] * A[1] * A.back(),
              A[0] * A[n-1] * A[n-2], A[n-1] * A[n-2] * A[n-3]});
}

//! 28/05/2024
//! Previous solutions are better (as they are shorter)
//! Idea of previous solutions - use sort to find 3 smallest and 3 biggest
#include <vector>

int solution(vector<int> &A) {
    std::vector<int> min_elems = {A[0], A[1], A[2]};
    sort(begin(min_elems), end(min_elems));

    std::vector<int> max_elems = {A[0], A[1], A[2]};
    sort(begin(max_elems), end(max_elems));

    const size_t n = A.size();
    int best = A[0] * A[1] * A[2];

    for(size_t i = 3; i < n; ++i) {
        const int soFar = max( { min_elems[0] * min_elems[1] * A[i], 
        min_elems[0] * max_elems[2] * A[i],
        max_elems[1] * max_elems[2] * A[i] });
        best = max(best, soFar);
        if(A[i] < min_elems.back()) {
            min_elems.back() = A[i];
            sort(begin(min_elems), end(min_elems));
        } else if(A[i] > max_elems.front()) {
            max_elems.front() = A[i];
            sort(begin(max_elems), end(max_elems));
        }
    }
    return best;
}