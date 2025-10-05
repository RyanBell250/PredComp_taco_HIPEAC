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
#include<bitset>
#include<stack>
#include<unordered_map>
#include<utility>
#include<cassert>
#include<complex>
#include<numeric>
#include<array>
using namespace std;

//#define int long long
typedef long long ll;

typedef unsigned long long ul;
typedef unsigned int ui;
constexpr ll mod = 998244353;
const ll INF = mod * mod;
typedef pair<int, int>P;
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
#define all(v) (v).begin(),(v).end()
typedef pair<ll, ll> LP;
typedef long double ld;
typedef pair<ld, ld> LDP;
const ld eps = 1e-12;
const ld pi = acosl(-1.0);

ll mod_pow(ll x, ll n, ll m = mod) {
	ll res = 1;
	while (n) {
		if (n & 1)res = res * x % m;
		x = x * x % m; n >>= 1;
	}
	return res;
}
struct modint {
	ll n;
	modint() :n(0) { ; }
	modint(ll m) :n(m) {
		if (n >= mod)n %= mod;
		else if (n < 0)n = (n % mod + mod) % mod;
	}
	operator int() { return n; }
};
bool operator==(modint a, modint b) { return a.n == b.n; }
modint operator+=(modint& a, modint b) { a.n += b.n; if (a.n >= mod)a.n -= mod; return a; }
modint operator-=(modint& a, modint b) { a.n -= b.n; if (a.n < 0)a.n += mod; return a; }
modint operator*=(modint& a, modint b) { a.n = ((ll)a.n * b.n) % mod; return a; }
modint operator+(modint a, modint b) { return a += b; }
modint operator-(modint a, modint b) { return a -= b; }
modint operator*(modint a, modint b) { return a *= b; }
modint operator^(modint a, ll n) {
	if (n == 0)return modint(1);
	modint res = (a * a) ^ (n / 2);
	if (n % 2)res = res * a;
	return res;
}

ll inv(ll a, ll p) {
	return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p);
}
modint operator/(modint a, modint b) { return a * modint(inv(b, mod)); }

const int max_n = 1 << 21;
modint fact[max_n], factinv[max_n];
void init_f() {
	fact[0] = modint(1);
	for (int i = 0; i < max_n - 1; i++) {
		fact[i + 1] = fact[i] * modint(i + 1);
	}
	factinv[max_n - 1] = modint(1) / fact[max_n - 1];
	for (int i = max_n - 2; i >= 0; i--) {
		factinv[i] = factinv[i + 1] * modint(i + 1);
	}
}
modint comb(int a, int b) {
	if (a < 0 || b < 0 || a < b)return 0;
	return fact[a] * factinv[b] * factinv[a - b];
}

using bt = bitset<100>;
struct graph {
private:
	int n;
	vector<vector<int>> G, rG;
	vector<bool> used;
	vector<int> vs;

	int mk;
	vector<vector<int>> fG;
	vector<vector<int>> ori;
	vector<int> trans;
public:
	graph(int sz) {
		n = sz;
		G.resize(n);
		rG.resize(n);
		used.resize(n);

		fG.resize(n);
		trans.resize(n, -1);
		ori.resize(n);
	}
	void add_edge(int a, int b) {
		G[a].push_back(b);
		rG[b].push_back(a);
	}
	void dfs(int v) {
		used[v] = true;
		rep(i, G[v].size()) {
			if (!used[G[v][i]])dfs(G[v][i]);
		}
		vs.push_back(v);
	}
	void rdfs(int v, int k) {
		used[v] = true;
		queue<int> q; q.push(v);
		vector<int> c;
		while (!q.empty()) {
			int id = q.front(); q.pop();
			ori[k].push_back(id);
			rep(j, rG[id].size()) {
				int to = rG[id][j];
				if (used[to]) {
					if (trans[to] >= 0)c.push_back(trans[to]);
					continue;
				}
				used[to] = true; q.push(to);
			}
		}
		sort(c.begin(), c.end());
		int len = unique(c.begin(), c.end()) - c.begin();
		rep(i, len) {
			fG[c[i]].push_back(k);
		}
		rep(i, ori[k].size()) {
			trans[ori[k][i]] = k;
		}
	}
	void scc() {
		fill(used.begin(), used.end(), false);
		rep(i, n) {
			if (!used[i])dfs(i);
		}
		fill(used.begin(), used.end(), false);
		int k = 0;
		per(i, (int)vs.size()) {
			if (!used[vs[i]]) {
				rdfs(vs[i], k); k++;
			}
		}
		mk = k;
	}
	bool valid() {
		rep(i, mk)if (ori[i].size() > 1)return false;
		return true;
	}
	vector<bt> query() {
		vector<bt> res(n);
		per(i, mk) {
			int id = ori[i][0];
			res[id][id] = 1;
			for (int tto : fG[i]) {
				int to = ori[tto][0];
				res[id] |= res[to];

			}
		}
		return res;
	}
	bool valid(int sz, vector<int> banlist, vector<bool> als) {
		vector<bool> used(sz);
		vector<bool> exi(mk, true);
		per(i, mk) {
			for (int id : ori[i]) {
				if (id < sz) {
					if (banlist[id] & 1)exi[i] = false;
				}
				else {
					if (banlist[id - sz] & 2)exi[i] = false;
				}
				if (used[id % sz])exi[i] = false;
			}
			for (int to : fG[i])if (!exi[to])exi[i] = false;
			if (exi[i]) {
				for (int id : ori[i]) {
					used[id % sz] = true;
				}
			}
		}
		rep(i, als.size())if (als[i] && !used[i])return false;
		return true;
	}
};

