#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

vi pi(string s) {
    vi b(s.size());
    for(int i = 1, j = 0; i < s.size(); i++) {
        while(j && s[i] != s[j]) j = b[j - 1];
        b[i] = j + (s[i] == s[j]);
    }
    return b;
}