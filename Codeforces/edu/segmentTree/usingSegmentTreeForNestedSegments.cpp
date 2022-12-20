#include <bits/stdc++.h>
using namespace std;



struct SegmentTreeSum {
    vector<int> sums;
    size_t sz{1};
    void init(size_t n) {
        while(sz < n) sz *= 2;

        sums.resize(2*sz-1);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx==1) sums[x] = val;
        else {
            const int m = lx + (rx-lx) / 2;
            if(i < m) set(i,val,2*x+1,lx,m);
            else set(i,val,2*x+2,m,rx);
            sums[x] = sums[2*x+1] + sums[2*x+2];
        }
    }

    void set(int i, int val) {
        set(i,val,0,0,sz);
    }

    int getSum(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(rx <= l || r <= lx) return 0;
        //! 2. contains (nested)
        if(l <= lx && rx <= r) return sums[x];
        //! 3. overlap
        const int m = lx + (rx-lx) / 2;
        const auto left = getSum(l,r,2*x+1, lx,m);
        const auto right = getSum(l,r,2*x+2, m,rx);
        return left + right;
    }
    int getSum(int l, int r) {
        return getSum(l,r,0,0,sz);
    }
};

int main() {
    int n;
    cin >> n;
    
    unordered_map<int,int> leftBorderPos;
    SegmentTreeSum sts;
    sts.init(n*2);

    vector<int> res(n,0);

    for(int i = 0; i < n * 2; ++i) { 
        int val;
        cin >> val;
        if(leftBorderPos.count(val)) { // v -is a right border
            res[val-1] = sts.getSum(leftBorderPos[val], i);
            sts.set(leftBorderPos[val],1);
        }
        else {
            leftBorderPos[val] = i;
        }
    }
    for(auto v : res) cout << v << " ";
    cout << '\n';

    return 0;
}