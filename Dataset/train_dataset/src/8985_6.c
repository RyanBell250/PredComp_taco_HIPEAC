#pragma GCC optimization "O2"
#pragma GCC optimization "unroll-loop"
#pragma GCC target ("avx2")

#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define fs first
#define sc second
using namespace std;
const ll N = 35009;
const ll Log2 = 20;
const ll inf = 1e9 + 7;
typedef pair<ll,ll> LL;
vector<ll> g[N];
ll n,k,dp[109][N],x,biggest[N],a[N];

void Renew(ll lf,ll rg,ll now){
    for (ll i = lf;i <= now;i++) biggest[a[i]] = i;
}

ll st,en,nxt[N],pre[N],last[N],res;

ll cal(ll l,ll r){
    while(st < l){
        if (nxt[st] <= en) res -= nxt[st] - st;
        st++;
    }
    while(st > l){
        st--;
        if (nxt[st] <= en) res += nxt[st] - st;
    }
    while(en < r){
        en++;
        if (pre[en] >= st) res += en - pre[en];
    }
    while(en > r){
        if (pre[en] >= st) res -= en - pre[en];
        en--;
    }
    return res;
}

void DAC(ll grp,ll l,ll r,ll lf,ll rg){
    if (l > r) return;
    ll now = (l + r)/2,cost = 0,total = inf,opt;
    //cout<<cal(3,4); exit(0);
    for (ll i = min(now,rg);i >= lf;i--){
        ll cost = cal(i,now);
        //cout<<cost<<" "<<dp[grp - 1][i - 1]<<"\n";
        if (total > cost + dp[grp - 1][i - 1]){
            opt = i; total = cost + dp[grp - 1][i - 1];
        }
    }
    //exit(0);
    dp[grp][now] = total; //exit(0);
    DAC(grp,l,now - 1,lf,opt); DAC(grp,now + 1,r,opt,rg);
}

void out(){
    for (ll i = 1;i <= k;i++){
        for (ll j = 1;j <= n;j++) cout<<dp[i][j]<<" ";
        cout<<"\n";
    }
    exit(0);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    #define task "tst"
    if (fopen(task".inp", "r")){
        freopen(task".inp", "r", stdin);
        //freopen(task".out", "w", stdout);
    }
    cin>>n>>k; st = en = 1;
    for (ll i = 1;i <= n;i++){
        cin>>a[i]; pre[i] = last[a[i]];
        if (pre[i]) nxt[pre[i]] = i; last[a[i]] = i;
    }
    for (ll i = 1;i <= n;i++) last[a[i]] = 0;
    for (ll i = n;i > 0;i--) if (!last[a[i]]) nxt[i] = n + 1,last[a[i]] = i;

    for (ll i = n;i > 0;i--) biggest[a[i]] = i;
    for (ll i = 1;i <= n;i++){
        dp[1][i] = dp[1][i - 1] + i - biggest[a[i]];
        biggest[a[i]] = i;
    }
    for (ll i = 2;i <= k;i++) DAC(i,1,n,1,n);
    cout<<dp[k][n];
}
