#define _USE_MATH_DEFINES
#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <cfloat>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <time.h>
#include <vector>
#include <random>
using namespace std;

#define rep(i, N) for (int i = 0; i < N; i++)
#define pb push_back

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> i_i;
typedef pair<ll, int> ll_i;
typedef pair<int, ll> i_ll;
typedef pair<double, int> d_i;
typedef pair<ll, ll> ll_ll;
typedef pair<double, double> d_d;
struct edge { int v; ll w; };

const int MOD = 1000000007;
const int _MOD = 1000000009;
double EPS = 1e-10;
ll INF = INT_MAX / 2;

ll solve(int N, vector<int> lb, vector<int> ub) {
	map<int, ll> dp; dp[1] = 1;
	ll ans = 0;
	rep(t, 12) {
		map<int, ll> _dp;
		int cnt = 0;
		for (i_ll Sx: dp) {
			int S = Sx.first; ll x = Sx.second;
			rep(d, 10) {
				int _S = 0;
				rep(i, N) if (S>>i & 1) {
					if (lb[i] <= d && d <= ub[i])
						_S |= 1<<(i + 1);
					if (lb[i]/10 < d && d < ub[i]/10)
						_S |= 1<<(N+1 + i);
					if (d && d == lb[i]/10 && d < ub[i]/10)
						_S |= 1<<(N*2+1 + i);
					if (d && lb[i]/10 < d && d == ub[i]/10)
						_S |= 1<<(N*3+1 + i);
					if (d && d == lb[i]/10 && d == ub[i]/10)
						_S |= 1<<(N*4+1 + i);
				}
				rep(i, N) if (S>>(N+1 + i) & 1) {
					_S |= 1<<(i + 1);
				}
				rep(i, N) if (S>>(N*2+1 + i) & 1) {
					if (d >= lb[i]%10)
						_S |= 1<<(i + 1);
				}
				rep(i, N) if (S>>(N*3+1 + i) & 1) {
					if (d <= ub[i]%10)
						_S |= 1<<(i + 1);
				}
				rep(i, N) if (S>>(N*4+1 + i) & 1) {
					if (lb[i]%10 <= d && d <= ub[i]%10)
						_S |= 1<<(i + 1);
				}
				_dp[_S] += x;
			}
		}
		dp = _dp;
		for (i_ll Sx: dp) {
			int S = Sx.first; ll x = Sx.second;
			if (S>>N & 1) ans += x;
		}
	}
	return ans;
}

int main() {
	for (;;) {
		int N; cin >> N;
		if (!N) break;
		vector<int> lb(N), ub(N);
		rep(i, N) cin >> lb[i] >> ub[i];
		cout << solve(N, lb, ub) << endl;
	}
}