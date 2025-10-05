#include<bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#define FASTER ios_base::sync_with_stdio(0);cin.tie(0)
#define trace(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); tracer(_it, args); cout << endl; }
void tracer(istream_iterator<string> it) {}
template<typename T, typename... Args>
void tracer(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << " | ";
	tracer(++it, args...);
}
#define setPrecision(n) cout << std::setprecision(n) << std::fixed;
#define rep(i,j,n) for(int i = j; i < n; i++)
#define ll long long
#define ld long double
#define pb push_back
#define pii pair<int,int>
#define sz(x) ((int) (x).size())
#define all(c) (c).begin(),(c).end()
#define F first
#define S second

const int INF = 2e9;
const long long LINF =  2e18;
const long long MOD = 1e9 + 7;
const double err = 1e-10;
const int N = 2e5 + 5;
vector<vector<int>> adj;
vector<int> leaf;
int k;
void dfs(int u, int par = -1) {
	int child = 0, mxdep = 0, mndep = INF;
	vector<int> deps;
	for (auto v : adj[u]) {
		if (v == par) continue;
		child++;
		dfs(v, u);
		deps.pb(leaf[v] + 1);
	}
	if (child > 0) {
		sort(all(deps));
		mxdep = deps.back();
		mndep = deps.front();
		leaf[u] = mndep;
		if (u == 1) {
			k = max(k, deps.back());
			if (sz(deps) > 1) {
				k = max(k, deps[sz(deps) - 2] + 1);
			}
		}
		else {
			k = max(k, mxdep + 1);
		}
	}
	else {
		leaf[u] = 0;
	}
}
void solve() {
	int n;
	cin >> n;
	adj = vector<vector<int>>(n + 1);
	leaf = vector<int>(n + 1);
	rep(i, 0, n - 1) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	k = 1;
	dfs(1);
	cout << k << "\n";
}
int32_t main() {
	
	
	FASTER;
	int T = 1;
	cin >> T;
	for (int i = 1; i <= T; i++) {
		
		solve();
	}
	return 0;
}
