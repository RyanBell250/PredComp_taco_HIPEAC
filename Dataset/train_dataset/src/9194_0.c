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
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
typedef unsigned int ui;
const ll mod = 1000000007;
const ll INF = (1e+18) + 7;
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
const ld eps = 1e-6;
const ld pi = acos(-1.0);
typedef vector<int> vec;
ll mod_pow(ll a, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1)res = res * a%mod;
		a = a * a%mod; n >>= 1;
	}
	return res;
}
struct modint {
	ll n;
	modint() :n(0) { ; }
	modint(ll m) :n(m) {
		if (n >= mod)n %= mod;
		else if (n < 0)n = (n%mod + mod) % mod;
	}
	operator int() { return n; }
};
bool operator==(modint a, modint b) { return a.n == b.n; }
modint operator+=(modint &a, modint b) { a.n += b.n; if (a.n >= mod)a.n -= mod; return a; }
modint operator-=(modint &a, modint b) { a.n -= b.n; if (a.n < 0)a.n += mod; return a; }
modint operator*=(modint &a, modint b) { a.n = ((ll)a.n*b.n) % mod; return a; }
modint operator+(modint a, modint b) { return a += b; }
modint operator-(modint a, modint b) { return a -= b; }
modint operator*(modint a, modint b) { return a *= b; }
modint operator^(modint a, int n) {
	if (n == 0)return modint(1);
	modint res = (a*a) ^ (n / 2);
	if (n % 2)res = res * a;
	return res;
}
ll inv(ll a, ll p) {
	return (a == 1 ? 1 : (1 - p * inv(p%a, a)) / a + p);
}
modint operator/(modint a, modint b) { return a * modint(inv(b, mod)); }
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
using poly = vector<int>;
poly operator+(const poly &a, const poly &b) {
	poly res(a.size());
	rep(i, a.size())res[i] = a[i] + b[i];
	return res;
}
poly operator-(const poly &a) {
	poly res(a.size());
	rep(i, a.size())res[i] = -a[i];
	return res;
}
const poly inf(52, mod);
const poly zerop(52,0);
using speP = pair<poly, int>;
int max_n;
const int mn = 100000;
struct edge {
	int to, cap; poly cost; int rev;
};
vector<edge> G[mn];
P par[mn];
poly dist[mn];
void add_edge(int from, int to, int cap, poly cost) {
	G[from].push_back({ to,cap,cost,(int)G[to].size() });
	G[to].push_back({ from,0,-cost,(int)G[from].size() - 1 });
	max_n = max({ max_n, from + 1, to + 1 });
}
poly minimum_road(int s, int t) {
	fill(par, par + max_n, LDP{ -1,-1 });
	fill(dist, dist + max_n, inf);
	dist[s] = zerop;
	priority_queue<speP, vector<speP>, greater<speP>> q; q.push({ zerop,s });
	while (!q.empty()) {
		speP p = q.top(); q.pop();
		int id = p.second;
		if (id == t)continue;
		if (p.first > dist[id])continue;
		rep(j, G[id].size()) {
			if (G[id][j].cap > 0) {
				int to = G[id][j].to;
				poly nd = p.first + G[id][j].cost;
				if (nd < dist[to]) {
					dist[to] = nd;
					par[to] = { id,j };
					q.push({ dist[to],to });
				}
			}
		}
	}
	int cur = t;
	int f = 1;
	while (cur != s) {
		int p = par[cur].first, j = par[cur].second;
		if (p < 0)return { -1,-1 };
		G[p][j].cap -= f;
		if (G[p][j].rev >= 0) {
			G[cur][G[p][j].rev].cap += f;
		}
		cur = p;
	}
	return dist[t];
}
poly minimum_cost_flow(int s, int t, int k) {
	poly ret = zerop;
	rep(i, k) {
		poly z = minimum_road(s, t);
		ret = ret + z;
	}
	return ret;
}
int trans(char &t) {
	if (t <= 'Z')return t - 'A';
	else return 26 + t - 'a';
}
char trans(int &i) {
	if (i < 26)return 'A' + i;
	else return 'a' + i - 26;
}
char mp[50][50];
void solve() {
	int n; cin >> n;
	rep(i, n) {
		rep(j, n) {
			cin >> mp[i][j];
		}
	}
	int sta = 2 * n; int goa = sta + 1;
	rep(i, n)add_edge(sta, i, 1, zerop);
	rep(i, n)add_edge(i + n, goa, 1, zerop);
	rep(i, n)rep(j, n) {
		poly c(52, 52); c[trans(mp[i][j])]--;
		add_edge(i, j + n, 1, c);
	}
	string ans;
	poly p=minimum_cost_flow(sta, goa, n);
	rep(i, 52)rep(j, 52*n-p[i])ans.push_back(trans(i));
	cout << ans << endl;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	solve();
	stop
		return 0;
}
