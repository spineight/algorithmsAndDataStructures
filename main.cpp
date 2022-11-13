#include <bits/stdc++.h>
using namespace std;


int solution(vector<int> &A, int M) {
  map<int ,size_t> freq;
  for(auto v : A) ++freq[v];

  int best{0};
  while(!freq.empty()) {
    auto it = begin(freq);
    int soFar{0};
    cout << "it->first: " << it->first << '\n';

    while(it != end(freq)) {
      soFar += it->second;
      auto nextIt = freq.find(it->first + M);
      freq.erase(it);
      it = nextIt;
    }
    cout << "soFar: " << soFar << '\n';
    best = max(best, soFar);
  }

  return best;
}

int main() {
  vector<int> a = {-3, -2, 1, 0, 8, 7, 1};
  cout << solution(a,3);
  return 0;
}