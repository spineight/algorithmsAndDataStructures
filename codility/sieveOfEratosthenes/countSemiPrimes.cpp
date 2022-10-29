//! https://app.codility.com/programmers/lessons/11-sieve_of_eratosthenes/count_semiprimes/
/*


A prime is a positive integer X that has exactly two distinct divisors: 1 and X. The first few prime integers are 2, 3, 5, 7, 11 and 13.

A semiprime is a natural number that is the product of two (not necessarily distinct) prime numbers. The first few semiprimes are 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.

You are given two non-empty arrays P and Q, each consisting of M integers. These arrays represent queries about the number of semiprimes within specified ranges.

Query K requires you to find the number of semiprimes within the range (P[K], Q[K]), where 1 ≤ P[K] ≤ Q[K] ≤ N.

For example, consider an integer N = 26 and arrays P, Q such that:
    P[0] = 1    Q[0] = 26
    P[1] = 4    Q[1] = 10
    P[2] = 16   Q[2] = 20

The number of semiprimes within each of these ranges is as follows:

        (1, 26) is 10,
        (4, 10) is 4,
        (16, 20) is 0.

Write a function:

    vector<int> solution(int N, vector<int> &P, vector<int> &Q);

that, given an integer N and two non-empty arrays P and Q consisting of M integers, returns an array consisting of M elements specifying the consecutive answers to all the queries.

For example, given an integer N = 26 and arrays P, Q such that:
    P[0] = 1    Q[0] = 26
    P[1] = 4    Q[1] = 10
    P[2] = 16   Q[2] = 20

the function should return the values [10, 4, 0], as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..50,000];
        M is an integer within the range [1..30,000];
        each element of arrays P and Q is an integer within the range [1..N];
        P[i] ≤ Q[i].
 */

#include <unordered_set>
vector<int> solution(int N, vector<int> &P, vector<int> &Q) {
  size_t n = N;
  vector<size_t> sieve(N+1, 1);
  size_t i {2};
  while(i*i <= n) {
    if(sieve[i]) {
      size_t k = i * i;

      while(k <= n) {
        sieve[k] = 0;
        k += i;
      }
    }
    ++i;
  }

  vector<size_t> primes;
  for(size_t i = 2; i <= n; ++i) {
    if(sieve[i]) primes.push_back(i);
  }
  unordered_set<size_t> semiPrimes;

  for(size_t i = 0; i < primes.size() && i*i <= n; ++i) {
    for(size_t j = i; j < primes.size() && i * j <= n; ++j) {
      semiPrimes.insert(primes[i] * primes[j]);
    }
  }
  vector<size_t> prefixSum(n+2, 0);
  for(size_t i = 1; i <= n+1; ++i) {
    prefixSum[i] = prefixSum[i-1];
    if(semiPrimes.count(i)) {
      ++prefixSum[i];
    }
  }
  vector<int> res;
  for(size_t i = 0; i < P.size(); ++i) {
    const int cnt = prefixSum[Q[i]] - prefixSum[P[i]-1];
    res.push_back(cnt);
  }
  return res;
}