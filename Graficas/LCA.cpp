#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6, LOG = 20;
vector<int> adj[MAXN];
int up[LOG][MAXN], dep[MAXN];
void dfs(int s, int p = 0) {
    up[0][s] = (p ?: s);
    dep[s] = (p ? dep[p] + 1 : s);
    for(auto v : adj[s]) if(v != s) dfs(v, s);
}
void build() {
    dfs(1);
    for(int l = 1; l < LOG; l++) for(int v = 1; v < MAXN; v++)
        up[l][v] = up[l - 1][up[l - 1][v]];
}
void jmp(int &u, int v, int d) {
    for(int l = LOG - 1; l >= 0; l--) if(d & (1 << l))
            u = up[l][u];
}
int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    jmp(u, v, dep[u] - dep[v]);
    if(u == v) return u;
    for(int l = LOG - 1; l >= 0; l--)
        if(up[l][u] != up[l][v])
            u = up[l][u], v = up[l][v];
    return up[0][u];
}
int main(){}