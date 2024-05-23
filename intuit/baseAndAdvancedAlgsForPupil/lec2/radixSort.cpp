#include <bits/stdc++.h>
using namespace std;

//! Radix - the base of a system of numeration
//! We use LSD sort - start from less significant digits
void radixSort(vector<uint32_t>& a) {
  if(!a.empty()) {
    // https://en.cppreference.com/w/cpp/types/integer
    constexpr uint16_t RADIX{256};
    constexpr uint16_t  BLOCK_SZ_BITS{8};
    // for counting sort:
    size_t cnt[RADIX];
    vector<uint32_t> aux(a);
    // numbers are divided into blocks of BLOCK_SZ_BITS
    for (size_t blockIdx = 0; blockIdx < sizeof(uint32_t)/*4 blocks, each of 8 bits in size*/; ++blockIdx) {
      memset(cnt, 0, sizeof(cnt));
      for (auto v: a) {
        uint32_t blockKey = (v >> blockIdx * BLOCK_SZ_BITS) & (RADIX - 1);
        ++cnt[blockKey];
      }
      // to save memory reuse cnt array for prefixSum array
      for (size_t k = 1; k < size(cnt); ++k) {
        cnt[k] += cnt[k - 1];
      }
      // we go in reverse order as numbers will be put starting at the end of a block and towards the beggining
      // this is required for couintingSort to be stable (see countingSort.cpp for details)
      for (int i = a.size()-1; i >= 0; --i) {
        uint32_t blockKey = (a[i] >> blockIdx * BLOCK_SZ_BITS) & (RADIX - 1);
        // --cnt - as it is number of elements and we need a position in 0 indexed array
        aux[--cnt[blockKey]] = a[i];
      }
      copy(begin(aux), end(aux), begin(a));
    }
  }
}

int main() {
  vector<uint32_t> a = {111111111,222222222,333333333,444444444,111112222, 111113333};
  radixSort(a);
  for(auto v : a) cout << v << ' ';
  cout << '\n';

  random_device rd;
  mt19937 engine(rd());
  uniform_int_distribution<uint32_t> valDist(0,numeric_limits<uint32_t>::max());
  uniform_int_distribution<uint32_t> szDist(0,10'000);

  constexpr size_t iterCnt{1000};
  for(size_t i = 0; i < iterCnt; ++i) {
    vector<uint32_t> a(szDist(engine));
    std::generate(a.begin(), a.end(),[&](){return valDist(engine);});
    vector<uint32_t> groundTruth(a);
    sort(begin(groundTruth), end(groundTruth));
    radixSort(a);
    assert(a == groundTruth);
  }
  return 0;
}