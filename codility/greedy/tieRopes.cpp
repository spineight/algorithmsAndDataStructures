//! https://app.codility.com/programmers/lessons/16-greedy_algorithms/tie_ropes/

int solution(int K, vector<int> &A) {
  int soFar{0};
  size_t cnt{0};
  for(size_t i = 0; i < A.size(); ++i) {
    soFar += A[i];
    if(soFar >= K) {
      ++cnt;
      soFar = 0;
    }
  }
  return cnt;
}
