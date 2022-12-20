#include <bits/stdc++.h>
using namespace std;

struct SegmentTreeFirstAbove {
    vector<long long> maxElement;
    static constexpr long long NEG_INF = numeric_limits<long long>::min();
    size_t sz{1};

    void init(int n) {
        while(sz < n) sz *= 2;

        maxElement.assign(2*sz-1, NEG_INF);
    }

    void build(const vector<long long>& a, int x, int lx, int rx) {
        if(rx-lx == 1) {
            if(lx < a.size()) maxElement[x] = a[lx];
        }
        else {
            const int m = lx + (rx-lx) / 2;
            build(a, 2*x+1,lx,m);
            build(a,2*x+2,m,rx);
            maxElement[x] = max(maxElement[2*x+1], maxElement[2*x+2]);
        }
    }
    void build(const vector<long long>& a) {
        build(a,0,0,sz);
    }
    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx == 1) {
            maxElement[x] = val;
        } else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val, 2*x+1, lx,m);
            else set(i,val,2*x+2,m,rx);
            maxElement[x] = max(maxElement[2*x+1], maxElement[2*x+2]);
        }
    }
    void set(int i, int val) {
        set(i,val,0,0,sz);
    }

    optional<int> getIdxFirstAbove(int val, int x, int lx, int rx) {
        // cout << val << "," << x << "," << lx << "," << rx << '\n';
        if(maxElement[x] < val) return nullopt;
        
        if(rx-lx == 1) return lx;

        const int m = lx + (rx-lx) / 2;
        optional<int> res = getIdxFirstAbove(val, 2*x+1, lx,m);
        if(res) return res;

        return  getIdxFirstAbove(val, 2*x+2, m, rx);
    }

    int getIdxFirstAbove(int val) {
        auto res = getIdxFirstAbove(val,0,0,sz);
        if(!res) return -1;
        return *res;
    }

    optional<int> getIdxFirstAbove(int val, int l, int x, int lx, int rx) {
        if(maxElement[x] < val || rx <= l) return nullopt;

        if(rx-lx==1) return lx;
        const int m = lx + (rx-lx) / 2;
        auto res = getIdxFirstAbove(val,l,2*x+1,lx,m);
        if(res) return res;
        return getIdxFirstAbove(val,l, 2*x+2, m, rx);
    }

    int getIdxFirstAbove(int val, int l) {
        auto res = getIdxFirstAbove(val,l,0,0,sz);
        if(res) return *res;
        return -1;
    }
};


int main() {
    int n,m;
    cin >> n >> m;
    vector<long long> a(n);
    for(auto& v : a) cin >> v;

    SegmentTreeFirstAbove stfa;
    stfa.init(n);
    stfa.build(a);

    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i,v;
            cin >> i >> v;
            stfa.set(i,v);
        } 
        else {
            int x,l;
            cin >> x >> l;
            cout << stfa.getIdxFirstAbove(x, l) << '\n';
        }
    }
    return 0;
}