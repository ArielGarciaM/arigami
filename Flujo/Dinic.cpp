#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5000, INF = 1e9;
int dist[MAXN], ptr[MAXN], src, dst;
struct Edge {
    int to, rev, f, cap;
	Edge(int to, int rev, int f, int cap) : to(to), rev(rev), f(f), cap(cap);
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
            if(dist[v] == -1 && e.f < e.cap) {
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
    while(bfs()) {
        memset(ptr, 0, sizeof ptr);
        while(long long pushed = dfs(src, INF))
            mf += pushed;
    }
    return mf;
}
int main() {}