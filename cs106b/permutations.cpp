#include <bits/stdc++.h>
using namespace std;

//! want to enumerate all rearrangements
//! ABCD permutes to DCBA, CABD etc

//! this is a choice pattern

void permute(string soFar, string rest) {
  if(rest.empty()) cout << soFar << '\n';
  else {
    for(int i = 0; i < rest.size(); ++i) {
      auto next = soFar + rest[i];
      auto remain = rest.substr(0, i) + rest.substr(i+1);
      permute(next, remain);
    }
  }
}

void permute(string s) {
  permute("", s);
}

int main() {
  permute("abc");
  return 0;
}