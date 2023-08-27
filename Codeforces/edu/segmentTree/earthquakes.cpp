#include <bits/stdc++.h>

using namespace std;


struct ElemT {
    map<size_t, size_t> m; 
    int val{0};
};

ElemT neutralElem;



struct SegmentTree {
    vector<ElemT> elems;
    size_t sz{1};
    void init(size_t n) {
        while(sz < n) sz *= 2;
        elems.resize(2*sz-1);
    }

    static ElemT combine(const ElemT& a, const ElemT& b) {
        ElemT res;
        for(const auto& [k,v] : a.m) {
            res.m[k] += v;
        }
        for(const auto& [k,v] : b.m) {
            res.m[k] += v;
        }
        return res;
    }

    void set(int i, int v, int x, int lx, int rx) {
        if(rx-lx==1) { 
            const auto prevVal = elems[x].val;
            --elems[x].m[prevVal];
            ++elems[x].m[v];
            elems[x].val = v;
        }
        else {
            const int m = lx + (rx-lx) /2;
            if(i < m) set(i,v,2*x+1,lx,m);
            else set(i,v,2*x+2,m,rx);
            elems[x] = combine(elems[2*x+1], elems[2*x+2]);
        }
    }

    void set(int i, int v) {
        set(i,v,0,0,sz);
    }

    ElemT get(int l, int r, int x, int lx ,int rx) {
        //! 1. no overlap
        if(rx <= l || r <= lx) return neutralElem;
        //! 2. contains
        if(l <= lx && rx <= r) return elems[x];
        //! 3. overlap
        const int m = lx + (rx-lx) / 2;
        const auto left = get(l,r,2*x+1,lx,m);
        const auto right = get(l,r,2*x+2,m,rx);
        return combine()
    }

    size_t getAboveValCnt(int l, int r, int val) {

    }
};

int main() {
    int n,m;
    cin >> n >> m;

    while(m--) {
        int op;
        cin >> op;
        if(1== op) {
            int i, h;
            cin >> i >> h;
        }
        else {
            int l,r,p;
            cin >> l >> r >> p;
        }
    }
    return 0;
}