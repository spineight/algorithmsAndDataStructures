//! https://app.codility.com/programmers/lessons/8-leader/dominator/
/*


An array A consisting of N integers is given. The dominator of array A is the value that occurs in more than half of the elements of A.

For example, consider array A such that
 A[0] = 3    A[1] = 4    A[2] =  3
 A[3] = 2    A[4] = 3    A[5] = -1
 A[6] = 3    A[7] = 3

The dominator of A is 3 because it occurs in 5 out of 8 elements of A (namely in those with indices 0, 2, 4, 6 and 7) and 5 is more than a half of 8.

Write a function

    int solution(vector<int> &A);

that, given an array A consisting of N integers, returns index of any element of array A in which the dominator of A occurs. The function should return −1 if array A does not have a dominator.

For example, given array A such that
 A[0] = 3    A[1] = 4    A[2] =  3
 A[3] = 2    A[4] = 3    A[5] = -1
 A[6] = 3    A[7] = 3

the function may return 0, 2, 4, 6 or 7, as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [0..100,000];
        each element of array A is an integer within the range [−2,147,483,648..2,147,483,647].
 */

int solution(vector<int> &A) {
  const size_t n{A.size()};
  if(n == 0) return -1;
  if(n == 1) return 0;

  size_t cnt{1};

  int candidate{A.front()};
  for(size_t i = 1; i < n; ++i) {
    if(candidate == A[i]) ++cnt;
    else {
      --cnt;
      if(0 == cnt) {
        candidate = A[i];
        ++cnt;
      }
    }
  }
  int lastIdx{-1};
  size_t candidateCnt{0};
  for(size_t i = 0; i < n; ++i) {
    if(A[i] == candidate) {
      ++candidateCnt;
      lastIdx = i;
    }
  }
  if(candidateCnt > n / 2)
    return lastIdx;
  return -1;
}