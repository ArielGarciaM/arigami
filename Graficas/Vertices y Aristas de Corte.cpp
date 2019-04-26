/*INFO
{\bf Descripción: } Encuentra vértices de corte y aristas de corte (puentes) en una gráfica.
{\bf Complejidad: } $\mathcal{O}(V + E)$
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int low[MAXN], ord[MAXN], tin;
vector<int> adj[MAXN];
int dfs(int s) {
    low[s] = ord[s] = ++tin;
    for(auto v : adj[s]) {
        if(!low[v]) {
            dfs(v);
            if(low[v] > ord[s]) { /* uv es puente */ }
            if(low[v] >= ord[s]) { /* u es punto de articulacion (o raiz) */}
            low[s] = min(low[s], low[v]);
        }
        else if(ord[v] < ord[s])
            low[s] = min(low[s], ord[v]);
    }
    return low[s];
}
int main() {
    
}