//! https://app.codility.com/programmers/lessons/12-euclidean_algorithm/common_prime_divisors/

/*


A prime is a positive integer X that has exactly two distinct divisors: 1 and X. The first few prime integers are 2, 3, 5, 7, 11 and 13.

A prime D is called a prime divisor of a positive integer P if there exists a positive integer K such that D * K = P. For example, 2 and 5 are prime divisors of 20.

You are given two positive integers N and M. The goal is to check whether the sets of prime divisors of integers N and M are exactly the same.

For example, given:

        N = 15 and M = 75, the prime divisors are the same: {3, 5};
        N = 10 and M = 30, the prime divisors aren't the same: {2, 5} is not equal to {2, 3, 5};
        N = 9 and M = 5, the prime divisors aren't the same: {3} is not equal to {5}.

Write a function:

    int solution(vector<int> &A, vector<int> &B);

that, given two non-empty arrays A and B of Z integers, returns the number of positions K for which the prime divisors of A[K] and B[K] are exactly the same.

For example, given:
    A[0] = 15   B[0] = 75
    A[1] = 10   B[1] = 30
    A[2] = 3    B[2] = 5

the function should return 1, because only one pair (15, 75) has the same set of prime divisors.

Write an efficient algorithm for the following assumptions:

        Z is an integer within the range [1..6,000];
        each element of arrays A and B is an integer within the range [1..2,147,483,647].
 */

int gcd(int a, int b) {
  if(a < b) swap(a,b);
  while(b) {
    int tmp = b;
    b = a%b;
    a = tmp;
  }
  return a;
}


int solution(vector<int> &A, vector<int> &B) {
  int cnt{0};
  for(size_t i = 0; i < A.size(); ++i) {
    int a = A[i];
    int b = B[i];

    int gcd_ab = gcd(a,b);

    while(a != 1) {
      int gcd_a = gcd(a, gcd_ab);
      if(gcd_a == 1) break;
      a /= gcd_a;
    }
    if(a == 1) {
      while(b != 1) {
        int gcd_b = gcd(b, gcd_ab);
        if(gcd_b == 1) break;
        b /= gcd_b;
      }
      if(b == 1) ++cnt;
    }
  }
  return cnt;
}