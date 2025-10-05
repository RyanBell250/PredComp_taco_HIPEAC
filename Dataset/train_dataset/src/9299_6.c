#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  double pr[101];
  for (int i = 0; i < (n + 1); i++) scanf("%lf", pr + i);
  static double dp[201][201];
  for (int i = 0; i < (201); i++)
    for (int j = 0; j < (201); j++) dp[i][j] = -1e77;
  dp[0][0] = 0;
  for (int i = 0; i < (2 * n + 1); i++) {
    for (int j = 0; j < (2 * n + 1); j++) {
      for (int k = 0; k < (n + 1); k++) {
        if (0 <= j + (n - 2 * k) && j + (n - 2 * k) <= 2 * n) {
          dp[i + 1][j + (n - 2 * k)] =
              max(dp[i + 1][j + (n - 2 * k)], dp[i][j] + pr[k]);
        }
      }
    }
  }
  double ans = 0;
  for (int m = 1; m <= 2 * n; m++) ans = max(ans, dp[m][0] / m);
  printf("%.9f\n", ans);
  return 0;
}
