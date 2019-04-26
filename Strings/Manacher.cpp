/*INFO
{\bf Descripción: } Calcula $p[i] = $ máximo $L$ tal que $s[i - L : i + L]$ es capicua.
{\bf Complejidad: } $\mathcal{O}(n)$
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
typedef vector<int> vi;
//unignore
vi manacher(string &s) {
    // Encuentra palindromos de longitud impar.
    int n = s.length(), l = -1, r = -1;
    vi p(n);
    for(int i = 0; i < n; i++) {
        if(i <= r) p[i] = min(p[l + r - i], r - i);
        while(i+p[i]+1 < n && i-p[i]-1 >= 0 && s[i+p[i]+1] == s[i-p[i]-1]) p[i]++;
        if(i + p[i] > r) l = i - p[i], r = i + p[i];
    }
    return p;
}
int main() {
    string s;
    cin >> s;
    for(int i = 0; i < s.length(); i++)
        cout << s[i] << " ";
    cout << endl;
    vi p = manacher(s);
    for(int i = 0; i < s.length(); i++)
        cout << p[i] << " ";
    cout << endl;
}