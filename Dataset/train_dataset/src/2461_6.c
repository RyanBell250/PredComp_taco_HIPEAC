#include <bits/stdc++.h>

using namespace std;

const int MAXN = 17;

long long dp[(1<<MAXN)];

int main() {
    #ifdef BLAT
        freopen("input", "r", stdin);
    #endif

   	int n;
   	cin >> n;

   	vector< vector< int > > v(n + 1, vector< int > (n + 1));

   	for(int i = 0; i < n; ++i) {
   		for(int j = 0; j < n; ++j) cin >> v[i][j];
   	}

   	for(int i = 0; i < n; ++i) {
   		for(int j = i + 1; j < n; ++j) {
   			for(int mask = 0; mask < (1<<n); ++mask) {
   				if((mask&(1<<i)) && (mask&(1<<j))) dp[mask] += v[i][j];
   			}
   		}
   	}

   	for(int mask = 0; mask < (1<<n); ++mask) {
   		for(int m = mask; m; --m &= mask) {
   			dp[mask] = max(dp[mask], dp[m] + dp[mask - m]);
   		}
   	} 

   	cout << dp[(1<<n) - 1] << '\n';
}   	