#include <bits/stdc++.h>
using namespace std;
//ignore
typedef long long ll;
//unignore

const int MAXN = 5005, INF = 1e9;
const bool scale = true; // Magia. Mejor en gráficas muy grandes o casos anti-Dinic, pero peor constante.
int dist[MAXN], ptr[MAXN], src, dst, lim = 1;
struct Edge {
    int to, rev, f, cap;
	Edge(int to, int rev, int f, int cap) : to(to), rev(rev), f(f), cap(cap) {}
};
vector<Edge> G[MAXN];
void addEdge(int u, int v, int cap) {
    G[u].push_back(Edge(v, G[v].size(), 0, cap));
    G[v].push_back(Edge(u, G[u].size() - 1, 0, 0));
}
bool bfs() {
    queue<int> q({src});
    memset(dist, -1, sizeof dist);
    dist[src] = 0;
    while(!q.empty() && dist[dst] == -1) {
        int u = q.front();
        q.pop();
        for(auto e : G[u]) {
            int v = e.to;
            if(dist[v] == -1 && e.f < e.cap && (!scale || e.cap - e.f >= lim)) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist[dst] != -1;
}
int dfs(int u, int f) {
    if(u == dst || !f) return f;
    for(int &i = ptr[u]; i < G[u].size(); i++) {
        Edge &e = G[u][i];
        int v = e.to;
        if(dist[v] != dist[u] + 1) continue;
        if(int df = dfs(v, min(f, e.cap - e.f))) {
            e.f += df;
            G[v][e.rev].f -= df;
            return df;
        }
    }
    return 0;
}
long long dinic() {
    long long mf = 0;
    for(lim = (scale ? (1 << 30) : 1); lim > 0; lim >>= 1) {
        while(bfs()) {
            memset(ptr, 0, sizeof ptr);
            while(long long pushed = dfs(src, INF))
                mf += pushed;
        }
    }
    return mf;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        addEdge(a, b, w);
        addEdge(b, a, w);
    }
    src = 1, dst = n;
    cout << dinic() << endl;
}