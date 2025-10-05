#include <bits/stdc++.h>
using namespace std;
const long long INF = 4e18;
const long long MAX = 1e5 + 5;
const long long MOD = 1e9 + 7;
int n, p, k;
bool a1[1010], a2[1010];
int tmp[2][1010][55][55];
auto dp = tmp[0];
auto pre = tmp[1];
int main() {
  cin >> n >> p >> k;
  int r;
  cin >> r;
  for (int i = 0; i < r; i++) {
    int x;
    cin >> x;
    a1[x] = 1;
  }
  int s;
  cin >> s;
  for (int i = 0; i < s; i++) {
    int x;
    cin >> x;
    a2[x] = 1;
  }
  if (p / 2 * k >= n) {
    int all = 0;
    for (int i = 1; i <= n; i++) all += (a1[i] || a2[i]);
    cout << all << '\n';
    return 0;
  }
  for (int j = 0; j <= p; j++)
    for (int l = 0; l < k; l++)
      for (int m = 0; m < k; m++) pre[j][l][m] = dp[j][l][m] = -2000;
  pre[0][0][0] = 0;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= p; j++) {
      for (int l = 0; l < k; l++) {
        for (int m = 0; m < k; m++) {
          if (m < k - 1 && l < k - 1)
            dp[j][l][m] =
                max(dp[j][l][m], pre[j][l + 1][m + 1] + (a1[i] || a2[i]));
          if (l == 0 && m < k - 1)
            dp[j][l][m] = max(dp[j][l][m], pre[j][0][m + 1] + a2[i]);
          if (m == 0 && l < k - 1)
            dp[j][l][m] = max(dp[j][l][m], pre[j][l + 1][0] + a1[i]);
          if (l == 0 && m == 0) dp[j][l][m] = max(dp[j][l][m], pre[j][0][0]);
        }
      }
      if (j) {
        for (int m = 0; m < k; m++)
          dp[j][0][k - 1] = max(dp[j][0][k - 1], pre[j - 1][0][m] + a2[i]);
        for (int l = 0; l < k - 1; l++)
          for (int m = 0; m < k; m++)
            dp[j][l][k - 1] =
                max(dp[j][l][k - 1], pre[j - 1][l + 1][m] + (a1[i] || a2[i]));
        for (int l = 0; l < k; l++)
          dp[j][k - 1][0] = max(dp[j][k - 1][0], pre[j - 1][l][0] + a1[i]);
        for (int m = 0; m < k - 1; m++)
          for (int l = 0; l < k; l++)
            dp[j][k - 1][m] =
                max(dp[j][k - 1][m], pre[j - 1][l][m + 1] + (a1[i] || a2[i]));
      }
      if (j > 1) {
        for (int l = 0; l < k; l++)
          for (int m = 0; m < k; m++)
            dp[j][k - 1][k - 1] =
                max(dp[j][k - 1][k - 1], pre[j - 2][l][m] += (a1[i] || a2[i]));
      }
    }
    for (int j = 0; j <= p; j++)
      for (int l = 0; l < k; l++)
        for (int m = 0; m < k; m++) pre[j][l][m] = -2000;
    swap(dp, pre);
  }
  for (int l = 0; l < k; l++)
    for (int m = 0; m < k; m++) ans = max(ans, pre[p][l][m]);
  cout << ans << '\n';
  return 0;
}
