#include <bits/stdc++.h>
using namespace std;

//ignore
typedef long long ll;
typedef vector<ll> vl;
//unignore
struct rhash {
    ll P, Q;  // P ~ cantidad de caracteres del alfabeto, Q ~ 10^9
    vl H, po; // Se pueden usar varios hashes si las colisiones son problema
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
int main() {
    string s = "abacabadabacaba";
    auto H = rhash(s, 31, 1000000007);
    for(int i = 0; i < s.length(); i++) {
        for(int j = i; j < s.length(); j++) {
            cout << s.substr(i, j - i + 1) << " " << H.get(i, j) << endl;
        }
    }
}