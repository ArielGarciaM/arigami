/*INFO
{\bf Descripción:} Encuentra un árbol generador de peso mínimo para una gráfica.
{\bf Complejidad:} $\mathcal{O}(E \log E)$
{\bf Dependencias:} \texttt{Estructuras/Union Find}
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
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
//unignore
struct edge {
    int u, v, w;
    bool operator< (const edge &o) const{ return w < o.w; }
};
vector<edge> edges;
int kruskal() {
    int res = 0;
    sort(edges.begin(), edges.end());
    for(auto e : edges) if(join(e.u, e.v))
        res += e.w; // uv es arista del MST
    return res;
}
int main(){}