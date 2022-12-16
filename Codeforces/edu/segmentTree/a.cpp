#include <bits/stdc++.h>
using namespace std;



int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int sum{0};
        int res {1'000'000'000};

        auto fnFixEven = [](int val) {
            int cnt{0};
            while(! (val&1) ) { 
                val /= 2;
                ++cnt;
            }
            return cnt;
        };
        auto fnFixOdd = [](int val) {
            int cnt{0};
            while(val & 1) { 
                val /= 2;
                ++cnt;
            }
            return cnt;
        };
        
        while(n--) {
            int val;
            cin >> val;
            if(val & 1) res = min(res, fnFixOdd(val));
            else res = min(res, fnFixEven(val));
            sum += val;
        }

        if( !(sum & 1) ) cout << "0\n";
        else cout << res << '\n';
    }
    return 0;
}