#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

int fact[500050],inv[500050];

int qpow(int base,int tms)
{
    int tmp = 1;
    while(tms)
    {
        if(tms & 1) tmp = tmp * 1ll * base % mod;
        base = base * 1ll * base % mod;
        tms >>= 1;
    }
    return tmp;
}

int C(int n,int r)
{
    return fact[n] * 1ll * inv[r] % mod * inv[n - r] % mod;
}

int main()
{
    fact[0] = inv[0] = 1;
    for(int i = 1;i <= 500000; ++ i)
        fact[i] = fact[i - 1] * 1ll * i % mod;
    inv[500000] = qpow(fact[500000],mod - 2);
    for(int i = 499999;i >= 1; -- i)
        inv[i] = inv[i + 1] * 1ll * (i + 1) % mod;
    int n,m; scanf("%d%d",&n,&m);
    int lim = min(n,m),ans = 0;
    for(int i = 0,sgn = 1;i <= lim; ++ i,sgn = mod - sgn)
        ans = (ans + sgn * 1ll * C(n,i) % mod * C(m,i) % mod * qpow(n + 1,m - i) % mod * qpow(m + 1,n - i) % mod * fact[i] % mod) % mod;
    printf("%d\n",ans);
    return 0;
}