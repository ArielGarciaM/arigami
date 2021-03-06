/*INFO
{\bf Descripción:} Segment Tree recursivo para RMQ y similares. Los intervalos son cerrados.
{\bf Complejidad:} $\mathcal{O}(\log n)$ en updates y queries.
*/
#include <bits/stdc++.h>
using namespace std;

const int NE = 1e9;
struct node {
    int mn, l, r;
    node *left, *right;
    node(int l, int r, int* A) : l(l), r(r) {
        if(l == r)
            mn = A[l];
        else {
            int mi = (l + r)/2;
            left = new node(l, mi, A);
            right = new node(mi + 1, r, A);
            mn = min(left->mn, right->mn);
        }
    }
    void upd(int p, int v) {
        if(r < p || p < l)
            return;
        if(l == r) {
            mn = v;
            return;
        }
        left->upd(p, v), right->upd(p, v);
        mn = min(left->mn, right->mn);
    }
    int qry(int rl, int rr) {
        if(rr < l || r < rl)
            return NE;
        if(rl <= l && r <= rr)
            return mn;
        return min(left->qry(rl, rr), right->qry(rl, rr));
    }
};

const int MAXN = 1e5 + 5;
int a[MAXN];

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    node tree(0, n - 1, a);
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        cout << tree.qry(l, r) << endl;
    }
}