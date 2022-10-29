//! https://app.codility.com/programmers/lessons/7-stacks_and_queues/stone_wall/

#include <stack>
int solution(vector<int> &H) {
  size_t cnt{0};
  stack<int> blocks;
  for(size_t i = 0; i < H.size(); ++i) {
    while(!blocks.empty() && blocks.top() > H[i])
      blocks.pop();
    if(blocks.empty() || blocks.top() < H[i]) {
      ++cnt;
      blocks.push(H[i]);
    }
  }
  return cnt;
}