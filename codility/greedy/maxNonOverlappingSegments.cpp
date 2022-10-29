//! https://app.codility.com/programmers/lessons/16-greedy_algorithms/max_nonoverlapping_segments/

/*


 */
int solution(vector<int> &A, vector<int> &B) {
  if(A.empty()) return 0;
  size_t cnt{1};
  int prevEnd = B[0];
  for(size_t i = 1; i < A.size(); ++i) {
    if(A[i] > prevEnd) {
      ++cnt;
      prevEnd = B[i];
    }
  }
  return cnt;
}