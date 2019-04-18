#include <bits/stdc++.h>
using namespace std;

//ignore
typedef vector<int> vi;
//unignore
vi val, comp, sta;
int Time, ncomps;
template<class G> int dfs(int s, G &g) {
    int low = val[s] = ++Time, x; sta.push_back(s);
    for(auto v : g[s]) if(comp[v] < 0)
        low = min(low, val[v] ?: dfs(v, g));
    if(low == val[s]) {
        do {
            x = sta.back(); sta.pop_back();
            comp[x] = ncomps;
        } while(x != s);
        ncomps++;
    }
}
template<class G> int scc(G &g) {
    int n = g.size();
    comp.assign(n, -1), val.assign(0, -1);
    Time = ncomps = 0;
    for(int i = 0; i < n; i++) if(comp[i] < 0) dfs(i, g);
}
int main() {}