#include <bits/stdc++.h>

using namespace std;

//! There are only '1' and '0' elements
//! Need to find k-th '1'
//! We reuse SegmentTreeSum for this + implement operation getKthOne based on the sum information for each node
struct SegmentTreeKthOne {
    vector<int> sums;
    size_t sz{1};

    void init(int n) {
        while(sz < n) sz *= 2;

        sums.assign(2*sz-1, 0);
    }

    void build(const vector<int>& a, int x, int lx, int rx) {
        if(rx-lx==1) {
            if(lx < a.size()) sums[x] = a[lx];
        } 
        else {
            const int m = lx + (rx-lx) / 2;
            build(a, 2*x+1, lx,m);
            build(a, 2*x+2, m,rx);
            sums[x] = sums[2*x+1] + sums[2*x+2];
        }
    }
    void build(const vector<int>& a) {
        build(a,0,0,sz);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx==1) { 
            sums[x] ^= val;
        }
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val, 2*x+1, lx, m);
            else set(i,val, 2*x+2, m, rx);
            sums[x] = sums[2*x+1] + sums[2*x+2];
        }
    }

    void set(int i, int val) {
        set(i,val, 0,0,sz);
    }
    int getKthOne(int k, int x, int lx, int rx) const {
        if(rx-lx == 1) return lx;
        const int m = lx + (rx-lx) / 2;
        const int leftCnt = sums[2*x+1];
        if(k >= leftCnt) return getKthOne(k - leftCnt, 2*x+2, m, rx);
        return getKthOne(k, 2*x+1, lx, m);
    }

    int getKthOne(int k) const {
        return getKthOne(k, 0,0,sz);
    }
};

int main() {
    int n,m;
    cin >> n >> m;

    vector<int> a(n);
    for(auto& v : a) cin >> v;

    SegmentTreeKthOne stko;
    stko.init(n);
    stko.build(a);

    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i;
            cin >> i;
            stko.set(i,1);
        } else {
            int k;
            cin >> k;
            cout << stko.getKthOne(k) << '\n';
        }
    }

    return 0;
}