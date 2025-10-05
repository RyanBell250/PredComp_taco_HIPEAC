#include <bits/stdc++.h>
using namespace std;
const int N = 100;
int n, m, k, DP[2][N], dp[2][N][N], maxsum[N];
void fun(int idx, vector<int> &a) {
  memset(dp, -1, sizeof(dp));
  memset(maxsum, -1, sizeof(maxsum));
  dp[1][0][0] = 0;
  maxsum[0] = 0;
  for (int i = 0; i < m; ++i) {
    int f = i & 1;
    for (int sz = 0; sz <= m / 2; ++sz)
      for (int rem = 0; rem < k; ++rem) dp[f][sz][rem] = dp[1 - f][sz][rem];
    for (int sz = 0; sz < m / 2; ++sz) {
      for (int rem = 0; rem < k; ++rem) {
        if (dp[1 - f][sz][rem] != -1) {
          dp[f][sz + 1][(rem + a[i]) % k] =
              max(dp[1 - f][sz][rem] + a[i], dp[f][sz + 1][(rem + a[i]) % k]);
          maxsum[(rem + a[i]) % k] =
              max(maxsum[(rem + a[i]) % k], dp[f][sz + 1][(rem + a[i]) % k]);
        }
      }
    }
  }
  for (int i = 0; i < k; i++) DP[idx][i] = DP[1 - idx][i];
  for (int i = 0; i < k; i++) {
    if (maxsum[i] == -1) continue;
    for (int j = 0; j < k; ++j)
      if (DP[1 - idx][j] != -1)
        DP[idx][(j + i) % k] =
            max(DP[idx][(j + i) % k], DP[1 - idx][j] + maxsum[i]);
  }
}
int main() {
  memset(DP, -1, sizeof(DP));
  DP[1][0] = 0;
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    vector<int> a(m);
    for (int j = 0; j < m; ++j) cin >> a[j];
    fun(i & 1, a);
  }
  cout << DP[(n - 1) & 1][0];
  return 0;
}
