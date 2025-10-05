#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, MAXN = 3e2 + 2;
ll fastpow(ll base, ll p) {
	ll res = 1;
	for(; p; p >>= 1, base = base * base % mod) if(p & 1) res = res * base % mod;
	return res;
}
int f[MAXN][30], t, n, dis[MAXN], lg[MAXN];
ll p[MAXN][MAXN];
vector<int> adj[MAXN];
int lca(int x, int y) {
	if(dis[x] < dis[y]) swap(x, y);
	for(int i = lg[dis[x]]; i >= 0; i--) {
		if(dis[f[x][i]] >= dis[y]) x = f[x][i];
	}
	if(x == y) return x;
	for(int i = lg[dis[y]]; i >= 0; i--) {
		if(f[x][i] != f[y][i]) {
			x = f[x][i]; y = f[y][i];
		}
	}
	return f[x][0];
}
void dfs(int u, int fa) {
	f[u][0] = fa;
	dis[u] = dis[fa] + 1;
	for(int i = 1; i <= lg[dis[u]]; i++) {
		f[u][i] = f[f[u][i - 1]][i - 1];
	}
	for(int v : adj[u]) if(fa != v) {
		dfs(v, u);
	}
}
ll calc(int x) {
	memset(f, 0, sizeof(f));
	dfs(x, 0);
	ll res = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			int l = lca(i, j);
			res += p[dis[i] - dis[l]][dis[j] - dis[l]];
			res %= mod;
		}
	}
	return res;
}
ll ans;
int main() {
	for(int i = 2; i < MAXN; i++) lg[i] = lg[i >> 1] + 1;
	for(int i = 1; i < MAXN; i++) {
		p[i][0] = 1;
		for(int j = 1; j < MAXN; j++) {
			p[i][j] = (p[i - 1][j] + p[i][j - 1]) % mod * fastpow(2, mod - 2) % mod;
		}
	}
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	for(int i = 1; i <= n; i++) {
		ans += calc(i);
		ans %= mod;
	}
	ans = ans * fastpow(n, mod - 2) % mod;
	printf("%lld", ans);
	return 0;
}
