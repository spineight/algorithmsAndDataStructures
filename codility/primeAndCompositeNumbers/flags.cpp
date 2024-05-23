//! https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/flags/


int solution(vector<int> &A) {
  // 1 3 5 10
  const size_t n = A.size();
  vector<size_t> peaks;
  for(size_t i = 1; i < n-1; ++i) {
    if(A[i-1] < A[i] && A[i] > A[i+1])
      peaks.push_back(i);
  }
  size_t best{0};
  for(size_t k = peaks.size(); k >= 1; --k) {
    size_t soFar{1};
    auto it = begin(peaks);
    while(it != end(peaks) && soFar < k) {
      it = lower_bound(begin(peaks), end(peaks), *it + k);
      if(it != end(peaks)) ++soFar;
    }
    best = max(best, soFar);
  }
  return best;
}

//! 21/11/2023
//! looked up
int solution(vector<int> &A) {
  const int n = A.size();
  vector<int> peaks;
  for(int i = 1; i + 1 < n; ++i) {
    if(A[i-1] < A[i] && A[i+1] < A[i])
      peaks.push_back(i);
  }
  int best{0};
  for(int k = peaks.size(); k >= 1; --k) {
    auto it = begin(peaks);
    int soFar{0};
    while(it != end(peaks) && soFar < k) {
      ++soFar;
      it = lower_bound(begin(peaks), end(peaks), *it + k);
    }
    if(soFar == k) {
      best = soFar;
      break;
    }
  }
  return best;
}