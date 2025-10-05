#include <iostream>
#include <cstring>
using namespace std;
#define mod 1000000007
typedef long long ll;
const int maxn = 1e6 + 5;
ll fac[2 * maxn], inv[2 * maxn];
int k, len;
ll qpow(ll a, ll b)
{
	ll res = 1;
	while (b)
	{
		if (b & 1)
		{
			res *= a;
			res %= mod;
		}
		a *= a;
		a %= mod;
		b /= 2;
	}
	return res % mod;
}
void init()
{
	fac[0] = 1;
	for (int i = 1; i <= len + k; i++)
	{
		fac[i] = fac[i - 1] * i % mod;
	}
	inv[len + k] = qpow(fac[len + k], mod - 2);
	for (int i = len + k - 1; i >= 0; i--)
	{
		inv[i] = inv[i + 1] * (i + 1) % mod;
	}
}
ll C(int m, int n)
{
	return  fac[m] * inv[m - n] % mod * inv[n] % mod;
}
int main()
{
	ios::sync_with_stdio(false);
	char s[maxn];
	cin >> k >> s;
	len = strlen(s);
	init();
	ll ans = 0;
	for (int i = 0; i <= k; i++)
	{
		ans = (ans + qpow(26, i) * C(k + len - i - 1, len - 1) % mod * qpow(25, k - i) % mod) % mod;
	}
	cout << ans << endl;
	return 0;
}
