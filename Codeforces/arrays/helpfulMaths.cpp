//! https://codeforces.com/group/yg7WhsFsAp/contest/355490/problem/P06

#include <bits/stdc++.h>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  string s;
  cin >> s;
  vector<int> nums;
  for(int i = 0; i < s.size(); i += 2) {
    nums.push_back(s[i]-'0');
  }
  sort(begin(nums), end(nums));
  for(int i = 0; i < nums.size() - 1; ++i) {
    cout << nums[i] << "+";
  }
  cout << nums.back() << '\n';
  return 0;
}