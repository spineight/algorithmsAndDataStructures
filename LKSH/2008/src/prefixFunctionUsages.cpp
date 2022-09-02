#include <bits/stdc++.h>
using namespace std;

//! Префикс функция - длина наибольшего собственного суффикса подстроки который одновременно является ее префиксом.
//! Собственный суфикс - не совпадающий со всей строкой
vector<int> prefixFunction(const std::string& s) {
  vector<int> res(s.size(),0);
  for(int i = 1; i < s.size(); ++i) {
    int k = res[i-1];
    while(k > 0 && s[k] != s[i])
      k = res[k-1];
    if(s[k] == s[i]) res[i] = k + 1;
  }
  return res;
}

//! find all occurrences of s(string) in t(text)
//! m = s.size(); n = t.size()
//! time: O(m + n), space O(m + n)
vector<int> find(const string& s, const string& t) {
  //! we use `$` as a symbol that is not in text, this allows us to limit max match to s
  string aux = s + '$';
  aux += t;
  vector<int> positions;

  vector<int> prefixFunction(aux.size(),0);
  for(int i = s.size()+1; i < aux.size(); ++i) {
    int k = prefixFunction[ i-1 ];
    while(k > 0 && aux[k] != aux[i])
      k = prefixFunction[k-1];
    if(aux[k] == aux[i]) prefixFunction[i] = k+1;
    // 012 3 456
    // sss|$|  i
    // prefixFunction[i] = 3
    // pos = i - prefixFunction[i] + 1 - s.size() - 1 => (as s.size() == prefixFunction[i]) = i - 2 * prefixFunction[i]
    if(prefixFunction[i] == s.length()) positions.push_back(i-s.size()*2);
  }
  return positions;
}

//! returns true if one string can be obtained from the other by circular shift
//! abcd, cdab -> true
//! abcd, dabc -> true
//! aaba, aaab -> true
//! abab, aabb -> false
//!
//! Идея:
//! a b b
//! abcd cdab cdab
//!
bool isShift(const string& a, const string& b) {
  if(a.size() != b.size()) return false;

  auto abb = a + b + b;
  vector<int> prefixFn(abb.size(),0);
  for(int i = 1; i < abb.size(); ++i) {
    int k = prefixFn[i-1];
    while(k > 0 && abb[k] != abb[i])
      k = prefixFn[k-1];
    if(abb[k] == abb[i]) {
      prefixFn[i] = k+1;
      if(prefixFn[i] == a.size()) return true;
    }
  }
  return false;
}



int main() {
  auto res = prefixFunction("abcabcd"); // 0 0 0 1 2 3 0
  for(auto r : res) cout << r << ' ';
  cout << '\n';

  auto pos = find("aba", "abacabadabacaba");
  for(auto p : pos) cout << p << ' '; // 0 4 8 12
  cout << '\n';

  cout << isShift("abcd", "cdab") << '\n'; // 1
  cout << isShift("abcd", "dabc") << '\n'; // 1
  cout << isShift("aaba", "aaab") << '\n'; // 1
  cout << isShift("abab", "aabb") << '\n'; // 0
  return 0;
}