#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); i++)
using ll = long long;
using namespace std;

int n;
vector<int> a, b;
vector<bool> used;

bool check () {
    vector<vector<bool>> data(51,vector<bool>(51,false));
    rep(i,51) if(i && used[i]) rep(j,51) data[j][j%i] = true; rep(i,51) data[i][i] = true;
    rep(i,51) rep(j,51) rep(k,51) if (data[i][k] && data[k][j]) data[i][j] = true;
    rep(i,n) if (!data[a[i]][b[i]]) return false;
    return true;
}

int main(){
    cin >> n;
    a.resize(n); rep(i,n) cin >> a[i];
    b.resize(n); rep(i,n) cin >> b[i];
    rep(i,n) if(a[i] < b[i]) { cout << -1 << "\n"; return 0; }

    used.assign(51,true); 

    if (!check()) { cout << -1 << "\n"; return 0; }
    for (int i = 50; i >= 1; i--) {
        used[i] = false;
        if (!check()) used[i] = true;
    }
    ll ans = 0; rep(i,51) if(i && used[i]) ans += 1ll<<i;
    cout << ans << "\n";
    return 0;
}