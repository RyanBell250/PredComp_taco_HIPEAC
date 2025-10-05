#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const ll mod = 1e9 + 7;
#define inf 1e18 + 3
#define pb push_back
#define mp make_pair

void solve() {
	int n, k;
	cin >> n >> k;
	ll ans = 1;
	while (k > 0) {
		ans = (ans * n) % mod;
		k--;
	}
	cout << ans << '\n';
}

signed main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t;
	cin >> t;
	while (t--)solve();
	return 0;
}