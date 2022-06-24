#include <bits/stdc++.h>
using namespace std;

void RecSubsets(string soFar, string rest) {
  if(rest.empty()) cout << soFar << '\n';
  else {
    // add to subset remove from the rest, recur
    RecSubsets(soFar + rest.front(), rest.substr(1));
    // don't add to subset, remove from the rest, recur
    RecSubsets(soFar, rest.substr(1));
  }
}

void listSubsets(string s) {
  RecSubsets("", s);
}

int main() {
  listSubsets("abc");
  return 0;
}