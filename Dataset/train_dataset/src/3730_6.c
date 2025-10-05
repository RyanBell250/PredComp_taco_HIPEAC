#include <bits/stdc++.h>
using namespace ::std;
const long long maxn = 1e5 + 500;
const long long maxs = 400;
const long long mod = 1e9 + 7;
long long dp[maxs][maxs];
long long dpp[maxs][maxs];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long n, m, x;
  cin >> n >> m >> x;
  x--;
  if (n > m) {
    cout << 0;
    return 0;
  }
  if (x == 0) {
    dp[0][0] = 0;
    dp[0][1] = 1;
    dp[1][0] = 1;
    dp[1][1] = 0;
  } else {
    dp[0][0] = 1;
    dp[0][1] = 1;
    dp[1][0] = 1;
    dp[1][1] = 0;
  }
  for (long long i = 1; i < m; i++) {
    if (x == i) {
      {
        long long j = 0;
        for (long long k = 0; k <= n; k++) {
          dpp[j + 1][k] = (dpp[j + 1][k] + dp[j][k]) % mod;
          dpp[j][k + 1] = (dpp[j][k + 1] + dp[j][k]) % mod;
        }
      }
      for (long long j = 1; j <= n; j++) {
        for (long long k = 0; k <= n; k++) {
          dpp[j + 1][k] = (dpp[j + 1][k] + dp[j][k]) % mod;
          dpp[j][k + 1] = (dpp[j][k + 1] + dp[j][k]) % mod;
        }
      }
    } else {
      {
        long long j = 0;
        for (long long k = 0; k <= n; k++) {
          dpp[j][k] = (dpp[j][k] + dp[j][k]) % mod;
          dpp[j + 1][k] = (dpp[j + 1][k] + dp[j][k]) % mod;
          dpp[j][k + 1] = (dpp[j][k + 1] + dp[j][k]) % mod;
        }
      }
      for (long long j = 1; j <= n; j++) {
        for (long long k = 0; k <= n; k++) {
          dpp[j][k] = (dpp[j][k] + dp[j][k]) % mod;
          dpp[j + 1][k] = (dpp[j + 1][k] + dp[j][k]) % mod;
          dpp[j - 1][k + 1] = (dpp[j - 1][k + 1] + dp[j][k]) % mod;
          dpp[j][k + 1] = (dpp[j][k + 1] + dp[j][k]) % mod;
        }
      }
    }
    for (long long j = 0; j <= n; j++) {
      for (long long k = 0; k < maxs; k++) {
        dp[j][k] = dpp[j][k];
        dpp[j][k] = 0;
      }
    }
  }
  long long ans = dp[0][n];
  for (long long i = 1; i <= n; i++) {
    ans *= i;
    ans %= mod;
  }
  cout << ans;
}
