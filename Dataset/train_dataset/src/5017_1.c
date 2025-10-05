#ifndef BZ
#pragma GCC optimize "-O3"
#endif
#include <bits/stdc++.h>
#define ALL(v) (v).begin(), (v).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using namespace std;
const ll MOD = 998244353;
ll pw(ll a, ll b) {
	ll ans = 1; while (b) {
		while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
		ans = (ans * a) % MOD, --b;
	} return ans;
}
const int MX = 2e6;
ll fc[MX];
ll bfc[MX];
void init() {
	fc[0] = 1;
	for (int i = 1; i < MX; ++i)
		fc[i] = (fc[i - 1] * i) % MOD;
	bfc[MX - 1] = pw(fc[MX - 1], MOD - 2);
	for (int i = MX - 2; i >= 0; --i)
		bfc[i] = (bfc[i + 1] * (i + 1)) % MOD;
}
ll cnk(int n, int k) {
	if (k > n)
		return 0;
	return fc[n] * bfc[k] % MOD * bfc[n - k] % MOD;
}
int n, m;
int main() {
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	init();
	cin >> n >> m;
	ll ans = 0;
	for (int i = m; i >= 0; i -= 2) {
		ans = (ans + cnk(n, i) * cnk((3 * m - i) / 2 + n - 1, n - 1)) % MOD;
	}
	ll go = 0;
	for (int i = 2 * m + 1; i <= 3 * m; ++i) {
		go = (go + cnk(3 * m - i + n - 2, n - 2)) % MOD;
	}
	go = (go * n) % MOD;
	ans = (ans - go + MOD) % MOD;
	cout << ans << "\n";
	return 0;
}
