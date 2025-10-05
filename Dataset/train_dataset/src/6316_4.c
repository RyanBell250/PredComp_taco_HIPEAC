#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<functional>
#include<iomanip>
#include<queue>
#include<ciso646>
#include<random>
#include<map>
#include<set>
#include<complex>
#include<bitset>
#include<stack>
#include<unordered_map>
#include<utility>
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
typedef unsigned int ui;
const ll mod = 1000000007;
typedef double ld;
typedef complex<ld> Point;
const ll INF = mod * mod;
typedef pair<int, int> P;
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
const ld eps = 1e-8;
const ld pi = acos(-1.0);
typedef pair<ld, ld> LDP;
typedef pair<ll, ll> LP;
int c[1 << 17];
struct edge2 {
	int to, id;
};
vector<edge2> g[100000];
int root;
int parent[17][100000];
int depth[100000];
void dfs(int v, int p, int d) {
	parent[0][v] = p;
	depth[v] = d;
	for (int i = 0; i < (int)g[v].size(); i++) {
		if (g[v][i].to != p)dfs(g[v][i].to, v, d + 1);
	}
}
void init(int V) {
	dfs(root, -1, 0);
	for (int k = 0; k + 1 < 17; k++) {
		for (int v = 0; v < V; v++) {
			if (parent[k][v] < 0)parent[k + 1][v] = -1;
			else parent[k + 1][v] = parent[k][parent[k][v]];
		}
	}
}
int lca(int u, int v) {
	if (depth[u] > depth[v])swap(u, v);
	for (int k = 0; k < 17; k++) {
		if ((depth[v] - depth[u]) >> k & 1) {
			v = parent[k][v];
		}
	}
	if (u == v)return u;
	for (int k = 16; k >= 0; k--) {
		if (parent[k][u] != parent[k][v]) {
			u = parent[k][u];
			v = parent[k][v];
		}
	}
	return parent[0][u];
}
vector<int> ans;
void dfs2(int id,int fr) {
	rep(j, g[id].size()) {
		int to = g[id][j].to;
		if (to == fr)continue;
		dfs2(to, id);
		c[id] += c[to];
		if (c[to] > 0) {
			ans[g[id][j].id] = 1;
		}
	}
}
struct uf {
private:
	vector<int> par, ran;
public:
	uf(int n) {
		par.resize(n, 0);
		ran.resize(n, 0);
		rep(i, n) {
			par[i] = i;
		}
	}
	int find(int x) {
		if (par[x] == x)return x;
		else return par[x] = find(par[x]);
	}
	void unite(int x, int y) {
		x = find(x), y = find(y);
		if (x == y)return;
		if (ran[x] < ran[y]) {
			par[x] = y;
		}
		else {
			par[y] = x;
			if (ran[x] == ran[y])ran[x]++;
		}
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
};
struct edge {
	int to; ll cost; int id;
};
vector<edge> G[1 << 17],rG[1<<17];
ll ds[1 << 17], dg[1 << 17];
priority_queue<LP,vector<LP>,greater<LP>> q;
void solve() {
	int n, m; cin >> n >> m;
	ans.resize(m);
	rep(i, m) {
		int a, b, c; cin >> a >> b >> c; a--; b--;
		G[a].push_back({ b,c,i });
		rG[b].push_back({ a,c,i });
	}
	fill(ds, ds + n, INF); fill(dg, dg + n, INF);
	ds[0] = 0; q.push({ 0,0 });
	while (!q.empty()) {
		LP p = q.top(); q.pop();
		int id = p.second;
		rep(j, G[id].size()) {
			int to = G[id][j].to;
			ll nd = p.first + G[id][j].cost;
			if (nd < ds[to]) {
				ds[to] = nd;
				q.push({ nd,to });
			}
		}
	}
	dg[1] = 0; q.push({ 0,1 });
	while (!q.empty()) {
		LP p = q.top(); q.pop();
		int id = p.second;
		rep(j, rG[id].size()) {
			int to = rG[id][j].to;
			ll nd = p.first + rG[id][j].cost;
			if (nd < dg[to]) {
				dg[to] = nd;
				q.push({ nd,to });
			}
		}
	}
	ll ma = ds[1];
	vector<P> banlist;
	uf u(n);
	rep(i, n) {
		rep(j, G[i].size()) {
			int to = G[i][j].to;
			ll cost = ds[i] + dg[to] + G[i][j].cost;
			if (cost == ma) {
				if (u.same(i, to)) {
					ans[G[i][j].id] = 1;
					banlist.push_back({ i,to });
				}
				else {
					u.unite(i, to);
					g[i].push_back({ to,G[i][j].id });
					g[to].push_back({ i,G[i][j].id });
				}
			}
		}
	}
	root = 0;
	init(n);
	rep(i, banlist.size()) {
		int le = banlist[i].first, ri = banlist[i].second;
		int cp = lca(le, ri);
		c[le]++; c[ri]++; c[cp] -= 2;
	}
	dfs2(root,-1);
	rep(i, n) {
		rep(j, G[i].size()) {
			int to = G[i][j].to, id = G[i][j].id;
			ll cost = G[i][j].cost;
			if (cost + ds[to] + dg[i] < ma) {
				ans[id] = 2;
			}
			else if (cost + ds[i] + dg[to] > ma) {
				ans[id] = 1;
			}
		}
	}
	rep(i, m) {
		if (ans[i] == 0) {
			cout << "SAD" << endl;
		}
		else if (ans[i] == 1) {
			cout << "SOSO" << endl;
		}
		else {
			cout << "HAPPY" << endl;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
