#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace a {


  void solve() {
    int t;
    cin >> t;
    while(t--) {
      int n;
      cin >> n;
      if((n % 2) == 0) cout << "0\n";
      else {
        const auto str = to_string(n);
        bool isEvenDigit{false};
        for(auto ch : str) if ((ch-'0') % 2 ==0 ) {
          isEvenDigit = true;
          break;
        }
        if(isEvenDigit) cout << "2\n";
        else cout << "0\n";
      }
    }
  }
}