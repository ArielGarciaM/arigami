/*INFO
{\bf Descripción: } Encuentra $x$ tal que $x \equiv x_1 \pmod{m_1}, x \equiv x_2 \pmod{m_2}$. Regresa $-1$ si tal $x$ no existe.
{\bf Complejidad: } $\mathcal{O}(\log(m_1 + m_2))$. Rápido en la práctica.
*/
#include <bits/stdc++.h>
using namespace std;

template<typename T> void euclid(T a, T b, T &x, T &y) {
    if(!b) {x = 1, y = 0; return;}
    euclid(b, a % b, y, x);
    y -= a/b * x;
}
template<typename T> T crt(T x1, T m1, T x2, T m2) {
    T d = __gcd(m1, m2), r, s;
    if(x1 % d != x2 % d)
        return -1;
    euclid(m1, m2, r, s);
    m1 /= d, m2 /= d;
    T mod = d*m1*m2, a1 = ((m1*r)%mod*x2)%mod, a2 = ((m2*s)%mod*x1)%mod, y = (a1 + a2)%mod;
    return (y >= 0 ? y : y + mod);
}
int main(){
    int x1, m1, x2, m2;
    cin >> x1 >> m1 >> x2 >> m2;
    cout << crt(x1, m1, x2, m2);
}