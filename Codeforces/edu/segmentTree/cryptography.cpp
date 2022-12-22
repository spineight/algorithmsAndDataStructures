#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    int a[4];
    Matrix(const vector<int>& v) {
        memcpy(a,v.data(), v.size() * sizeof(int));
    }
    Matrix(const Matrix& other) {
        memcpy(a,other.a, sizeof(a));
    }
    Matrix() {
        memset(a,0,sizeof(a));
    }
    Matrix& operator=(const Matrix& other) {
        memcpy(a,other.a, sizeof(a));
        return *this;
    }

    int operator[](int i) const {
        return a[i];
    }
    int& operator[](int i) {
        return a[i];
    }
};

//! Neutral element
Matrix identityMatrix ({1,0,0,1});

ostream& operator<<(ostream& out, const Matrix& m) {
    out << m[0] << " " << m[1] << '\n';
    out << m[2] << " " << m[3] << '\n';
    return out;
}

istream& operator>>(istream& in, Matrix& m) {
    in >> m[0] >> m[1] >> m[2] >> m[3];
    return in;
}

struct SegmentTree {
    vector<Matrix> elems;
    size_t sz{1};
    int r_;
    void init(size_t n, int r) {
        while(sz < n) sz *= 2;

        elems.assign(2*sz-1, identityMatrix);
        r_ = r;
    }

    static Matrix combine(const Matrix& a, const Matrix& b, int r) {
        Matrix res;
        res[0] = (a[0]*b[0] % r  + a[1] * b[2] % r)%r;
        res[1] = (a[0]*b[1] % r + a[1] * b[3] % r)%r;
        res[2] = (a[2]*b[0] % r + a[3] * b[2] % r)%r;
        res[3] = (a[2]* b[1] % r + a[3] * b[3] % r)%r;
        return res;
    }

    void build(const vector<Matrix>& a, int x, int lx, int rx) {
        if(rx-lx == 1) {
            if(lx < a.size()) elems[x] = a[lx];
        }
        else {
            const int m = lx + (rx-lx) / 2;
            build(a, 2*x+1, lx,m);
            build(a,2*x+2,m,rx);
            elems[x] = combine(elems[2*x+1], elems[2*x+2], r_);
        }
    }
    void build(const vector<Matrix>& a) {
        build(a, 0, 0, sz);
    }

    Matrix get(int l, int r, int x, int lx, int rx) {
        //! 1. no overlap
        if(rx <= l || r <= lx) return identityMatrix; // return neutral element
        //! 2. contains
        if(l <= lx && rx <= r) return elems[x];
        //! 3. overlap
        const int m = lx + (rx-lx)/ 2;
        const auto left = get(l,r,2*x+1,lx,m);
        const auto right = get(l,r,2*x+2,m,rx);
        return combine(left, right,r_);
    }
    Matrix get(int l, int r) {
        return get(l,r,0,0,sz);
    }
};


int main() {
    ios::sync_with_stdio(false);

    
    int r,n,m;
    cin >> r >> n >> m;

    vector<Matrix> a(n);
    for(auto& v : a) { 
        cin >> v;
    }

    // Matrix b ({2,1,1,2});
    // cout << SegmentTree::combine(b,identityMatrix,10) << '\n';

    SegmentTree st;
    st.init(n,r);
    st.build(a);

    while(m--) {
        int l,r;
        cin >> l >> r;
        cout << st.get(l-1,r) << '\n';
    }
    return 0;
}