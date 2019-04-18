#include <bits/stdc++.h>
using namespace std;

//ignore
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
//unignore
vl lis(vl a) {
    int n = a.size(), sz = 0; map<pl, pl> pre;
    vl dp(n + 1, LLONG_MAX); dp[0] = LLONG_MIN;
    for(int i = 0; i < n; i++) {
        auto it = upper_bound(dp.begin(), dp.end(), a[i]); //a[i]-1 para estricta.
        if(*it == LLONG_MAX) sz++; *it = min(*it, a[i]);
        int pos = distance(dp.begin(), it); pre[{pos, a[i]}] = {pos - 1, dp[pos - 1]};
    }
    vl ans; pl cu = {sz, dp[sz]};
    do {
        ans.push_back(cu.second);
        cu = pre[cu];
    } while(cu.first);
    return reverse(ans.begin(), ans.end()), ans;
}
int main() {
    int n;
    cin >> n;
    vl v(n);
    for(auto &x : v) cin >> x;
    vl ans = lis(v);
    for(auto x : ans)
        cout << x << " ";
    cout << endl;
}