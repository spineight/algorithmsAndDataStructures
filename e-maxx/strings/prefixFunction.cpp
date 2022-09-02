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




int main() {
  auto res = prefixFunction("abcabcd"); // 0 0 0 1 2 3 0
  for(auto r : res) cout << r << ' ';
  cout << '\n';

  auto pos = find("aba", "abacabadabacaba");
  for(auto p : pos) cout << p << ' '; // 0 4 8 12
  cout << '\n';
  return 0;
}