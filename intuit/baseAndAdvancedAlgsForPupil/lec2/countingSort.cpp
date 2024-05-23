#include <bits/stdc++.h>

using namespace std;

void countingSort(vector<uint32_t> &a) {
  static constexpr uint32_t MAX_VAL{10'000};
  uint32_t gCount[MAX_VAL+1] = {0};

  for (auto v : a) ++gCount[v];
  int i{0};
  for (int j = 0; j <= MAX_VAL; ++j) {
    while (gCount[j]) {
      a[i] = j;
      --gCount[j];
      ++i;
    }
  }
}

/*!
 * Based on Сергей Копелиович lecture


 The idea is not to copy elements into resulting array (as they might be expensive to copy (for ex. strings of length 10000)),
 rather return permutation: which maps idx of element in initial sequence to idx in the resulting sequence

 we sort pair (keys[i], data[i]) - each key has a data associated with it
 */
template<uint32_t MAX_N, typename T>
void countingSort(const vector<uint32_t>& keys, const vector<T>& data, vector<uint32_t>& permutation) {
  //! 1. count elements
  vector<uint32_t> cnt(MAX_N+1,0);
  for(auto& k : keys) ++cnt[k];

  //! 2. calculate prefix sum, we reuse cnt array for it
  // cnt[i]-1 - position of the last element of i-th class
  for(int i = 1; i <= MAX_N; ++i)
    cnt[i] += cnt[i-1];

  //! 3. construct resulting permutation
  //! here important that we go from the end, as we have pos of last element of class - we fill the class from end to begin
  //! and if we traverse elements in reverse order - we will get resulting sequence preserving of order for elements within one class
  //! Hence this sorting will be stable, this important property that allows to use it for Radix sort
  for(int i = (int)keys.size()-1; i >=0 ; --i) {
    //! --cnt - it is number of elements and we need position in 0 indexed array
    permutation[--cnt[keys[i]]] = i;
  }
}


int main() {
  vector<uint32_t> a = {5, 4, 3, 2, 1};;
  countingSort(a);
  for (auto v : a) cout << v << " ";
  cout << '\n';

  vector<uint32_t> keys = {3,6,6,3,6,9,2,2,1,4};
  vector<string> data = {"4", "7", "8", "5", "9", "10", "2", "3", "1", "6"};
  assert(keys.size() == data.size());
  vector<uint32_t> permutation(keys.size());
  countingSort<100, string>(keys, data,permutation);
  //! shows how given the permutation output data in the sorted order (by keys)
  for(int i = 0; i < permutation.size(); ++i) {
    cout << data[permutation[i]] << " ";
  }
  cout << '\n';
  return 0;
}