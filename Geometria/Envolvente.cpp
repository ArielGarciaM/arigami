#include <bits/stdc++.h>
using namespace std;

//ignore
template<class T>
struct pt {
    T x, y;
    pt(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator< (pt o) const {return (x < o.x || (x == o.x && y < o.y)); }
    bool operator== (pt o) const {return (x == o.x && y == o.y);}
    pt operator+ (pt o) const {return pt(x + o.x, y + o.y);}
    pt operator- (pt o) const {return pt(x - o.x, y - o.y);}
    pt operator* (T l) const {return pt(l*x, l*y);}
    pt operator/ (T l) const {return pt(x/l, y/l);}
    T dot(pt o) { return x*o.x + y*o.y; }
    T cross(pt o) { return x*o.y - y*o.x; }
    T cross(pt a, pt b) { return (a - *this).cross(b - *this); }
    T normsq(pt o) { return x*x +y*y; }
    double norm(pt o) { return hypot(x, y); }
};
typedef long long ll;
//unignore
vector<pt<ll>> convex_hull(vector<pt<ll>> P) {
    int n = P.size();
    if(n <= 2) return P;
    vector<pt<ll>> L, U;
    sort(P.begin(), P.end());
    for(int i = 0; i < n; i++) {
        while(U.size() >= 2 && U[U.size() - 2].cross(U[U.size() - 1], P[i]) >= 0)
            U.pop_back();
        while(L.size() >= 2 && L[L.size() - 2].cross(L[L.size() - 1], P[n-i-1]) >= 0)
            L.pop_back();
        U.push_back(P[i]), L.push_back(P[n - i - 1]);
    }
    U.insert(U.end(), L.begin() + 1, L.end() - 1);
    return U;
}
int main() {
    int n;
    cin >> n;
    vector<pt<ll>> poly(n);
    for(int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        poly[i] = pt<ll>(x, y);
    }
    auto v = convex_hull(poly);
    for(auto p : v)
        cout << p.x << " " << p.y << endl;
}