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
using namespace std;
typedef long long ll;
typedef unsigned long long ul;
typedef unsigned int ui;
const ll mod = 998244353;
const ll INF = mod * mod;
typedef pair<int, int> P;
#define stop char nyaa;cin>>nyaa;
#define rep(i,n) for(int i=0;i<n;i++)
#define per(i,n) for(int i=n-1;i>=0;i--)
#define Rep(i,sta,n) for(int i=sta;i<n;i++)
#define rep1(i,n) for(int i=1;i<=n;i++)
#define per1(i,n) for(int i=n;i>=1;i--)
#define Rep1(i,sta,n) for(int i=sta;i<=n;i++)
typedef pair<ll, ll> LP;
typedef vector<LP> vec;
typedef vector<string> svec;
typedef long double ld;
typedef pair<ld, ld> LDP;
const ld eps = 1e-8;
ll dp[200][1 << 10],cop[200][1<<10];
void solve() {
	int n, k; ll m; cin >> n >> k >> m;
	int s = (1 << 10);
	rep1(i, k) {
		dp[i][0] = 1;
	}
	rep(i, n - 1) {
		rep(j, 200) {
			rep(x, (1 << 10))cop[j][x] = 0;
		}
		rep(j, 200) {
			rep(x, (1 << 10)) {
				if (dp[j][x] == 0)continue;
				int len = j - i;
				if (len > n)continue;
				if (len < i + 1)continue;
				else if (len == i + 1) {
					bool f = false; int las;
					rep(l, 10) {
						if ((x&(1 << l)) == 0) {
							las = j - 1 - l;
							f = true; break;
						}
					}
					if (!f)continue;
					if (j + 1 - las > k)continue;
					Rep1(l, 2, k) {
						if (j + l >= 2 * n)continue;
						int nx = x << l; nx += (1 << (l - 1));
						nx %= s;
						cop[j + l][nx] += dp[j][x];
						if (cop[j + l][nx] >= m)cop[j + l][nx] -= m;
					}
				}
				else {
					int dif = len - (i + 1);
					int tmp = 0; bool f = false;
					int past;
					int las;
					rep(l, 10) {
						if ((x&(1 << l))==0) {
							if (tmp == 0) {
								las = j - 1 - l;
							}
							tmp++;
							if (tmp == dif) {
								past = j - 1 - l;
								f = true; break;
							}
						}
					}
					if (!f) {
						continue;
					}
					rep1(l, k) {
						int nj = j + l;
						if (nj >= 2 * n)continue;
						if (nj - past > k)continue;
						if (l > 1) {
							if (j + 1 - las > k)continue;
						}
						int nx = x << l; nx += (1 << (l-1));
						nx %= s;
						cop[nj][nx] += dp[j][x];
						if (cop[nj][nx] >= m)cop[nj][nx] -= m;
					}
				}
			}
		}
		rep(j, 200) {
			rep(x, (1 << 10)) {
				dp[j][x] = cop[j][x];
			}
		}
	}
	int ans = 0;
	rep(x, (1 << 10)) {
		ans += dp[2 * n - 1][x];
		if (ans >= m)ans -= m;
	}
	cout << ans << endl;
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	solve();
	return 0;
}
