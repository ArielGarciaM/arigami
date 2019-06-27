#include <bits/stdc++.h>
using namespace std;

//ignore
typedef long long ll;
//unignore
const int SEED = 17111999;
struct treap {
    int k, p, cnt;
    treap *l, *r;
    treap() {}
    treap(int k, int p) : k(k), p(p), l(nullptr), r(nullptr){}
};
typedef treap* ptreap;
inline int cnt(ptreap t) { return t ? t->cnt : 0; }
inline void upd(ptreap t) { if(t) t->cnt = 1 + cnt(t->l) + cnt(t->r); }
void split(ptreap t, ll k, ptreap &l, ptreap &r) {
    if(!t)
        l = r = nullptr;
    else if (k < t->k)
        split(t->l, k, l, t->l), r = t;
    else
        split(t->r, k, t->r, r), l = t;
    upd(t);
}
void merge(ptreap &t, ptreap l, ptreap r) {
    if(!l || !r)
        t = l ? l : r;
    else if(l.p > r.p)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
    upd(t);
}
void insert(ptreap &t, ptreap x) {
    if(!t)
        t = x;
    else if(x->p > t->p)
        split(t, x->k, x->l, x->r), t = x;
    else
        insert(x->k < t->k ? t->l : t->r, x);
    upd(t);
}
void erase(ptreap &t, int k) {
    if(!t)
        return;
    if(t->k == k)
        merge(t, t->l, t->r);
    else
        erase(k < t->k ? t->l : t->r, k);
    upd(t);
}
int main() {
    
}