//! Solved based on this solutions:
//! https://rafal.io/posts/codility-genomic-range-query.html
//! https://github.com/ZRonchy/Codility/blob/master/Lesson3/GenomicRangeQuery.java

/*


A DNA sequence can be represented as a string consisting of the letters A, C, G and T, which correspond to the types of successive nucleotides in the sequence. Each nucleotide has an impact factor, which is an integer. Nucleotides of types A, C, G and T have impact factors of 1, 2, 3 and 4, respectively. You are going to answer several queries of the form: What is the minimal impact factor of nucleotides contained in a particular part of the given DNA sequence?

The DNA sequence is given as a non-empty string S = S[0]S[1]...S[N-1] consisting of N characters. There are M queries, which are given in non-empty arrays P and Q, each consisting of M integers. The K-th query (0 ≤ K < M) requires you to find the minimal impact factor of nucleotides contained in the DNA sequence between positions P[K] and Q[K] (inclusive).

For example, consider string S = CAGCCTA and arrays P, Q such that:
    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6

The answers to these M = 3 queries are as follows:

        The part of the DNA between positions 2 and 4 contains nucleotides G and C (twice), whose impact factors are 3 and 2 respectively, so the answer is 2.
        The part between positions 5 and 5 contains a single nucleotide T, whose impact factor is 4, so the answer is 4.
        The part between positions 0 and 6 (the whole string) contains all nucleotides, in particular nucleotide A whose impact factor is 1, so the answer is 1.

Write a function:

    vector<int> solution(string &S, vector<int> &P, vector<int> &Q);

that, given a non-empty string S consisting of N characters and two non-empty arrays P and Q consisting of M integers, returns an array consisting of M integers specifying the consecutive answers to all queries.

Result array should be returned as a vector of integers.

For example, given the string S = CAGCCTA and arrays P, Q such that:
    P[0] = 2    Q[0] = 4
    P[1] = 5    Q[1] = 5
    P[2] = 0    Q[2] = 6

the function should return the values [2, 4, 1], as explained above.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..100,000];
        M is an integer within the range [1..50,000];
        each element of arrays P and Q is an integer within the range [0..N - 1];
        P[K] ≤ Q[K], where 0 ≤ K < M;
        string S consists only of upper-case English letters A, C, G, T.


 */

//! 10/15/2022
//! Idea: use prefixSum to count number of occurrences ( one per nucleotide type )
//!     for answering whether nucleotide of the given type occurred in the given interval
//! when answering a query: we are going through nucleotide types in order of values
//! we are interested with the first one with the positive count
//!
//! we only count A,C,G we don't need to count T, as if no positive count among A,C,G - when T occured
vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
  const int n = S.size();
  vector<vector<int>> prefixSum(n+1, vector<int>(3, 0));
  for(int i = 1; i <= n; ++i) {
    for(size_t j = 0; j <= 2; ++j) {
      prefixSum[i][j] = prefixSum[i-1][j];
    }


    switch (S[i-1]) {
      case 'A': ++prefixSum[i][0]; break;
      case 'C': ++prefixSum[i][1]; break;
      case 'G': ++prefixSum[i][2]; break;
    }
  }
  vector<int> res;
  for(size_t i = 0; i < P.size(); ++i) {
    for(size_t j = 0; j <= 2; ++j) {
      if( (prefixSum[Q[i] + 1][j] - prefixSum[P[i]][j]) > 0 ) {
        res.push_back(j + 1);
        break;
      }
    }
    if(res.size() < i+1) {
      res.push_back(4);
    }
  }
  return res;
}