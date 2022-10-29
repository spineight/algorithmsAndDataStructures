//! https://app.codility.com/programmers/lessons/8-leader/equi_leader/

/*

A non-empty array A consisting of N integers is given.

The leader of this array is the value that occurs in more than half of the elements of A.

An equi leader is an index S such that 0 ≤ S < N − 1 and two sequences A[0], A[1], ..., A[S] and A[S + 1], A[S + 2], ..., A[N − 1] have leaders of the same value.

For example, given array A such that:
A[0] = 4
A[1] = 3
A[2] = 4
A[3] = 4
A[4] = 4
A[5] = 2

we can find two equi leaders:

0, because sequences: (4) and (3, 4, 4, 4, 2) have the same leader, whose value is 4.
2, because sequences: (4, 3, 4) and (4, 4, 2) have the same leader, whose value is 4.

The goal is to count the number of equi leaders.

Write a function:

int solution(vector<int> &A);

that, given a non-empty array A consisting of N integers, returns the number of equi leaders.

For example, given:
A[0] = 4
A[1] = 3
A[2] = 4
A[3] = 4
A[4] = 4
A[5] = 2

the function should return 2, as explained above.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000,000..1,000,000,000].

*/

int solution(vector<int> &A) {
  const size_t n{A.size()};
  if(n == 1) return 0;

  int candidate = A.front();
  size_t cnt{1};
  for(size_t i = 1; i < n; ++i) {
    if(candidate == A[i]) ++cnt;
    else {
      --cnt;
      if(0 == cnt){
        candidate = A[i];
        ++cnt;
      }
    }
  }

  size_t candidateCnt{0};
  for(size_t i = 0; i < n; ++i) {
    if(candidate == A[i]) ++candidateCnt;
  }
  // if(candidateCnt * 2 <= n) return 0;

  size_t equiCnt{0};

  size_t curCnt{0};
  for(size_t i = 0; i < n; ++i) {
    if(A[i] == candidate) ++curCnt;
    if( ((i+1) < curCnt * 2) && ( (candidateCnt - curCnt) * 2 >  n - i - 1) )
      ++equiCnt;
  }
  return equiCnt;
}