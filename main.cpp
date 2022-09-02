#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//struct Solve {
//  const string chars{"klmny"};
//  string soFar;
//  int solve(int i) {
//    int res{0};
//    if(i > 7) {
//      auto cnt = count_if(begin(soFar), end(soFar), [](auto ch) {return ch == 'y';});
//      if(cnt > 1) return 0;
//      if(soFar.back() == 'l') return 0;
//      return 1;
//    }
//
//    for(auto ch : chars) {
//      soFar.push_back(ch);
//      res += solve(i+1);
//      soFar.pop_back();
//    }
//
//    return res;
//  }
//};

//int f(int n) {
//  if(n == 1) return 1;
//  if(n & 1) return n + f(n-2);
//  else return n * f(n-2);
//}


//pair<int,int> f(int a) {
//  int R,L,M;
//  L = 0;
//  R = 15;
//  while(a >= R) {
//    L = L + 1;
//    a = a - R;
//  }
//  M = a;
//  if(M < L) {
//    M = L;
//    L = a;
//  }
////  cout << L << '\n' << M << '\n';
//  return {L,M};
//}


struct Solve {
  vector<int> trajectory;
  int solve(int v) {
    int cnt{0};
    if(v > 34) return 0;
    if(v == 34) {
      for(auto v : trajectory) cout << v << ",";
      cout << '\n';
      if(find(begin(trajectory), end(trajectory), 21) == end(trajectory)
      && find(begin(trajectory), end(trajectory), 16) != end(trajectory))
        return 1;
      return 0;
    }

    trajectory.push_back(v+1);
    cnt += solve(v+1);
    trajectory.pop_back();
    trajectory.push_back(v*2);
    cnt += solve(v*2);
    trajectory.pop_back();
    return cnt;
  }
};

void solve(string& s) {
  bool ok = true;
  while(ok) {
    ok = false;
    while (1) {
      auto pos = s.find("111");
      if (pos == string::npos) break;
      s.replace(pos, 3, "7");
      ok = true;
    }
    while (1) {
      auto pos = s.find("777");
      if (pos == string::npos) break;
      s.replace(pos, 3, "17");
      ok = true;
    }
  }
}


int main() {
//  for(int a = 1000'000; a >= 0; --a) {
//    if( (a % 100'000) == 0 ) cout << "A:" << a << '\n';
//    const auto [L,M] = f(a);
//    if( L == 6 && M == 10) {
//      cout << a << '\n';
//      break;
//    }
//  }
  string s(53, '7');
  cout << s << '\n';
  solve(s);
  cout << s << '\n';

  return 0;
}
