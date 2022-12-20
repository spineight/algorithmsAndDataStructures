#include <bits/stdc++.h>
using namespace std;


struct SegmentTreeSum {
    vector<int> sums;
    size_t sz{1};
    
    void init(size_t n) {
        while(sz < n) sz *= 2;
        sums.assign(2*sz - 1, 0);
    }

    void set(int i, int val, int x, int lx, int rx) {
        if(rx-lx == 1) sums[x] = val;
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

    size_t getSum(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(rx <= l || r <= lx) return 0;
        //! 2. contains
        if(l <= lx && rx <= r) return sums[x];
        const int m = lx + (rx-lx) / 2;
        const auto left = getSum(l,r,2*x+1,lx,m);
        const auto right = getSum(l,r,2*x+2,m,rx);
        return left + right;
    }
    size_t getSum(int l, int r) {
        return getSum(l,r,0,0,sz);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> a(n*2);
    for(auto& v : a) cin >> v;
    SegmentTreeSum sts;
    sts.init(2*n);

    unordered_map<int,int> leftBoarderPos;
    vector<int> res(n,0);

    auto fn = [&]() {
        for(int i = 0; i < a.size(); ++i) {
            if(leftBoarderPos.count(a[i]) ) {
                res[a[i]-1] += sts.getSum(leftBoarderPos[a[i]]+1, i);
                sts.set(leftBoarderPos[a[i]],0);
            } 
            else {
                sts.set(i,1);
                leftBoarderPos[a[i]] = i;
            }
        }
    };
    fn();

    reverse(begin(a), end(a));
    leftBoarderPos.clear();
    sts.init(2*n);
    fn();

    for(auto v : res) cout << v << " ";
    cout << '\n';

    return 0;
}