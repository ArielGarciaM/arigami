/*INFO
{\bf Descripción:} Árbol que mantiene subsucesiones de un arreglo formadas por elementos con valores en ciertos intervalos. Útil para range queries de k-ésimo elemento o número de elementos debajo de cierta cota, etc.
{\bf Complejidad:} $\mathcal{O}(\log(\max A))$ por query.
*/
#include <bits/stdc++.h>
using namespace std;

struct wnode {
    wnode *left, *right;
    int lo, hi;
    vector<int> c;
    wnode(int lo, int hi, int* st, int* en) : lo(lo), hi(hi) {
        if(hi == lo || st == en)
            return;
        int mi = (lo + hi)/2;
        auto f = [mi](int x) { return x <= mi; };
        c.push_back(0);
        for(auto it = st; it != en; ++it)
            c.push_back(c.back() + f(*it));
        auto it = stable_partition(st, en, f);
        left = new wnode(lo, mi, st, it);
        right = new wnode(mi + 1, hi, it, en);
    }
    int kth(int L, int R, int k) {
        if(lo == hi)
            return lo;
        int der = c[R], izq = c[L - 1], tol = der - izq;
        if(tol >= k)
            return left->kth(izq + 1, der, k);
        return right->kth(L - izq, R - der, k - tol);
    }
};
int main(){}