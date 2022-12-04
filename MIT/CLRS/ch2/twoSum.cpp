#include <bits/stdc++.h>
using namespace std;

//! O(nlogn)
optional<pair<int,int>> twoSumVer0(const vector<int>& a, int targetSum) {
  const int n = a.size();
  vector<int> tmp(a);
  sort(begin(tmp), end(tmp));
  int l = 0;
  int r{n-1};
  while(l < r) {
    if(tmp[l] + tmp[r] > targetSum) --r;
    else if (tmp[l] + tmp[r] < targetSum) ++l;
    else return pair<int,int>{tmp[l],tmp[r]};
  }
  return nullopt;
}

//! O(n)
optional<pair<int,int>> twoSumVer1(const vector<int>& a, int targetSum) {
  const int n = a.size();
  unordered_map<int,int> freq;
  for(int i = 0; i < n; ++i) {
    const int d = targetSum - a[i];
    if(freq.contains(d)) return pair<int,int>{a[i], d};
    ++freq[a[i]];
  }
  return nullopt;
}

int main() {
  mt19937 engine;
  uniform_int_distribution<int> dist(0,50);
  int nOfIter{1000};
  while(nOfIter--) {
    vector<int> a(20);
    for(auto& v : a) v = dist(engine);
    auto res0 = twoSumVer0(a, 15);
    auto res1 = twoSumVer1(a, 15);
    assert( (res0 && res1) || (!res0 && ! res1));
    if(res0) {
      cout << "res0:" << res0->first << "," << res0->second << '\n';
    }
    if(res1) {
      cout << "res1:" << res1->first << "," << res1->second << '\n';
      cout << '\n';
    }
  }
  return 0;
}