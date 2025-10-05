#include <bits/stdc++.h>
using namespace std;
long long l[50007], s[50007], c[50007], dp[5007][5007];
int main() {
  long long n, m;
  cin >> n >> m;
  for (long long i = n; i >= 1; --i) {
    cin >> l[i];
  }
  for (long long i = n; i >= 1; --i) {
    cin >> s[i];
  }
  for (long long i = 1; i <= n + m; ++i) {
    cin >> c[i];
  }
  for (long long i = 0; i <= n + m; ++i) dp[i][0] = 0;
  for (long long j = 0; j <= n; ++j) dp[0][j] = 0;
  for (long long i = 1; i <= n + m; ++i)
    for (long long j = 1; j <= n; ++j) dp[i][j] = -INT_MAX;
  for (long long i = 1; i <= n; ++i) {
    for (long long j = n; j >= 1; --j) {
      dp[l[i]][j] = max(dp[l[i]][j], dp[l[i]][j - 1] + c[l[i]] - s[i]);
    }
    int k = n * 2;
    for (long long i2 = l[i]; i2 < n + m; ++i2) {
      k >>= 1;
      for (long long j = 0; j <= k; ++j) {
        dp[i2 + 1][j >> 1] =
            max(dp[i2 + 1][j >> 1], dp[i2][j] + (j >> 1) * c[i2 + 1]);
      }
    }
  }
  cout << dp[n + m][0];
  return 0;
}
