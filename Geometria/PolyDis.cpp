#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct pt {
    ll x, y;
    pt(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
    pt operator+ (const pt &o) const { return pt(x + o.x, y + o.y); }
    pt operator- (const pt &o) const { return pt(x - o.x, y - o.y); }
    pt operator* (const double &d) const { return pt(d * x, d * y); }
    ll dot(const pt &o) { return x * o.x + y * o.y; }
    ll cross(const pt &o) const { return x * o.y - y * o.x; }
    ll cross(const pt &A, const pt &B) const { return (A - *this).cross(B - *this); }
    double norm() { return hypot(x, y); }
    int quad() const {
        if(x >= 0) {
            if(y >= 0) return 1;
            return 4;
        }
        if(y >= 0) return 2;
        return 3;
    }
    bool operator< (const pt &o) const {
        if(quad() != o.quad()) return quad() < o.quad();
        return cross(o) > 0;
    }
    bool operator== (const pt &o) const { return fabs(x - o.x) + fabs(y - o.y) < 1e-9; }
};

ostream& operator<< (ostream& out, pt p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

typedef vector<pt> poly;

poly mink_add(poly A, poly B) {
    int i1 = 0, i2 = 0, n = A.size(), m = B.size();
    for(int i = 1; i < n; i++)
        if(A[i].y < A[i1].y || (A[i].y == A[i1].y && A[i].x < A[i1].x)) i1 = i;
    rotate(A.begin(), A.begin() + i1, A.end());
    for(int i = 1; i < m; i++)
        if(B[i].y < B[i1].y || (B[i].y == B[i1].y && B[i].x < B[i1].x)) i2 = i;
    rotate(B.begin(), B.begin() + i2, B.end());
    vector<pt> edgA, edgB;
    for(int i = 0; i < n; i++)
        edgA.push_back(A[(i + 1) % n] - A[i]);
    for(int i = 0; i < m; i++)
        edgB.push_back(B[(i + 1) % m] - B[i]);
    poly combined;
    merge(edgA.begin(), edgA.end(), edgB.begin(), edgB.end(), back_inserter(combined));
    poly res({A[0] + B[0]});
    for(int i = 0; i < combined.size() - 1; i++)
        res.push_back(res.back() + combined[i]);
    return res;
}

double dis(pt X, pt A, pt B) {
    if(A == B) return (X - A).norm();
    pt v = B - A;
    double lam = (double)(X - A).dot(v)/v.dot(v);
    if(lam > 0 && lam < 1)
        return fabs(X.cross(A, B)/(A - B).norm());
    return min((X - A).norm(), (X - B).norm());
}

bool on_seg(pt X, pt A, pt B) {
    return fabs((A - X).norm() + (B - X).norm() - (A - B).norm()) < 1e-9;
}

bool in_poly(pt A, poly Q) {
    int n = Q.size(), inter = 0;
    for(int i = 0; i < n; i++) {
        pt X = Q[i], Y = Q[(i + 1) % n];
        if(on_seg(A, X, Y)) return true;
        inter ^= ((A.y < X.y) - (A.y < Y.y)) * A.cross(X, Y) > 0;
    }
    return inter;
}

double dis(pt X, poly Q) {
    if(in_poly(X, Q)) return 0;
    double res = 1e18;
    int n = Q.size();
    for(int i = 0; i < Q.size(); i++)
        res = min(res, dis(X, Q[i], Q[(i + 1) % n]));
    return res;
}

double dis(poly A, poly B) {
    for(int i = 0; i < B.size(); i++)
        B[i] = pt(0, 0) - B[i];
    poly M = mink_add(A, B);
    return dis(pt(0, 0), M);
}

int main() {
    int n, m;
    cin >> n >> m;
    poly A(n), B(m);
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        A[i] = {x, y};
    }
    for(int i = 0;i < m; i++) {
        int x, y;
        cin >> x >> y;
        B[i] = {x, y};
    }
    cout << dis(A, B) << '\n';
}