#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* Para NTT:
998244353 = 119*2^23 + 1, raíz primitiva 3.
*/
const double PI = acos(-1);
typedef complex<double> C;

C mul(C &x, C &y) {
    double rx = x.real(), ix = x.imag(), ry = y.real(), iy = y.imag();
    return C(rx*ry - ix*iy, rx*iy + ix*ry);
}

vector<C> fft(vector<C> &P, vector<C> &root, vector<int> &rev) {
    int n = P.size();
    vector<C> f(n);
    for(int i = 0; i < n; i++)
        f[i] = P[rev[i]];
    for(int k = 1; k < n; k *= 2) {
        for(int i = 0; i < n; i += 2*k) {
            for(int j = 0; j < k; j++) {
                C z = mul(root[j + k], f[i + j + k]);
                f[i + j + k] = f[i + j] - z;
                f[i + j] = f[i + j] + z;
            }
        }
    }
    return f;
}

vector<C> conv(vector<C> A, vector<C> B) {
    int n = A.size() + B.size(), L = 32 - __builtin_clz(n);
    n = 1 << L;
    A.resize(n, 0), B.resize(n, 0);
    vector<C> root(n);
    for(int i = 0; i < n / 2; i++)
        root[i + n/2] = polar(1.0, 2.0*PI*((double)i)/((double)n));
    for(int i = n/2 - 1; i >= 0; i--)
        root[i] = root[2*i];
    vector<int> rev(n);
    for(int i = 1; i < n; i++)
        rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (L - 1));
    vector<C> f = fft(A, root, rev), g = fft(B, root, rev);
    for(int i = 0; i < n; i++) {
        f[i] = mul(f[i], g[i]);
        root[i] = conj(root[i]);
    }
    g = fft(f, root, rev);
    for(int i = 0; i < n; i++)
        g[i] /= n;
    return g;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<C> P(n + 1), Q(n + 1);
        for(int i = 0; i <= n; i++)
            cin >> P[i];
        for(int i = 0; i <= n; i++)
            cin >> Q[i];
        auto R = conv(P, Q);
        for(int i = 0; i < 2*n + 1; i++)
            cout << (ll)round(R[i].real()) << " ";
        cout << '\n';
    }
}