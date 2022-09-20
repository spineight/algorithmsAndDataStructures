#include <bits/stdc++.h>
using namespace std;

int main() {
  //! Precompute combinations table, to be able to answer C(n,k)
  constexpr int MAX_N {1000};
  //! C(n,k) - number of ways to choose k elements from n
  //!
  //! Recurrence C(n,k) = C(n-1, k-1) + C(n-1, k)
  //! C(n-1,k-1) = resulting sets with the element included
  //! C(n-1, k) = number of sets without given element
  //!
  //! C(n,k) = k-th binomial coefficient: C(n,k)*a^k*b^(n-k) of  (a+b)^n
  //!
  //! Elements of recurrence: base, generic step
  long long C[MAX_N][MAX_N];
  //! Base
  for(int i = 0; i <= MAX_N; ++i) {
    C[i][0] = 1; //! There is only one way to pick 0 elements from i elements - pick empty set
    C[i][i] = 1; //! There is only one way to pick i elements from i elements - pick all elements
  }
  //! generic step
  for(int i = 1; i <= MAX_N; ++i) {
    for(int j = 1; j < i; ++j) //! when j > i - we always have 0 ways to pick j elements from i; When j == i - we calculated in the base case
      C[i][j] = C[i-1][j-1] + C[i-1][j];
  }

  //! Although there is a formula for C(n,k) = n! /  ( (n-k)! * k!) ) as it could easily overflow
  //! on practice the use recurrence relation and use dp(to not solve the same subproblem again)

  //check C(5,3) = 5! / ( (5-3)! * 3!) = 5 * 4 / 2 = 10
  cout << C[5][3] << '\n'; // 10

  //check C(8,5) = 8! / ( (8-5)! * 5!) = 8 * 7 * 6 / 6 = 56
  cout << C[8][5] << '\n'; // 56

  //check C(8,3) = 8! / ( (8-3)! * 3!) = 8 * 7 * 6 / 6 = 56
  cout << C[8][5] << '\n'; // 56

  //check C(10,3) = 10! / ( (10-3)! * 3!) = 10 * 9 * 8  / 6 = 10 * 3 * 3 * 2 * 4 / 6 = 120
  cout << C[10][3] << '\n'; // 120
  return 0;
}