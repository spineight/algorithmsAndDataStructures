/*
  Write a function:

    int solution(vector<int> &A);

that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.

For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.

Given A = [1, 2, 3], the function should return 4.

Given A = [−1, −3], the function should return 1.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..100,000];
        each element of array A is an integer within the range [−1,000,000..1,000,000].


 */

#include <unordered_set>
int solution(vector<int> &A) {
  std::unordered_set<int> seen;
  for(auto v : A) {
    if(v > 0) seen.insert(v);
  }
  if(seen.empty()) return 1;
  const int MAX_N{1'000'000};
  for(int i = 1; i <= MAX_N; ++i) {
    if(!seen.count(i)) return i;
  }
  return -1;
}

//! 11/11/2023
int solution(vector<int> &A) {
  auto last = remove_if(begin(A), end(A), [](int val) {
    return val < 0;
  });


  sort(begin(A), last);

  const int n = distance(begin(A), last);
  if(n == 0) return 1;

  if(A.front() > 1) return 1;

  int i = 1;
  for(; i < n; ++i) {
    if(A[i]-A[i-1] > 1) return A[i-1]+1;
  }
  return A[i-1] + 1;
}