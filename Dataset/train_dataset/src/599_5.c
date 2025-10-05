#include <bits/stdc++.h>
using namespace std;
struct timer {
  time_t start;
  timer() { start = clock(); }
  ~timer() {
    cerr << 1. * (clock() - start) / CLOCKS_PER_SEC << " secs" << endl;
  }
};
int n, m;
long long dp[2][2][2][155][155];
int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cin >> n >> m;
  long long ans = 0;
  int cur = 0, pre = 1;
  for (int i = 0; i < (n); i++)
    for (int j = i; j < (n); j++) {
      dp[cur][1][1][i][j] = 1;
      ans += m;
    }
  for (int ii = 0; ii < (m - 1); ii++) {
    swap(cur, pre);
    for (int L = 0; L < (2); L++)
      for (int R = 0; R < (2); R++)
        for (int l = 0; l < (n); l++)
          for (int r = 0; r < (n); r++) dp[cur][L][R][l][r] = 0;
    for (int L = 0; L < (2); L++)
      for (int R = 0; R < (2); R++)
        for (int l = 0; l < (n); l++)
          for (int r = l; r < (n); r++) {
            int from[4] = {0, l, l + 1, r + 1};
            int to[4] = {l, r, r + 1, n};
            for (int i = 0; i < (3); i++)
              for (int j = 0; j < (3); j++) {
                if (i == 0 && !L || j == 2 && !R) continue;
                int nL = i == 2 ? 0 : L;
                int nR = j == 0 ? 0 : R;
                dp[cur][nL][nR][from[i]][to[j]] += dp[pre][L][R][l][r];
                dp[cur][nL][nR][from[i + 1]][to[j]] +=
                    1000000007LL - dp[pre][L][R][l][r];
                dp[cur][nL][nR][from[i]][to[j + 1]] +=
                    1000000007LL - dp[pre][L][R][l][r];
                dp[cur][nL][nR][from[i + 1]][to[j + 1]] += dp[pre][L][R][l][r];
              }
          }
    for (int L = 0; L < (2); L++)
      for (int R = 0; R < (2); R++)
        for (int i = 0; i < (n); i++)
          for (int j = 0; j < (n); j++) {
            if (i == 0 && j == 0) {
            } else if (i == 0) {
              dp[cur][L][R][i][j] += dp[cur][L][R][i][j - 1];
            } else if (j == 0) {
              dp[cur][L][R][i][j] += dp[cur][L][R][i - 1][j];
            } else {
              dp[cur][L][R][i][j] += dp[cur][L][R][i][j - 1] +
                                     dp[cur][L][R][i - 1][j] + 1000000007LL -
                                     dp[cur][L][R][i - 1][j - 1];
            }
            dp[cur][L][R][i][j] %= 1000000007LL;
            if (i <= j) {
              ans += dp[cur][L][R][i][j] * (m - 1 - ii);
              ans %= 1000000007LL;
            }
          }
  }
  cout << ans;
}
