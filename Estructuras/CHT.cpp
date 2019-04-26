/*INFO
{\bf Descripción:} Mantiene una envolvente $S$ con queries de agregar lineas $y = mx + b$ y queries para $\max_{(m, b)\in S} mx + b$.
{\bf Complejidad:} $\mathcal{O}(\log n)$ amortizado por query.
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
typedef long long ll;
//unignore
bool Q;
struct Line {
    mutable ll m, b, p;
    bool operator<(const Line& o) const {
        return Q ? p < o.p : m < o.m;
    }
};
struct LineContainer : multiset<Line> {
    const ll inf = LLONG_MAX;
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
        else x->p = div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }
    void add(ll m, ll b) {
        auto z = insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z)) z  = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)-> p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        Q = 1; auto l = *lower_bound({0, 0, x}); Q = 0;
        return l.m * x + l.b;
    }
};
int main() {

}