int gcd(int a, int b) {
	if (a > b)swap(a, b);
	while (b > 0) {
		int r = a % b; a = b; b = r;
	}
	return a;
}
int gcm(int a, int b) {
	return (a / gcd(a, b)) * b;
}

vector<int> cnt;
vector<int> loc;
void solve() {
	int n; cin >> n;
	vector<int> a(3 * n), b(3 * n);
	rep(i, 3 * n) {
		cin >> a[i]; a[i]--;
	}
	rep(i, 3 * n) {
		cin >> b[i]; b[i]--;
	}
	vector<vector<int>>trans(n, vector<int>(3, -1));
	vector<vector<int>> transb(n, vector<int>(3, -1));
	rep(i, 3 * n) {
		rep(j, 3) {
			if (trans[a[i]][j] < 0) {
				trans[a[i]][j] = i; break;
			}
		}
		rep(j, 3) {
			if (transb[b[i]][j] < 0) {
				transb[b[i]][j] = i; break;
			}
		}
	}
	cnt.resize(n);
	loc.resize(3 * n);
	vector<int> lcnt(n), rcnt(n);
	int ans = mod;
	//[l,r]を残す
	for (int l = 0; l < 3 * n; l++)for (int r = l; r < 3 * n; r++) {
		fill(all(lcnt), 0);
		fill(all(rcnt), 0);
		rep(i, l)lcnt[b[i]]++;
		Rep(i, r + 1, 3 * n) {
			rcnt[b[i]]++;
		}
		rep(i, 3 * n)Rep(j, i, 3 * n) {
			if (a[i] == b[l] && a[j] == b[r]) {
				fill(all(cnt), 0);
				for (int x = l; x <= r; x++) {
					cnt[b[x]]++;
				}
				fill(all(loc), -1);
				bool valid = true;
				graph sc(3 * n);
				rep(x, l - 1) {
					sc.add_edge(x, x + 1);
				}
				for (int x = 3 * n - 1; x - 1 > r; x--) {
					sc.add_edge(x, x - 1);
				}
				rep(c, n) {
					if (cnt[c] == 3) {
						rep(t, 3) {
							loc[transb[c][t]] = trans[c][t];
						}
					}
					else if (cnt[c] == 2) {
						int id = 0;
						rep(t, 3) {
							if (transb[c][t] >= l && transb[c][t] <= r) {
								loc[transb[c][t]] = trans[c][id];
								if (id == 0)id = 2;
							}
						}
					}
					else if (cnt[c] == 1) {
						if (lcnt[c] == 2) {
							loc[transb[c][2]] = trans[c][2];
						}
						else if (rcnt[c] == 2) {
							//cout << transb[c][0] << " " << trans[c][0] << "\n";
							loc[transb[c][0]] = trans[c][0];
						}
						else {
							//
						}
					}
					else {
						if (lcnt[c] == 3) {
							valid = false;
						}
						else if (rcnt[c] == 3) {
							valid = false;
						}
						else {
							if (lcnt[c] == 1) {
								sc.add_edge(transb[c][2], transb[c][0]);
								//sc.add_edge(transb[c][0], transb[c][1]);
							}
							else {
								sc.add_edge(transb[c][0], transb[c][2]);
								//sc.add_edge(transb[c][2], transb[c][1]);
							}
						}
					}
				}
				if (!valid)continue;
				//scc
				sc.scc();
				if (!sc.valid())continue;


				vector<bt> cp = sc.query();
				graph nw(2 * n);
				vector<int> banlist(n, 0);
				for (int x = l; x <= r; x++) {
					if (loc[x] < 0) {
						int id = b[x];

						int le = -mod;
						if (x - 1 >= l && loc[x - 1] >= 0)le = loc[x - 1];
						int ri = mod;
						if (x + 1 <= r && loc[x + 1] >= 0)ri = loc[x + 1];
						int al = trans[id][0];
						int ar = trans[id][2];
						if (x == l && al != i)banlist[id] |= 1;
						if (x == r && al != j)banlist[id] |= 1;
						if (x == l && ar != i)banlist[id] |= 2;
						if (x == r && ar != j)banlist[id] |= 2;
						if (al < le || al > ri)banlist[id] |= 1;
						if (ar < le || ar > ri)banlist[id] |= 2;
						if (banlist[id] == 3) {
							valid = false;
						}
					}
				}
				if (!valid)continue;
				if (loc[l] >= 0 && loc[l] != i)valid = false;
				if (loc[r] >= 0 && loc[r] != j)valid = false;
				for (int x = l; x < r; x++) {
					if (loc[x] >= 0 && loc[x + 1] >= 0) {
						if (loc[x] > loc[x + 1])valid = false;
					}
				}
				//cout << "? " << l << " " << r << "\n";
				if (!valid)continue;
				for (int x = l; x < r; x++) {
					if (loc[x] < 0 && loc[x + 1] < 0) {
						int al = trans[b[x]][0];
						int ar = trans[b[x]][2];
						int bl = trans[b[x + 1]][0];
						int br = trans[b[x + 1]][2];
						if (al > br) {
							valid = false;
							break;
						}
						if (ar > br) {
							banlist[b[x]] |= 2;
						}
						if (al > bl) {
							banlist[b[x + 1]] |= 1;
						}
						if (ar > bl) {
							nw.add_edge(b[x] + n, b[x + 1] + n);
							nw.add_edge(b[x + 1], b[x]);
						}
					}
				}
				for (int x = l; x <= r; x++) {
					if (loc[x] >= 0)continue;
					int ale = transb[b[x]][0];
					int ari = transb[b[x]][2];
					if (cp[ari][ale])banlist[b[x]] |= 1;
					if (cp[ale][ari])banlist[b[x]] |= 2;
					for (int y = x + 1; y <= r; y++) {
						if (loc[y] >= 0)continue;
						int ble = transb[b[y]][0];
						int bri = transb[b[y]][2];
						//left,left
						if (cp[ari][ble] && cp[bri][ale]) {
							nw.add_edge(b[x], b[y] + n);
							nw.add_edge(b[y], b[x] + n);
						}
						//left,right
						if (cp[ari][bri] && cp[ble][ale]) {
							nw.add_edge(b[x], b[y]);
							nw.add_edge(b[y] + n, b[x] + n);
						}
						//right,left
						if (cp[ale][ble] && cp[bri][ari]) {
							nw.add_edge(b[x] + n, b[y] + n);
							nw.add_edge(b[y], b[x]);
						}
						//right,right
						if (cp[ale][bri] && cp[ble][ari]) {
							nw.add_edge(b[x] + n, b[y]);
							nw.add_edge(b[y] + n, b[x]);
						}
					}
				}
				// cout << "?! " << l << " " << r << "\n";
				vector<bool> als(n);
				for (int x = l; x <= r; x++)if (loc[x] < 0)als[b[x]] = true;
				nw.scc();
				if (!nw.valid(n, banlist, als))continue;

				if (valid) {
					//cout << l << " " << r << " "<<i<<" "<<j<<"\n";
					ans = min(ans, l + (3 * n - 1 - r));
				}
			}
		}
	}
	if (ans == mod)ans = -1;
	//assert(ans >= 0);
	cout << ans << "\n";
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout << fixed << setprecision(8);
	//init_f();
	//init();
	//expr();
	//int t; cin >> t; rep(i, t)
	solve();
	return 0;
}



