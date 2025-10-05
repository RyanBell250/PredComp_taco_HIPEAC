#include <bits/stdc++.h>
 
#define ll long long
 
using namespace std;
 
int a[16][16];
int n;
ll cost[1 << 16];
ll dp[1 << 16];
 
ll go(int gr, int mask) {
	
}
 
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for (int mask = 0; mask < (1 << n); mask++) {
		vector < int > res;
		for (int j = 0; j < n; j++) {
			if ((mask >> j) & 1) {
				res.push_back(j);
			}
		}
		for (int i = 0; i < res.size(); i++) {
			for (int j = i + 1; j < res.size(); j++) {
				dp[mask] += a[res[i]][res[j]];
			}
		}
	}
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = mask; i > 0; i = mask & (i - 1)) {
			dp[mask] = max(dp[mask], dp[mask ^ i] + dp[i]);
		}
	}
	cout << dp[(1 << n) - 1];
}