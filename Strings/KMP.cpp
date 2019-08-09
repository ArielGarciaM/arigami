/*INFO
Descripcion: KMP + Automaton. Encuentra $\pi[i] = \max \{x \colon s[0 : x) = s(i - x : i]\}$ para cada $i$.
Complejidad: $\mathcal{O}(n)$.
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
typedef vector<int> vi;
//unignore

vi kmp(string s) {
    vi pi(s.size());
    for(int i = 1, j = 0; i < s.size(); i++) {
        while(j && s[i] != s[j]) j = pi[j - 1];
        pi[i] = j += (s[i] == s[j]);
    }
    return pi;
}
void build_aut(string s, vector<vi> &aut) {
    aut.assign(s.size(), vi(26));
    vi pi = kmp(s);
    for(int c = 0; c < 26; c++)
        aut[0][c] = (s[0] == 'a' + c);

    for(int i = 1; i < s.size(); i++) {
        for(int c = 0; c < 26; c++) {
            if(s[i] == 'a' + c) aut[i][c] = i + 1;
            else aut[i][c] = aut[pi[i - 1]][c];
        }
    }
}

int main() {

}