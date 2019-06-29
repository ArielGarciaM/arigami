/*INFO
{\bf Descripción: } Dadas sucesiones enteras $\{a_k\}$ y $\{b_k\}$, $\texttt{conv}(a, b)$ calculauna convolucion
$c_k = \sum a_ib_{k - i} \pmod{p}$ para $p = 2^ab + 1$ un primo con $2^a$ mayor a la longitud de las sucesiones.
{\bf Complejidad: } $\mathcal{O}(n \log n)$.
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

/* Otras alternativas:
   P = 5 << 25 + 1, 7 << 26 + 1, ambos con raiz 3. */
const ll MOD = (119 << 23) + 1, gen = 3;

ll mpow(ll b, ll e) {
    ll res = 1;
    for(ll k = 1; k <= e; k <<= 1) {
        if(k & e) res = (res * b)%MOD;
        b = (b * b)%MOD;
    }
    return res;
}

void ntt(vl &f, vl &root, vector<int> &rev) {
    int n = f.size();
    for(int i = 0; i < n; i++)
        if(i < rev[i]) swap(f[i], f[rev[i]]);
    for(int k = 1; k < n; k *= 2) {
        for(int i = 0; i < n; i += 2*k) {
            for(int j = 0; j < k; j++) {
                ll z = (root[j + k] * f[i + j + k]) % MOD;
                f[i + j + k] = (f[i + j] < z ? f[i + j] - z + MOD : f[i + j] - z);
                f[i + j] = (f[i + j] + z >= MOD ? f[i + j] + z - MOD : f[i + j] + z);
            }
        }
    }
}

vl conv(vl A, vl B) {
    int sz = A.size() + B.size() - 1, L = 32 - __builtin_clz(sz), n = 1 << L;
    vl f(A), g(B), res(n), root(n, 1);
    f.resize(n), g.resize(n);
    ll pr = mpow(gen, MOD/n), inv = mpow(n, MOD - 2);
    for(int i = n/2 + 1; i < n; i++)
        root[i] = (pr * root[i - 1])%MOD;
    for(int i = n/2 - 1; i >= 0; i--)
        root[i] = root[2*i];
    vector<int> rev(n);
    for(int i = 1; i < n; i++)
        rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (L - 1));
    ntt(f, root, rev), ntt(g, root, rev);
    for(int i = 0; i < n; i++)
        res[i] = (f[i] * g[i])%MOD;
    reverse(res.begin() + 1, res.end());
    ntt(res, root, rev);
    for(int i = 0; i < sz; i++)
        res[i] = (res[i] * inv) % MOD;
    return {res.begin(), res.begin() + sz};
}

int main() {

}