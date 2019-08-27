#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct state {
    int link, chr, leaf;
    vector<int> to;
    state(int chr) : chr(chr), leaf(0), link(-1), to(vector<int>(26, -1)) {};
};
vector<state> t;

int add_word(string &s) {
    int cur = 0;
    for(auto &c : s) {
        if(t[cur].to[c - 'a'] == -1) {
            t[cur].to[c - 'a'] = t.size();
            t.push_back(state(c - 'a'));
        }
        cur = t[cur].to[c - 'a'];
    }
    t[cur].leaf = 1;
    return cur;
}

void build_aho() {
    queue<int> q;
    q.push(0);
    t[0].link = 0;
    while(!q.empty()) {
        int v = q.front(); q.pop();
        for(int ch = 0; ch < 26; ch++) {
            if(t[v].to[ch] != -1) {
                t[t[v].to[ch]].link = v == 0 ? 0 : t[t[v].link].to[ch];
                q.push(t[v].to[ch]);
            }
            else
                t[v].to[ch] = v == 0 ? 0 : t[t[v].link].to[ch];
        }
    }
}

int main() {
    
}