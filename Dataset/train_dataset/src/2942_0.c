#include <bits/stdc++.h>
using namespace std;
long long a[55], dp[55][55], sum[55];
int main() {
  ios::sync_with_stdio(false);
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    sum[i] = sum[i - 1] + a[i];
  }
  long long mask = 0, ans = 0;
  for (int d = 62; d >= 0; d--) {
    mask = ans | ((long long)1 << d);
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= k; j++)
        for (int p = 0; p < i; p++)
          if (((sum[i] - sum[p]) & mask) == mask && dp[p][j - 1]) dp[i][j] = 1;
    if (dp[n][k]) ans |= ((long long)1 << d);
  }
  cout << ans << endl;
  return 0;
}
