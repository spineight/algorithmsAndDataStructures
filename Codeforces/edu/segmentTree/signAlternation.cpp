#include <bits/stdc++.h>
using namespace std;


struct SegmentTree {
    struct Elem {
        int evenSum{0};
        int oddSum{0};
    };
    vector<Elem> elems;
    size_t sz{1};
    void init(size_t n) {
        while(sz < n) sz *= 2;

        elems.resize(2*sz-1);
    }

    Elem combine(const Elem& a, const Elem& b) {
        Elem res;
        res.evenSum = a.evenSum + b.evenSum;
        res.oddSum = a.oddSum + b.oddSum;
        return res;
    }

    void build(const vector<int>& a, int x, int lx, int rx) {
        if(rx-lx == 1) {
            if(lx < a.size()) {
                if(lx & 1) elems[x].oddSum = a[lx];
                else elems[x].evenSum = a[lx];
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
        if(rx-lx == 1) {
            if(lx & 1) elems[x].oddSum = val;
            else elems[x].evenSum = val;
        }
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val,2*x+1,lx,m);
            else set(i,val,2*x+2,m,rx);
            elems[x] = combine(elems[2*x+1], elems[2*x+2]);
        }
    }
    void set(int i, int val) {
        set(i-1,val,0,0,sz); // zero indexed array
    }
    int getAlternatingSum(int l, int r, int x, int lx, int rx) {
        int sign = -1;
        if (l & 1) sign = 1;
        //! 1. no overlap
        if(rx <= l || r <= lx) return 0;
        //! 2. contains
        if(l <= lx && rx <= r) {
            return elems[x].oddSum * sign - elems[x].evenSum * sign;
        }
        //! 3. overlap
        const int m = lx + (rx-lx) / 2;
        const auto left = getAlternatingSum(l,r,2*x+1,lx,m);
        const auto right = getAlternatingSum(l,r,2*x+2,m,rx);
        return left + right;
    }
    int getAlternatingSum(int l, int r) {
        return getAlternatingSum(l-1,r, 0, 0, sz); // zero indexed array
    }
};


int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto& v : a) cin >> v;

    SegmentTree st;
    st.init(n);
    st.build(a);

    int m;
    cin >> m;
    while(m--) {
        int op;
        cin >> op;
        if(op == 0) {
            int i,j;
            cin >> i >> j;
            st.set(i,j);
        }
        else {
            int l,r;
            cin >> l >> r;
            cout << st.getAlternatingSum(l,r) << '\n';
        }
    }
    return 0;
}