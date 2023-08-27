#include <bits/stdc++.h>
using namespace std;

static constexpr long long MAX_ELEM{40};

struct ElemT {
    bitset<MAX_ELEM+1> bs;
    int val{0};
};

ElemT neutralElement;

struct SegmentTree {
    
    vector<ElemT> elems;
    size_t sz{1};

    void init(size_t n) {
        while(sz < n) sz *= 2;
        elems.resize(2*sz-1);
    }

    ElemT combine(const ElemT& a, const ElemT& b) {
        ElemT res;
        res.bs |= a.bs;
        res.bs |= b.bs;
        return res;
    }

    void build(const vector<int>& a, int x, int lx, int rx) {
        if(rx-lx==1) {
            if(lx < a.size()) {
                elems[x].bs.set(a[lx]);
                elems[x].val = a[lx];
            }
        }
        else {
            const int m = lx + (rx-lx) / 2;
            build(a,2*x+1,lx,m);
            build(a,2*x+2,m,rx);
            elems[x] = combine(elems[2*x+1], elems[2*x+2]);
        }
    }

    void build(const vector<int>& a) {
        build(a,0,0,sz);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx==1) {
            elems[x].bs.reset(elems[x].val);
            elems[x].bs.set(val);
            elems[x].val = val;
        }
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val,2*x+1,lx,m);
            else set(i,val, 2*x+ 2, m ,rx);
            elems[x] = combine(elems[2*x+1], elems[2*x+2]);
        }
    }

    void set(int i, int val) {
        set(i, val, 0 ,0, sz);
    }

    ElemT getDifferentElementsCnt(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(rx <= l || r <= lx) return neutralElement;
        //! 2. contains
        if(l <= lx && rx <= r) return elems[x];
        //! 3. overlap
        const int m= lx + (rx-lx)/ 2;
        const auto left = getDifferentElementsCnt(l,r,2*x+1,lx,m);
        const auto right = getDifferentElementsCnt(l,r,2*x+2,m,rx);
        return combine(left, right);
    }

    size_t getDifferentElementsCnt(int l, int r) {
        return getDifferentElementsCnt(l,r,0,0,sz).bs.count();
    }
};

int main() {
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    SegmentTree st;
    st.init(n);
    st.build(a);

    while(q--) {
        int op,x,y;
        cin >> op >> x >> y;
        if(1==op) {
            // n of different elements [x,y]
            cout << st.getDifferentElementsCnt(x-1,y) << '\n';
        }
        else {
            // set(x-1, y)
            st.set(x-1,y);
        }
    }

    return 0;
}