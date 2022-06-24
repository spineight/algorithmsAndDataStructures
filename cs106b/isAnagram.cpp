#include <bits/stdc++.h>
using namespace std;


//! turning permute -> anagram finder
//void permute(string soFar, string rest) {
//  if(rest.empty()) cout << soFar << '\n';
//  else {
//    for(int i = 0; i < rest.size(); ++i) {
//      auto next = soFar + rest[i];
//      auto remain = rest.substr(0, i) + rest.substr(i+1);
//      permute(next, remain);
//    }
//  }
//}

bool isAnagram(string soFar, string rest, const set<string>& dict) {
  if(rest.empty()) {
    return dict.contains(soFar);
  }
  else {
    for(int i = 0; i < rest.size(); ++i) {
      if(isAnagram(soFar + rest[i], rest.substr(0, i) + rest.substr(i+1), dict))
        return true;
    }
  }
  return false;
}

bool isAnagram(string s) {
  filesystem::path path{DataDir};
  path += "/words.txt";
  ifstream in(path);
  istream_iterator<string> beginIt(in);
  istream_iterator<string> endIt;
  set<string> dict;
  copy(beginIt, endIt, inserter(dict, begin(dict)));
  return isAnagram("", s, dict);
}

int main() {
  cout << isAnagram("boat") << '\n';
  cout << isAnagram("bbbb") << '\n';
  return 0;
}