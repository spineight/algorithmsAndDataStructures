#include <bits/stdc++.h>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  int n;
  string digits;
  cin >> n;
  cin >> digits;
  if(n < 11) cout << "0\n";
  else {
    int digitsCnt[10];
    for(auto ch : digits) ++digitsCnt[ch-'0'];
    if(digitsCnt[8] == 0) cout << "0\n";
    else {
      // An(k) =
    }
  }
  return 0;
}