/*INFO
{\bf Descripción:} Encuentra los minimos de todos los subarreglos de longitud $k$.
{\bf Complejidad:} $\mathcal{O}(n)$.
*/
#include <bits/stdc++.h>
using namespace std;

//ignore
typedef vector<int> vi;
typedef pair<int, int> ii;
//unignore

vi mins(vi &v, int k) {
    int n = v.size();
    assert(k <= n);
    deque<ii> window;
    vi result;
    for(int i = 0, j = 0; i + k <= n; i++) {
        while(j < i + k) {
            while(window.size() && v[j] <= window.back().first)
                window.pop_back();
            window.push_back({v[j], j});
            j++;
        }
        while(window.size() && window.front().second < i)
            window.pop_front();
        result.push_back(window.front().first);
    }
    return result;
}

int main() {

}