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
typedef long double ld;
typedef pair<int, int> P;
typedef pair<ll, ll> LP;
typedef pair<ld, ld> LDP;
typedef complex<ld> Point;
const ll mod = 1000000007;
const ll INF = mod * mod;
const ld eps = 1e-8;
const ld pi = acos(-1.0);
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
int max_n;
const int mn = 100000;
struct edge {
	int to, cap, cost, rev;
};
vector<edge> G[mn];
int par[mn];
int dist[mn];
void add_edge(int from, int to, int cap, int cost) {
	G[from].push_back({ to,cap,cost,(int)G[to].size() });
	G[to].push_back({ from,0,-cost,(int)G[from].size() - 1 });
	max_n = max({ max_n, from + 1, to + 1 });
}
int minimum_road(int s,int t) {
	fill(par, par + max_n, -1);
	fill(dist, dist + max_n, mod);
	dist[s] = 0;
	priority_queue<P,vector<P>,greater<P>> q; q.push({ 0,s });
	while (!q.empty()) {
		P p = q.top(); q.pop();
		int id = p.second;
		if (id == t)continue;
		rep(j, G[id].size()) {
			if (G[id][j].cap > 0) {
				int to = G[id][j].to;
				int nd = p.first + G[id][j].cost;
				if (nd < dist[to]) {
					dist[to] = nd;
					par[to] = id;
					q.push({ dist[to],to });
				}
			}
		}
	}
	int cur = t;
	while (cur != s) {
		int p = par[cur];
		if (p < 0)return -1;
		rep(j, G[p].size()) {
			if (G[p][j].cap > 0&&G[p][j].to==cur&&dist[p]+G[p][j].cost==dist[cur]) {
				G[p][j].cap--;
				G[cur][G[p][j].rev].cap++;
				break;
			}
		}
		cur = p;
	}
	return dist[t];
}
int minimum_cost_flow(int s, int t,int k) {
	int ret = 0;
	rep(i, k) {
		int z = minimum_road(s,t);
		if (z < 0)return -1;
		ret += z;
	}
	return ret;
}
int x[100][100];
int y[100][100];
char mp[100][100];
bool used[100][100];
void solve() {
	int n; cin >> n;
	rep(i, n) {
		rep(j, n) {
			cin >> x[i][j];
		}
	}
	rep(i, n) {
		rep(j, n) {
			cin >> y[i][j];
		}
	}
	rep(i, n) {
		rep(j, n) {
			cin >> mp[i][j];
		}
	}
	rep(i, n) {
		rep(j, n) {
			int sum = 0;
			rep(k, n) {
				if (j != k)if (mp[i][k] == 'o')sum += y[i][k];
				if (i != k)if (mp[k][j] == 'o')sum += y[k][j];
			}
			if (mp[i][j] == '.')sum += 2 * x[i][j];
			
			add_edge(i, n + j,1, sum);
		}
	}
	int s = 2 * n, t = 2 * n + 1;
	rep(i, n) {
		add_edge(s, i, 1, 0);
		add_edge(n + i, t, 1, 0);
	}
	int ans = minimum_cost_flow(s, t,n);
	cout << ans / 2 << endl;
	rep(i, n) {
		rep(j, G[i].size()) {
			edge &e = G[i][j];
			if (e.to < s) {
				if (e.cap == 0) {
					used[i][e.to - n] = true; break;
				}
			}
		}
	}
	vector<P> era, wri;
	rep(i, n) {
		rep(j, n) {
			if (used[i][j] && mp[i][j] == '.') {
				wri.push_back({ i + 1,j + 1 });
			}
			if (!used[i][j] && mp[i][j] == 'o') {
				era.push_back({ i + 1,j + 1 });
			}
		}
	}
	cout << wri.size() + era.size() << endl;
	rep(i, era.size()) {
		cout << era[i].first << " " << era[i].second << " " << "erase" << endl;
	}
	rep(i, wri.size()) {
		cout << wri[i].first << " " << wri[i].second << " write" << endl;
	}
}
int main() {
	solve();
	
	return 0;
}
