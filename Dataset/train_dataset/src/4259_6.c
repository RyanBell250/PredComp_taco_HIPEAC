#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

long long fact[200005], mmi[200005];

long long power(long long n, long long expo)
{
    long long ans = 1;

    while (expo)
    {
        if (expo % 2)
            ans = ans * n % MOD;
        
        n = n * n % MOD;
        expo /= 2;
    }

    return ans;
}

long long nCr(int n, int r)
{
    return fact[n] * mmi[r] % MOD * mmi[n-r] % MOD;
}

int main() {
    
    int n, m, k;
    cin >> n >> m >> k;

    fact[0] = mmi[0] = 1;

    for (int i=1; i<=n; i++)
    {
        fact[i] = fact[i-1] * i % MOD;
        mmi[i] = power(fact[i], MOD - 2);
    }

    long long ans = 0;

    for (int i=0; i<=k; i++)
        ans += power(m-1, n-1-i) * nCr(n-1, i) % MOD;

    cout << ans % MOD * m % MOD << "\n";

    return 0;
}
