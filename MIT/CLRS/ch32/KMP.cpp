#include <bits/stdc++.h>
using namespace std;

vector<size_t> makePrefixFunction(const string& p) {
    vector<size_t> pi(p.size()+1,0); // pi[q] = for prefix of p length q (Pq) = length of prefix of Pq which is also a suffix of Pq
    size_t k{0}; // n of matched characters
    for(int q = 2; q <= p.size(); ++q) { // q - prefix length (Pq)
        while(k > 0 && p[k] != p[q-1]) k = pi[k-1];

        if(p[k] == p[q-1]) ++k;
        pi[q] = k;
    }
    return pi;
}

vector<size_t> KMP(const string& t, const string& p) {
    const int n = t.size();
    const int m = p.size();
    auto pi = makePrefixFunction(p);
    vector<size_t> matchedPos;
    int matchedCnt{0};

    for(int i = 0; i < n; ++i) {
        while(matchedCnt > 0 && p[matchedCnt] != t[i])
            matchedCnt = pi[matchedCnt];
        if(p[matchedCnt] == t[i]) ++matchedCnt;
        if(matchedCnt == m) {
            matchedPos.push_back(i+1-m);
            matchedCnt = pi[matchedCnt];
        }
    }
    return matchedPos;
}

int main() {
    auto res = KMP("aaaaaaa", "aaa");
    for(auto r : res) cout << r << " ";
    cout << '\n';
    return 0;
}