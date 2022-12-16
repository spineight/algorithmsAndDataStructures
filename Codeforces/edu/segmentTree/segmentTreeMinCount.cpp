#include<bits/stdc++.h>
using namespace std;


struct SegmentTreeMinCount {
    static const int INF;
    using ElemT = pair<int,int>;
    vector<ElemT> minCnt;
    size_t sz{1};

    void init(size_t n) {
        while(sz < n) sz *= 2;

        minCnt.assign(2*sz-1, {INF,0});
    }
    static ElemT minCntFn(const ElemT& a, const ElemT& b) {
        if(a.first < b.first) return a;
        if(a.first > b.first) return b;
        return {a.first, a.second + b.second};
    }

    void build(const vector<int>& a, int x, int lx, int rx) {
        if(rx-lx == 1) {
            if(lx < a.size()) minCnt[x] = {a[lx],1};
        } 
        else {
            const int m = lx + (rx-lx)/2;
            build(a,2*x+1, lx,m);
            build(a,2*x+2,m,rx);
            minCnt[x] = minCntFn(minCnt[2*x+1], minCnt[2*x+2]);
        }
    }
    void build(const vector<int>& a) {
        build(a, 0,0,sz);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx==1) {
            minCnt[x] = {val,1};
        }
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val, 2*x+1,lx,m);
            else set(i,val, 2*x + 2,m,rx);
            minCnt[x] = minCntFn(minCnt[2*x+1], minCnt[2*x+2]);
        }
    }

    void set(int i, int val) {
        set(i,val,0,0,sz);
    }

    ElemT getMinCnt(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(rx <= l || r <= lx) return {INF,0};
        //! 2. contains
        if(l <=lx && rx <= r) return minCnt[x];
        //! 3. overlap
        const int m = lx + (rx-lx) / 2;
        const auto left = getMinCnt(l,r,2*x+1,lx,m);
        const auto right = getMinCnt(l,r,2*x+2,m,rx);
        return minCntFn(left, right);
    }

    ElemT getMinCnt(int l, int r) {
        return getMinCnt(l,r,0,0,sz);
    }


};

const int SegmentTreeMinCount::INF = numeric_limits<int>::max();


int main() {
    ios::sync_with_stdio(false);
    int n,m;
    cin >> n >> m;

    SegmentTreeMinCount stmc;
    stmc.init(n);
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    stmc.build(a);

    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i,val;
            cin >> i >> val;
            stmc.set(i,val);
        } else {
            int l,r;
            cin >> l >> r;
            const auto res = stmc.getMinCnt(l,r);
            cout << res.first << " " << res.second << '\n';
        }
    }
    return 0;
}