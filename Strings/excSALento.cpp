#include <bits/stdc++.h>
using namespace std;

//dependencias Hashing
//ignore
typedef long long ll;
typedef vector<ll> vl;
struct rhash {
    ll P, Q;  // P ~ cantidad de caracteres del alfabeto, Q ~ 10^9
    vl H, po; // Se pueden usar varios hashes si las colisiones son problema
    rhash(){}
    rhash(string &s, ll P, ll Q) : P(P), Q(Q) {
        int n = s.length(); H.resize(n); po.resize(n);
        po[0] = 1; H[0] = s[0];
        for(int i = 1; i < n; i++) {
            H[i] = (P*H[i - 1] + s[i])%Q;
            po[i] = (po[i - 1] * P)%Q;
        }
    }
    ll get(ll l, ll r) { // Hash de s[l, r]
        if(l == 0) return H[r];
        ll res = (H[r] - po[r - l + 1]*H[l - 1])%Q;
        return res >= 0 ? res : res + Q;
    }
};
//unignore
string s;
rhash H;
vector<int> SA;
int lcp(int a, int b) { // O(log n)
    if(s[a] != s[b]) return 0;
    int lo = 1, hi = s.length() - max(a, b);
    while(lo < hi) {
        int mi = (lo + hi + 1)/2;
        if(H.get(a, a + mi - 1) == H.get(b, b + mi - 1)) lo = mi;
        else hi = mi - 1;
    }
    return lo;
}
bool cmp(int a, int b) {
    int l = lcp(a, b);
    if(max(a, b) + l == s.length()) return (a != min(a, b));
    return s[a + l] < s[b + l];
}
void build() { // O(n*log(n)^2)
    SA.resize(s.size());iota(SA.begin(),SA.end(),0);sort(SA.begin(),SA.end(),cmp);
//ignore
    for(int i = 0; i < s.length(); i++) cout << SA[i] << " " << s.substr(SA[i]) << endl;
//unignore
}
int main() {
    s = "ABACABADABACABA";
    H = rhash(s, 31, 1000*1000*1000 + 7);
    build();
}