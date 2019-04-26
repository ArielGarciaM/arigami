/*INFO
{\bf Descripción:} Union Find con path compression y union by size. Mantiene representantes de una unión disjunta.
{\bf Complejidad:} $\mathcal{O}(\alpha(n))$ amortizado.
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;
int rep[MAXN], sz[MAXN];
void init() {
    fill(rep, rep + MAXN, -1), fill(sz, sz + MAXN, 1);
}
int find(int u) {
    return (rep[u] == -1) ? u : rep[u] = find(rep[u]);
}
bool join(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return false;
    if(sz[u] < sz[v]) swap(u, v);
    return sz[u] += sz[v], rep[v] = u, true;
}
int main() {
    int n;
    cin >> n;
    init();
    while(true) {
        int u, v;
        cin >> u >> v;
        cout << join(u, v) << endl;
        for(int i = 0; i < n; i++)
            cout << sz[i] << " ";
        cout << endl;
    }
}