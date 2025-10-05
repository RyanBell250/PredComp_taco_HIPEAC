#include <bits/stdc++.h>
using namespace std;

using ll = long long int;

void chmax(ll &a, ll b){
    a = max(a,b);
}

int solve(){
    int n;
    cin >> n;
    if(n == 0) return 1;
    vector<int> v(n), t(n);
    for(int i=0;i<n;i++){
        int m;
        cin >> m >> v[i];
        for(int j=0;j<m;j++){
            int s, e;
            cin >> s >> e;
            s-=6; e-=6;
            for(int k=s;k<e;k++){
                t[i] |= 1<<k;
            }
        }
    }
    const int T_MAX = 1<<16;
    ll dp[T_MAX]{};
    for(int i=0;i<n;i++){
        for(int S=0;S<T_MAX;S++){
            if((S&t[i])==0){
                chmax(dp[S|t[i]], dp[S]+v[i]);
            }
        }
    }
    cout << dp[T_MAX-1] << endl;
    return 0;
}


int main(){
    while(solve()==0);
    return 0;
}

