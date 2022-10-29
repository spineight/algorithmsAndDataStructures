//! https://app.codility.com/programmers/lessons/5-prefix_sums/count_div/
/*
Write a function:

    int solution(int A, int B, int K);

that, given three integers A, B and K, returns the number of integers within the range [A..B] that are divisible by K, i.e.:

    { i : A ≤ i ≤ B, i mod K = 0 }

For example, for A = 6, B = 11 and K = 2, your function should return 3, because there are three numbers divisible by 2 within the range [6..11], namely 6, 8 and 10.

Write an efficient algorithm for the following assumptions:

        A and B are integers within the range [0..2,000,000,000];
        K is an integer within the range [1..2,000,000,000];
        A ≤ B.

 */

#include <cmath>
int solution(int A, int B, int K) {
  // 1 2 3 4 5 6 7    7
  // (7-1+1) / 7      1
  //
  // 1 2 3 4 5 6      7
  // (6-1+1) / 7      0
  //
  // 6 7 8 9 10
  // (10-6+1) / 7     0

  // 7 8 9 10 11 12 13
  // 7 8 9 10 11 12 14 15 16 17 18 19 20 21

  if( (A % K) == 0 ) {
    return 1 + (B-A) / K;
  }
  // 22 23 24 25 26 27 28
  const int firstDiv = ceil(A / static_cast<double>(K)) * K;
  if(firstDiv < B) {
    return (B-firstDiv) / K + 1;
  }
  if(firstDiv == B) return 1;

  return 0;
}