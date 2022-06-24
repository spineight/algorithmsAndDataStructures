#include <bits/stdc++.h>
using namespace std;

//! Radix - the base of a system of numeration
//! We use LSD sort - start from less significant digits
void radixSort(vector<uint32_t>& nums) {
  // https://en.cppreference.com/w/cpp/types/integer
  static const uint16_t RADIX{256};
  const int n = nums.size();
  // for counting sort:
  size_t cnt[256];
  vector<uint32_t> res(n);
  // numbers are divided into blocks of 4 bytes
  for(size_t i = 0; i < sizeof(uint32_t); ++i) {
    memset(cnt,0,sizeof(cnt));
    for(auto v : nums) {
      uint32_t blockVal = (v >> i * 8) & (RADIX-1);
      ++cnt[blockVal];
    }
    // to save memory reuse cnt array for prefixSum array
    for(size_t k = 1; k < size(cnt); ++k) {
      cnt[k] += cnt[k-1];
    }
    // we go in reverse order as numbers will be put starting at the end of a block and towards the beggining
    // this is required for couintingSort to be stable (see countingSort.cpp for details)
    for(int j = n-1; j >= 0; --j) {
      uint32_t blockVal = (nums[j] >> i * 8) & (RADIX-1);
      // as cnt[blockVal] - one element after the block end we do: cnt[blockVal]-1
      res[cnt[blockVal]-1] = nums[j];
      --cnt[blockVal];
    }
    copy(begin(res), end(res), begin(nums));
  }
}

int main() {
  vector<uint32_t> a = {111111111,222222222,333333333,444444444,111112222, 111113333};
  radixSort(a);
  for(auto v : a) cout << v << ' ';
  cout << '\n';
  return 0;
}