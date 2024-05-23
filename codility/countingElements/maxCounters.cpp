/*


You are given N counters, initially set to 0, and you have two possible operations on them:

        increase(X) − counter X is increased by 1,
        max counter − all counters are set to the maximum value of any counter.

A non-empty array A of M integers is given. This array represents consecutive operations:

        if A[K] = X, such that 1 ≤ X ≤ N, then operation K is increase(X),
        if A[K] = N + 1 then operation K is max counter.

For example, given integer N = 5 and array A such that:
    A[0] = 3
    A[1] = 4
    A[2] = 4
    A[3] = 6
    A[4] = 1
    A[5] = 4
    A[6] = 4

the values of the counters after each consecutive operation will be:
    (0, 0, 1, 0, 0)
    (0, 0, 1, 1, 0)
    (0, 0, 1, 2, 0)
    (2, 2, 2, 2, 2)
    (3, 2, 2, 2, 2)
    (3, 2, 2, 3, 2)
    (3, 2, 2, 4, 2)

The goal is to calculate the value of every counter after all operations.

Write a function:

    vector<int> solution(int N, vector<int> &A);

that, given an integer N and a non-empty array A consisting of M integers, returns a sequence of integers representing the values of the counters.

Result array should be returned as a vector of integers.

For example, given:
    A[0] = 3
    A[1] = 4
    A[2] = 4
    A[3] = 6
    A[4] = 1
    A[5] = 4
    A[6] = 4

the function should return [3, 2, 2, 4, 2], as explained above.

Write an efficient algorithm for the following assumptions:

        N and M are integers within the range [1..100,000];
        each element of array A is an integer within the range [1..N + 1].


 */

vector<int> solution(int N, vector<int> &A) {
  vector<int> counters(N);
  int activeMax{0}, curMax{0};
  for(auto v : A) {
    const int idx = v-1;
    if(v <= N) {
      counters[idx] = max(counters[idx], activeMax);
      ++counters[idx];
      curMax = max(curMax, counters[idx]);
    } else {
      activeMax = curMax;
    }
  }
  for(auto& v : counters) v = max(v, activeMax);
  return counters;
}

//! 11/11/2023
//! idea: when max val should be set we don't assign it to all elements (performance consideration)
//!     instead we set this as offset
//!     later one when some element is touched - we update it(+1) taking into account the offset
//!     at the end of iterarions some elements maybe untouched - for them we set their value to offset
vector<int> solution(int N, vector<int> &A) {
  int maxVal{0};
  int offset{0};
  vector<int> res(N,0);

  for(auto v : A) {
    // set max counter
    if(v > N) {
      offset = maxVal;
    } else {
      res[v-1] = max(res[v-1], offset);
      ++res[v-1];
      maxVal = max(maxVal, res[v-1]);
    }
  }
  for(auto& v : res) {
    v = max(v, offset);
  }
  return res;
}
