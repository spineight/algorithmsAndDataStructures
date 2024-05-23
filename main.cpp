#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;




int main() {

  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);

  int t;
  cin >> t;
  stack<int> s;
  map<int,int> m;

  while(t--) {
    int e;
    cin >> e;
    if(1== e) {
      int r;
      cin >> r;
      s.push(r);
      ++m[r];
//      std::cout << "check:" << begin(m)->second
    }
    else if(2 == e) {
      --m[s.top()];
      if(m[s.top()] == 0) {
        m.erase(s.top());
      }
      s.pop();
    } else {
      std::cout << begin(m)->first << "\n";
    }
  }
}