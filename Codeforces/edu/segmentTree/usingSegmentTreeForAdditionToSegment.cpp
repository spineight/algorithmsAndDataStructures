#include <bits/stdc++.h>
using namespace std;


struct SegmentTreeSum {
    vector<long long> sums;
    size_t sz{1};

    void init(size_t n) {
        while(sz < n) sz *= 2;
        sums.resize(2*sz-1);
    }

    void add(int i, int val, int x, int lx, int rx) {
        if(rx-lx == 1) {
            sums[x] += val;
        }
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) add(i, val, 2*x+1,lx,m);
            else add(i, val, 2*x+2, m, rx);
            sums[x] = sums[2*x+1] + sums[2*x+2];
        }
    }
    void add(int i, int val) {
        add(i,val,0,0,sz);
    }

    long long getSum(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(rx <= l || r <= lx) return 0;
        //! 2. contains
        if(l <= lx && rx <= r) return sums[x];
        //! 3. overlap
        const int m = lx + (rx-lx) / 2;
        const auto left = getSum(l,r,2*x+1,lx,m);
        const auto right = getSum(l,r,2*x+2, m,rx);
        return left + right;
    }
    long long getSum(int l, int r) {
        return getSum(l,r,0,0,sz);
    }

    void add(int l, int r, int val) {
        add(l, val);
        add(r,-val);
    }
    long long get(int i) {
        return getSum(0,i+1);
    }
};

int main() {
    int n,m;
    cin >> n >> m;
    SegmentTreeSum sts;
    sts.init(n+1);

    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int l,r,v;
            cin >> l >> r >> v;
            sts.add(l,r,v);
        } 
        else {
            int i;
            cin >> i;
            cout << sts.get(i) << '\n';
        }
    }
    return 0;
}