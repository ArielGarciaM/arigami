#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct P {
    ll x, y;
    P(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}
    P operator+ (const P &o) const { return P(x + o.x, y + o.y); }
    P operator- (const P &o) const { return P(x - o.x, y - o.y); }
    ll dot(const P &o) { return x * o.x + y * o.y; }
    ll cross(const P &o) const { return x * o.y - y * o.x; }
    ll cross(const P &A, const P &B) const { return (A - *this).cross(B - *this); }
    double norm() { return hypot(x, y); }
    int quad() const {
        if(x >= 0) {
            if(y >= 0) return 1;
            return 4;
        }
        if(y >= 0) return 2;
        return 3;
    }
    bool operator< (const P &o) const {
        if(quad() != o.quad()) return quad() < o.quad();
        return cross(o) > 0;
    }
};

ostream& operator<< (ostream& out, P p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

typedef vector<P> poly;

poly mink_add(poly A, poly B) {
    int i1 = 0, i2 = 0, n = A.size(), m = B.size();
    for(int i = 1; i < n; i++)
        if(A[i].y < A[i1].y || (A[i].y == A[i1].y && A[i].x < A[i1].x)) i1 = i;
    rotate(A.begin(), A.begin() + i1, A.end());
    for(int i = 1; i < m; i++)
        if(B[i].y < B[i1].y || (B[i].y == B[i1].y && B[i].x < B[i1].x)) i2 = i;
    rotate(B.begin(), B.begin() + i2, B.end());
    vector<P> edgA, edgB;
    for(int i = 0; i < n; i++)
        edgA.push_back(A[(i + 1) % n] - A[i]);
    for(int i = 0; i < m; i++)
        edgB.push_back(B[(i + 1) % m] - B[i]);
    poly combined;
    merge(edgA.begin(), edgA.end(), edgB.begin(), edgB.end(), back_inserter(combined));
    poly res({A[0] + B[0]});
    for(int i = 0; i < combined.size(); i++)
        res.push_back(res.back() + combined[i]);
    return res;
}

double dis(P X, P A, P B) {
    return 100;
}

bool in_convex_poly(P A, poly Q) {
    int n = Q.size();
    for(int i = 0; i < n; i++)
        if(A.cross(Q[i], Q[(i + 1) % n]) < 0) return false;
    return true;
}

double dis(P X, poly Q) {
    if(in_convex_poly(X, Q)) return 0;
    double res = 1e18;
    int n = Q.size();
    for(int i = 0; i < Q.size(); i++) {
        P A = Q[i], B = Q[(i + 1) % n];
        res = min(res, (X - A).norm());
        res = min(res, fabs(dis(X, A, B)));
    }
    return res;
}

double dis(poly A, poly B) {
    for(int i = 0; i < B.size(); i++)
        B[i] = P(0, 0) - B[i];
    poly M = mink_add(A, B);
    return dis(P(0, 0), M);
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