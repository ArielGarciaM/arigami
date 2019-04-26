/*INFO
{\bf Descripción: } Highest Label Preflow Push con gap heuristic. Calcula un flujo máximo en una red.
{\bf Complejidad: } $\mathcal{O}(V^2\sqrt{E})$
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
typedef long long ll;
typedef vector<int> vi;
//unignore
const int MAXN = 5000 + 5;
struct Edge {
    int to, rev;
    ll flow, cap;
};
vector<Edge> adj[MAXN];
void addEdge(int u, int v, int c, int r = 0) {
    Edge a = {v, (int)adj[v].size(), 0, c};
    Edge b = {u, (int)adj[u].size(), 0, r};
    adj[u].push_back(a);
    adj[v].push_back(b);
}
ll ex[MAXN];
vi hs[2*MAXN];
int H[MAXN], ptr[MAXN], n;
void push(Edge &e, ll f) {
    Edge &back = adj[e.to][e.rev];
    if(!ex[e.to] && f) hs[H[e.to]].push_back(e.to);
    e.flow += f; e.cap -= f; ex[e.to] += f;
    back.flow -= f; back.cap += f; ex[back.to] -= f;
}
ll maxflow(int s, int t) {
    H[s] = n; ex[t] = 1;
    vi cnt(2*n); cnt[0] = n - 1;
    for(auto e : adj[s]) push(e, e.cap);

    for(int ch = 0;;) {
        while(hs[ch].empty())
            if(!ch--) return -ex[s];
        int u = hs[ch].back(); hs[ch].pop_back();
        while(ex[u] > 0) {
            if(ptr[u] == adj[u].size()) {
                ptr[u] = 0;
                H[u]++;
                cnt[ch]--;
                cnt[H[u]]++;
                if(!cnt[ch] && ch < n) {
                    for(int v = 1; v <= n; v++) {
                        if(H[v] > ch && H[v] < n) {
                            --cnt[H[v]], H[v] = n + 1;
                        }
                    }
                }
                ch = H[u];
            }
            else {
                Edge &e = adj[u][ptr[u]];
                if(e.cap && H[u] ==  H[e.to] + 1)
                    push(e, min(ex[u], e.cap));
                else ++ptr[u];
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        if(a != b)
            addEdge(a, b, w, w);
    }
    cout << maxflow(1, n) << endl;
}