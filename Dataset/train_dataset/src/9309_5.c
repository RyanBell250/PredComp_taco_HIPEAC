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
using namespace std;
typedef long long ll;
typedef unsigned int ui;
const ll mod = 1000000007;
const ll INF = (ll)1000000007 * 1000000007;
typedef pair<int, int> P;
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
typedef long double ld;
typedef complex<ld> Point;
const ld eps = 1e-11;
const ld pi = acos(-1.0);
typedef pair<ll, ll> LP;
typedef pair<ld, ld> LDP;
typedef unsigned long long ul;
int a[1 << 17];
const int MAX_N = (1 << 17);
int nn, dat[2 * MAX_N - 1];
void init(int n_) {
	nn = 1;
	while (nn < n_)nn *= 2;
}
void update(int k, int a) {
	k += nn - 1;
	dat[k] = a;
	while (k > 0) {
		k = (k - 1) / 2;
		dat[k] = dat[k * 2 + 1]+ dat[k * 2 + 2];
	}
}
int query(int a, int b, int k, int l, int r) {
	if (r <= a || b <= l)return 0;
	if (a <= l && r <= b)return dat[k];
	else {
		int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
		int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
		return vl+vr;
	}
}
vector<int> v[1 << 17];
int main() {
	int n; cin >> n; init(n);
	rep(i, n) {
		cin >> a[i];
		update(i, 1);
		v[a[i]].push_back(i);
	}
	ll out = 0;
	rep1(i, 100000) {
		rep(j, v[i].size()) {
			update(v[i][j], 0);
		}
		rep(j, v[i].size()) {
			out += min(query(0, v[i][j], 0, 0, nn), query(v[i][j], n, 0, 0, nn));
		}
	}
	cout << out << endl;
	return 0;
}
