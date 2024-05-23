/*


A non-empty array A consisting of N integers is given.

A permutation is a sequence containing each element from 1 to N once, and only once.

For example, array A such that:
    A[0] = 4
    A[1] = 1
    A[2] = 3
    A[3] = 2

is a permutation, but array A such that:
    A[0] = 4
    A[1] = 1
    A[2] = 3

is not a permutation, because value 2 is missing.

The goal is to check whether array A is a permutation.

Write a function:

    int solution(vector<int> &A);

that, given an array A, returns 1 if array A is a permutation and 0 if it is not.

For example, given array A such that:
    A[0] = 4
    A[1] = 1
    A[2] = 3
    A[3] = 2

the function should return 1.

Given array A such that:
    A[0] = 4
    A[1] = 1
    A[2] = 3

the function should return 0.

Write an efficient algorithm for the following assumptions:

        N is an integer within the range [1..100,000];
        each element of array A is an integer within the range [1..1,000,000,000].


 */

#include <unordered_set>
int solution(vector<int> &A) {
  if(A.empty()) return false;
  std::unordered_set<int> us;
  int maxNum{A.front()};
  for(auto v : A) {
    us.insert(v);
    maxNum = max(maxNum, v);
  }
  if(us.size() == A.size() && maxNum == static_cast<int>(A.size()) )
    return 1;
  return 0;
}

//! 11/11/2023
#include <unordered_set>

int solution(vector<int> &A) {
  const int n = A.size();
  unordered_set<int> nums;
  for(auto v : A) {
    if(v > n) return 0;
    auto [_, ok] = nums.insert(v);
    if(!ok) return 0;
  }
  return nums.size() == n;
}