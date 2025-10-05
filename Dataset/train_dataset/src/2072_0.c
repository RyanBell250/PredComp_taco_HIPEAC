#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
int n, m, k, dp[2][51][101][101], now = 1, last = 0, C[101][101], ans;
void update(int &x, int y) { x = (x + y) % mod; }
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i <= 100; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
      if (C[i][j] > k) C[i][j] = k + 1;
    }
  }
  for (int i = 1; i * 2 <= n; i++) dp[now][i][i * 2][1] = 1;
  for (int i = 2; i <= m; i++) {
    last = now;
    now ^= 1;
    for (int j = 1; j * 2 <= n; j++)
      for (int p = j; p <= n; p++)
        for (int t = 1; t <= k; t++)
          if (dp[last][j][p][t]) {
            int &v = dp[last][j][p][t];
            update(ans, (long long)v * (m - i + 1) % mod);
            for (int next = 1; next * 2 + p <= n; ++next)
              if (t * C[j + next - 1][next] <= k)
                update(dp[now][next][p + next * 2][t * C[j + next - 1][next]],
                       v);
            v = 0;
          }
  }
  printf("%d\n", ans);
}
