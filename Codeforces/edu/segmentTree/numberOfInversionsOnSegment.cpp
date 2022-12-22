#include <bits/stdc++.h>
using namespace std;


static constexpr long long MAX_ELEM{40};


struct Elem {
    long long freq[MAX_ELEM+1];
    Elem() {
        memset(freq,0,sizeof(freq));
    }
    long long inversions{0};
};

Elem neutralElem;

struct SegmentTree {
    vector<Elem> elems;
    long long sz{1};
    void init(long long n) {
        while(sz < n) sz *= 2;

        elems.resize(2*sz-1);
    }

    Elem combine(const Elem& a, const Elem& b) {
        Elem res;
        res.inversions = a.inversions + b.inversions;
        for(int i = 1; i <= MAX_ELEM; ++i) {
            if(b.freq[i]) {
                for(int j = i+1; j <= MAX_ELEM; ++j)
                    res.inversions += b.freq[i] * a.freq[j];
            }
            res.freq[i] = a.freq[i] + b.freq[i];
        }
        return res;
    }

    void build(const vector<int>& a, int x, int lx, int rx) {
        if(rx-lx == 1) {
            if(lx < a.size()) {
                ++elems[x].freq[a[lx]];
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

    void set(int i, int val, int x , int lx, int rx) {
        if(rx-lx==1) {
            Elem e;
            ++e.freq[val];
            elems[x] = e;
        }
        else {
            const int m = lx + (rx-lx)/ 2;
            if(i < m) set(i,val, 2*x+1, lx,m);
            else set(i,val,2*x+2,m,rx);
            elems[x] = combine(elems[2*x+1], elems[2*x+2]);
        }
    }

    void set(int i, int val) {
        set(i,val,0,0,sz);
    }

    Elem getInversionsCnt(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(rx <= l || r <= lx) return neutralElem;
        //! 2. contains
        if(l <= lx && rx <= r) return elems[x];
        //! 3. overlap
        const int m = lx + (rx-lx) / 2;
        const auto left = getInversionsCnt(l,r,2*x+1,lx,m);
        const auto right = getInversionsCnt(l,r,2*x+2,m,rx);
        return combine(left, right);
    }

    long long getInversionsCnt(int l, int r) {
        return getInversionsCnt(l,r,0,0,sz).inversions;
    }
};


int main() {
    long long n,q;
    cin >> n >> q;

    vector<int> a(n);
    for(auto& v : a) cin >> v;

    SegmentTree st;
    st.init(n);
    st.build(a);

    while(q--) {
        int x,y;
        int op;
        cin >> op >> x >> y;

        if(1==op) {
            cout << st.getInversionsCnt(x-1,y) << '\n';
        }
        else {
            st.set(x-1,y);
        }
    }

    return 0;
}