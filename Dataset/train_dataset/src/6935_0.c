
#include <bits/stdc++.h>
#define F first
#define S second
#define pb push_back
#define all(x) x.begin(), x.end()
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int N = 25000 + 10;
const ll MOD = 1000000000 + 7;
const ll INF = 1000000010;
const ll LOG = 25;
int dp[N][410], ps[N][410], ans[N][410], psa[N][410], n, m, k, a[N], fac[N], inv[N], R[N], cnt[410], tav[N];
int mul(int a, int b){
	return (a * 1ll * b) % MOD;
}
int add(int a, int b){
	a += b;
	if (a >= MOD) a -= MOD;
	return a;
}
int minu(int a, int b){
	a -= b;
	if (a < 0) a += MOD;
	return a;
}
int POW(int a, int b){
	int res = 1;
	while (b){
		if (b & 1) res = mul(res, a);
		b >>= 1;
		a = mul(a, a);
	}
	return res;
}
int32_t main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	tav[0] = 1;
	cin >> n >> k >> m;
	for (int i = 1; i < N; i++) tav[i] = tav[i - 1] * 1ll * k % MOD;
	fac[0] = 1;
	for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * 1ll * i % MOD, inv[i] = POW(fac[i], MOD - 2);	
	for (int i = 1; i <= m; i++) cin >> a[i];
	bool f = 0;
	for (int i = 1; i <= m - k + 1; i++){
		memset(cnt, 0, sizeof cnt);
		for (int j = i; j <= i + k - 1; j++){
			cnt[a[j]]++;
			if (cnt[a[j]] == 2){
				R[i] = j - 1;
				break;
			}
		}
		if (R[i] == 0) R[i] = i + k - 1;
		if (R[i] == i + k - 1){
			return cout << mul(n - m + 1, tav[n - m]), 0;
		}
	}
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= m; i++){
		cnt[a[i]]++;
		if (cnt[a[i]] > 1) f = 1;
	}
	if (!f){
		dp[0][0] = 1;
		ps[0][0] = 1;
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= k - 1; j++){
				dp[i][j] = add(ps[i - 1][j], mul(dp[i - 1][j - 1], k - j + 1));
				ans[i][j] = add(mul(ans[i - 1][j - 1], k - j + 1), psa[i - 1][j]);
				if (j >= m) ans[i][j] = add(ans[i][j], mul(dp[i][j], mul(fac[k - m], inv[k])));
			}
			for (int j = k - 1; j >= 1; j--) ps[i][j] = add(ps[i][j + 1], dp[i][j]), psa[i][j] = add(psa[i][j + 1], ans[i][j]);
		}
		int res = mul(n - m + 1, tav[n - m]);
		return cout << minu(res, psa[n][1]), 0;
	}
	memset(cnt, 0, sizeof cnt);
	int Fi = 0;
	for (int i = 1; i <= m; i++){
		cnt[a[i]]++;
		if (cnt[a[i]] > 1){
			Fi = i - 1;
			break;
		}
	}
	dp[0][0] = 1;
	ps[0][0] = 1;
	int Tah = 0;
	memset(cnt, 0 , sizeof cnt);
	for (int i = m; i >= 1; i--){
		cnt[a[i]] ++;
		if (cnt[a[i]] > 1){
			Tah = i;
			break;
		}
	}
	Tah = m - Tah;
	for (int i = 1; i <= n; i++){
			for (int j = 1; j <= k - 1; j++){
			dp[i][j] = add(ps[i - 1][j], mul(dp[i - 1][j - 1], k - j + 1));
			ans[i][j] = add(mul(ans[i - 1][j - 1], k - j + 1), psa[i - 1][j]);
		}
		if (i >= m){
			ans[i][Tah] = add(ans[i][Tah], mul(ps[i - m + Fi][Fi], mul(fac[k - Fi], inv[k])));
		}
		for (int j = k - 1; j >= 1; j--) ps[i][j] = add(dp[i][j], ps[i][j + 1]), psa[i][j] = add(psa[i][j + 1], ans[i][j]); 
	}	
	int res = mul(n - m + 1, tav[n - m]);
	cout << minu(res, psa[n][1]);
	return 0;
}
