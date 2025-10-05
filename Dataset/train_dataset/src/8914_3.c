#include <bits/stdc++.h>
using namespace std;
double dp[108][10008];
int nxt[108][10008];
int n, x, tot = 0;
int c[108];
double C(int n, int m) {
  double ret = 1;
  for (int i = n; i > m; --i) ret = ret * i;
  for (int i = 1; i <= n - m; ++i) ret /= i;
  return ret;
}
int main() {
  scanf("%d %d", &n, &x);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &c[i]);
    tot += c[i];
  }
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = i - 1; j >= 0; --j)
      for (int s = tot - c[i]; s >= 0; --s) dp[j + 1][s + c[i]] += dp[j][s];
  double ans = 0;
  for (int k = 0; k < n; ++k)
    for (int s = 0; s <= tot; ++s)
      ans += dp[k][s] / C(n, k) *
             min(1.0 * (tot - s) / (n - k), x / 2.0 * (2 * n - k) / (n - k));
  printf("%.10f\n", ans);
}
