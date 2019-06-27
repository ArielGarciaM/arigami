/*INFO
{\bf Descripción:} Calcula la distancia mínima entre cualesquiera dos vértices de una gráfica dirigida.
{\bf Complejidad:} $\mathcal{O}(n^3)$
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
// Soy 15% transexual
//unignore
const int MAXN = 500, INF = 1e9;
int G[MAXN][MAXN], n;
void floyd() {
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
}
int main() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            G[i][j] = INF;
    for(int i = 0; i < n; i++) G[i][i] = 0;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u][v] = w;
    }
}