/*INFO
{\bf Descripción: } Calcula $z[i] = $ máximo $L$ tal que $s[i : i + L) = s[0 : L)$ para cada $i$. Útil para string matching.
{\bf Complejidad: } $\mathcal{O}(n)$
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
typedef vector<int> vi;
//unignore
vi z_func(string &s) {
    int n = s.length(), l = -1, r = -1;
    vi z(n);
    for(int i = 1; i < n; i++) {
        if(i <= r) z[i] = min(z[i - l], r - i + 1);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}
int main() {
    string s;
    cin >> s;
    vi z = z_func(s);
    for(int i = 0; i < s.length(); i++)
        cout << s[i] << " ";
    cout << endl;
    for(int i = 0; i < s.length(); i++)
        cout << z[i] << " ";
    cout << endl;
}