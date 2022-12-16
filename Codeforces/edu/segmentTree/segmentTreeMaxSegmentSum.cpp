#include <bits/stdc++.h>
using namespace std;

struct SegmentTreeMaxSegmentSum {
    struct Node {
        long long pref{0};
        long long suffix{0};
        long long maxSum{0};
        long long sum{0};
    };
    vector<Node> maxSegSum;
    size_t sz{1};

    void init(int n) {
        while(sz < n) sz *= 2;
        maxSegSum.assign(2*sz-1, Node());
    }

    Node fn(const Node& a, const Node& b) {
        Node res;
        res.pref = max(a.pref, a.sum + b.pref);
        res.suffix = max(b.suffix, a.suffix + b.sum);
        res.maxSum = max({ a.maxSum, b.maxSum, a.suffix + b.pref, 0ll});
        res.sum = a.sum + b.sum;
        return res;
    }

    void build(const vector<long long>& a, int x, int lx, int rx) {
        if(rx-lx == 1) {
            if(lx < a.size()) {
                maxSegSum[x] = {a[lx], a[lx], a[lx] > 0 ? a[lx] : 0, a[lx]};
            }
        } 
        else {
            const int m = lx + (rx-lx) / 2;
            build(a,2*x+1,lx,m);
            build(a,2*x+2,m,rx);
            maxSegSum[x] = fn(maxSegSum[2*x+1], maxSegSum[2*x+2]);
        }
        
    }

    void build(const vector<long long>& a) {
        build(a, 0, 0, sz);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx == 1) {
            maxSegSum[x] = {val,val, val > 0 ? val : 0, val};
        }
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val, 2*x+1, lx,m);
            else set(i,val, 2*x+2, m,rx);
            maxSegSum[x] = fn(maxSegSum[2*x+1], maxSegSum[2*x+2]);
        }
    }
    void set(int i, int val) {
        set(i,val, 0, 0, sz);
    }

    Node get(int l, int r, int x , int lx, int rx) {
        //! 1. no overlap
        if (rx <= l || r <= lx) return {0,0,0,0};
        //! 2. contains
        if(l <=lx && rx <= r) return maxSegSum[x];
        //! 3. overlap
        const int m = lx + (rx-lx) / 2;
        const auto left = get(l,r,2*x+1, lx,m);
        const auto right = get(l,r,2*x+2, m,rx);
        const auto res = fn(left, right);
        return res;
    }

    long long get(int l, int r) {
        return get(l,r, 0,0,sz).maxSum;
    }
};

ostream& operator<<(ostream& out, const SegmentTreeMaxSegmentSum::Node& n) {
    out << "pref: " << n .pref << ", suffix: " << n.suffix << ", maxSum: " << n.maxSum << ", sum: " << n.sum << '\n';
    return out;
}

int main() {
    int n,m;
    cin >> n >> m;
    vector<long long> a(n);
    for(auto& v : a) cin >> v;
    
    SegmentTreeMaxSegmentSum stmss;
    stmss.init(n);
    stmss.build(a);
    // for(const auto& v : stmss.maxSegSum) cout << v << '\n';

    cout << stmss.get(0,n) << '\n';

    while(m--) {
        int i,v;
        cin >> i >> v;
        stmss.set(i,v);
        cout << stmss.get(0,n) << '\n';
    }
    return 0;
}