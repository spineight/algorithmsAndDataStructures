#include <bits/stdc++.h>
using namespace std;

//! Complete binary tree
//! To make it complete we resize leafs to the nearest of power of two
struct SegmentTreeSum {

    //! The same idea as for binary heap, by idx of the current element we could calculate idxs of its children
    //! Hence we don't need to have explicit links to children
    //!     for the node with idx : leftChild = 2 * idx + 1; rightChild = 2 * idx + 2
    vector<long long> sum;
    
    // number of leaves, there will be node elements, a node - is sum of 2 nodes / leafes
    size_t sz{1};
    
    void init(int n) {
        while(sz < n) sz *= 2; // make leaves size power of 2


        // total number of elements = leafs(sz) + intern nodes(sz-1)
        // Explanation for intern nodes size = sz - 1
        // start from the top level till the leafs: 1 2 4 8 | 16 |
        // we observe that these are powers of 2, sum(2^n) where n = 0 .. k-1 = 2^k - 1
        sum.assign(2*sz-1,0);
    }
    //! x - is idx of node/leaf in sum array (0..2*sz-1)
    //! lx,rx - left,right boundaries (0 .. sz) for leafs
    void build(const vector<int>& a, int x, int lx, int rx) {
        if(rx-lx==1) {
            // check because we extend the array with  zeros to get number of leafs to the nearest power of two
            if(lx < a.size()) sum[x] = a[lx];
        }
        else {
            const int m = lx + (rx-lx) / 2;
            build(a, 2*x+1, lx,m);
            build(a, 2*x + 2, m, rx);
            // update on the exit from the recursion
            sum[x] = sum[2*x+1] + sum[2*x+2];
        }
    }
    void build(const vector<int>& a) {
        build(a,0,0,sz);
    }
    void set(int idx, int val, int x, int lx, int rx) {
        if(rx-lx==1) {
            sum[x] = val;
        } 
        else {
            const int m = lx + (rx-lx) / 2;
            if(idx < m) set(idx, val, 2*x+1, lx,m);
            else set(idx, val, 2*x+2, m,rx);
            // update on the exit from the recursion
            sum[x] = sum[2*x+1] + sum[2*x+2];
        }
    }
    void set(int idx, int val) {
        set(idx,val,0,0,sz);
    }

    long long getSum(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(r <= lx || rx <= l) return 0;
        //! 2. contains
        if(l <= lx && rx <= r) return sum[x];
        //! 3. overlap
        const int m = lx + (rx-lx)/2;
        const long long left = getSum(l,r,2*x+1,lx,m);
        const long long right = getSum(l,r,2*x+2,m,rx);
        return left+right;
    }

    //! [l,r)
    long long getSum(int l, int r) {
        return getSum(l,r,0,0,sz);
    }
};


int main() {
    int n,m;
    cin >> n >> m;

    SegmentTreeSum sts;
    sts.init(n);
    vector<int> a(n);
    for(auto& v : a) cin >> v;
    sts.build(a);

    while(m--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i,val;
            cin >> i >> val;
            sts.set(i,val);
        } else {
            int l,r;
            cin >> l >> r;
            cout << sts.getSum(l,r) << '\n';
        }
    }
    return 0;
}