#include <bits/stdc++.h>
using namespace std;


int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<size_t> a(n);
        size_t res{0};
        size_t minElem{INT_MAX};
        size_t maxElem{0};
        for(auto& v : a) { 
            cin >> v;
            res += v;
            minElem = min(v, minElem);
            maxElem = max(v, maxElem);
        }

        size_t res2 = 0;
        size_t d = maxElem - minElem;
        for(auto& v : a)
        {
            if(v < d) res2 += d;
            else res2 += v;
        }

    }
    return 0;
}