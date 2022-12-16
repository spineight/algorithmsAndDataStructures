#include <bits/stdc++.h>
using namespace std;


struct SegmentTreeMin {
    size_t sz{1};
    vector<long long> min_;
    //! https://stackoverflow.com/questions/3531060/how-to-initialize-a-static-const-member-in-c
    static const long long  INF;

    void init(int n) {
        while(sz < n) sz *= 2;
        
        min_.assign(2*sz-1, INF);
    }

    void build(const vector<int>& a, int x, int lx, int rx) {
        if(rx-lx == 1) {
            if(lx < a.size()) min_[x] = a[lx];
        }
        else {
            const int m = lx + (rx-lx) / 2;
            build(a, 2*x+1, lx,m);
            build(a, 2*x + 2, m,rx);
            min_[x] = min(min_[2*x+1], min_[2*x+2] );
        }
    }
    void build(const vector<int>& a) {
        build(a,0,0,sz);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx == 1) {
            min_[x] = val;
        }
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val,2*x+1,lx,m);
            else set(i,val, 2*x+2, m,rx);
            min_[x] = min(min_[2*x+1], min_[2*x+2]);
        }
    }
    void set(int i, int val) {
        set(i, val, 0, 0, sz);
    }
    long long getMin(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(r <= lx || rx <= l) return INF;
        //! 2. contains
        if(l <= lx && rx <= r) return min_[x];
        //! 3. overlap
        const int m = lx + (rx-lx) / 2;
        const auto left = getMin(l,r,2*x+1, lx, m);
        const auto right = getMin(l,r,2*x+2,m,rx);
        return min(left, right);
    }

    long long getMin(int l, int r) {
        return getMin(l,r,0,0,sz);
    }
};

const long long SegmentTreeMin::INF = numeric_limits<long long>::max();


int main() {
    int n,m;
    cin >> n >> m;

    SegmentTreeMin stm;
    stm.init(n);
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    stm.build(a);

    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i,val;
            cin >> i >> val;
            stm.set(i,val);
        } else {
            int l,r;
            cin >> l >> r;
            cout << stm.getMin(l,r) << '\n';
        }
    }
    return 0;
}