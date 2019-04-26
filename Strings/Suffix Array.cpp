/*INFO
{\bf Descripción: } Crea $SA$ tal que $s[SA[i]:n] \leq s[SA[i + 1]:n]$ para todo $i$.
{\bf Complejidad: } $\mathcal{O}(n \log n)$
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
typedef pair<int,int> ii;
//unignore
const int MAXN = 5e5 + 10;
string s;
int SA[MAXN], LCP[MAXN], val[MAXN], cnt[MAXN], n;

void csort(int l) {
    int mx = max(300, n), sum = 0, tSA[MAXN];
    fill(cnt, cnt + mx, 0);
    for(int i = 0; i < n; i++)
        cnt[(SA[i] + l < n) ? val[SA[i] + l] : 0]++;
    for(int i = 0; i < mx; i++)
        {int t = cnt[i]; cnt[i] = sum; sum += t;}
    for(int i = 0; i < n; i++)
        tSA[cnt[SA[i] + l < n ? val[SA[i] + l] : 0]++] = SA[i];
    for(int i = 0; i < n; i++)
        SA[i] = tSA[i];
}
void buildSA() {
    n = s.length();
    int nval[MAXN], rk, l = 1;
    iota(SA, SA + n, 0);
    for(int i = 0; i < n; i++)
        val[SA[i]] = s[i];
    do {
        csort(l);
        csort(0);
        nval[SA[0]] = rk = 0;
        for(int i = 1; i < n; i++) nval[SA[i]] =
            ii{val[SA[i]],val[SA[i]+l]} == ii{val[SA[i-1]],val[SA[i - 1]+l]} ? rk:++rk;
        for(int i = 0; i < n; i++)
            val[i] = nval[i];
        l <<= 1;
    } while(val[SA[n - 1]] != n - 1 && l < n);
}
void buildLCP() { // LCP[i] = LCP(s[SA[i - 1]:n], s[SA[i]:n])
    int pre[MAXN], PLCP[MAXN], L = 0;
    pre[SA[0]] = -1;
    for(int i = 1; i < n; i++)
        pre[SA[i]] = SA[i - 1];
    for(int i = 0; i < n; i++) {
        if(pre[i] == -1) {
            PLCP[i] = -1;
            continue;
        }
        while(s[i + L] == s[pre[i] + L]) L++;
        PLCP[i] = L;
        L = max(0, L - 1);
    }
    for(int i = 0; i < n; i++)
        LCP[i] = PLCP[SA[i]];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    string t;
    cin >> s >> t;
    int m = s.length();
    s += '$';
    s += t;
    s += '#';
    buildSA();
    buildLCP();
    int ans = 0;
    //for(int i = 0; i < s.length(); i++)
    //    cout << s.substr(SA[i]) << " " << LCP[i] << endl;
    for(int i = 1; i < n; i++) {
        if((SA[i] < m && SA[i - 1] > m) || (SA[i] > m && SA[i - 1] < m))
            ans = max(ans, LCP[i]); 
    }
    cout << ans << endl;
}