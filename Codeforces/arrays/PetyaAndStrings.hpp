#include <bits/stdc++.h>

using namespace std;



int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  std::cout.tie(0);

  string w0,w1;
  cin >> w0 >> w1;
  for(auto& ch : w0) ch &= ~(32);
  for(auto& ch : w1) ch &= ~(32);
  if(w0 == w1) cout << 0 << '\n';
  else if(w0 < w1) cout << "-1\n";
  else cout << "1\n";

  return 0;
}