#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cassert>
#include<cmath>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<queue>
#include<stack>
using namespace std;
#define MOD2 1000000007
#define MOD 998244353
#define INF ((1<<30)-1)
#define LINF (1LL<<60)
#define EPS (1e-10)
typedef long long Int;
typedef pair<Int, Int> P;

Int fact[1100000];
Int revfact[1100000];
Int rev[1100000];

void init(){
    Int m = MOD;
    fact[0] = 1;
    revfact[0] = 1;
    rev[0] = 0;
    rev[1] = 1;
    for(int i = 1;i < 1100000;i++){
        fact[i] = fact[i-1] * i % m;
        if(i>1)rev[i] = MOD / i * (MOD-rev[MOD % i]) % MOD;
        revfact[i] = revfact[i-1] * rev[i] % MOD;
    }
}

Int nCk(Int n, Int k){
    if(n < k)return 0;
    return fact[n] * revfact[n-k] % MOD * revfact[k] % MOD;
}

Int calc(Int n, Int x){
    if(n % 2 == 1)return 0;
    n /= 2;
    return nCk(n+x, n);
}

Int dp[550][550];

int main(){
    init();
    int n, x;
    cin >> n >> x;
    dp[0][0] = 1;
    for(Int num = 0;num <= x;num++){
        for(int i = n;i > 0;i--){
            for(int j = 0;j < 550;j++){
                dp[i][j] += dp[i-1][j^num];
                dp[i][j] %= MOD;
            }
        }
    }
    Int ans=0;
    for(int i = 0;i <= n;i++){
        ans += dp[i][x] * calc(n-i, x);
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
