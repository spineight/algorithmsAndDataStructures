#include <bits/stdc++.h>
using namespace std;


struct SegmentTreeKthOne {
    vector<int> sums;
    size_t sz{1};

    void init(size_t n) {
        while(sz < n) sz *= 2;
        sums.assign(2*sz-1,0);
    }
    void build(int x, int lx, int rx) {
        if(rx-lx==1) sums[x] = 1;
        else {
            const int m = lx + (rx-lx) / 2;
            build(2*x+1,lx,m);
            build(2*x+2,m,rx);
            sums[x] = sums[2*x+1] + sums[2*x+2];
        }
    }
    void build() {
        build(0,0,sz);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx == 1) sums[x] = val;
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val, 2*x+1,lx,m);
            else set(i,val, 2*x+2,m,rx);
            sums[x] = sums[2*x+1] + sums[2*x+2];
        }
    }

    void set(int i, int val) {
        set(i,val,0,0,sz);
    }

    size_t getKthOne(int k, int x, int lx, int rx) const{
        if(rx-lx == 1) return lx;
        const int m = lx + (rx-lx) / 2;
        if(sums[2*x+1] <= k) return getKthOne(k - sums[2*x+1], 2*x+2, m,rx);
        return getKthOne(k, 2*x+1,lx,m);
    }
    size_t getKthOne(int k) const{   
        return getKthOne(k,0,0,sz);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    SegmentTreeKthOne stko;
    stko.init(n+1);
    stko.build();

    vector<int> res(n);
    for(int i = n-1; i >= 0; --i) {
        int k = n-a[i];
        auto val = stko.getKthOne(k);
        res[i] = val;
        stko.set(val,0);
        --n;
    }
    for(auto v : res) cout << v << " ";
    cout << '\n';
    return 0;
}