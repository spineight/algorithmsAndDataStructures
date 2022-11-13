/* There are N points located on a line, numbered from 0 to N-1, whose coordinates are given in an array A.
The coordinates of points don`t have to be distinct

For a given integer M, a subset of these points is said to be M-aligned if the distance between any two points
within the subset is divisible by M.

Your task is to find the size of the largest M-aligned subset of the given set of N points.int

For ex.
 M = 3
 [-3,-2,1,0,8,7,1]

 a subset [-2,1,7,1] - is an example of a 3-aligned subset

 elements in [-1'000'000'000, 1'000'000'000]
*/

#include <unordered_map>

int solution(vector<int>& A, int M) {
  unordered_map<int,int> remindersCnt;
  int best{0};
  for(auto v : A) {
    v += 1'000'000'000;
    auto soFar = ++remaindersCnt[v%M];
    best = max(best, soFar);
  }
  return best;
}