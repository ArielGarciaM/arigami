#include <bits/stdc++.h>
using namespace std;

//ignore
typedef long long ll;
ll mmul(ll b, ll e, ll mod) {
    if(e == 0) return 0;
    ll x = mmul((b + b) % mod, e / 2, mod);
    return e % 2 ? ((x + b) % mod) : x;
}
ll mpow(ll b, ll e, ll mod) {
    if(e == 0) return 1;
    ll res = mpow(b, e / 2, mod);
    res = mmul(res, res, mod);
    if(e & 1) return mmul(res, b, mod);
    return res;
}
//unignore
bool isprime(ll p) {
    if(p == 1) return false;
    if(p % 2 == 0) return p == 2 ? true : false;
    ll d = p - 1;
    while(d % 2 == 0) d >>= 1ll;
    for(int its = 0; its < 15; its++) {
        ll a = (rand() % (p - 1)) + 1, x = d;
        a = mpow(a, d, p);
        while(x != p - 1 && a != p - 1 && a != 1) {
            a = mmul(a, a, p);
            x *= 2ll;
        }
        if(a != p - 1 && x % 2 == 0) return false;
    }
    return true;
}
int main() {
    ll p;
    while(true) {
        cin >> p;
        cout << isprime(p) << endl;
    }
}