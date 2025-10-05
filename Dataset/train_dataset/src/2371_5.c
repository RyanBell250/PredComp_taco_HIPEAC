#include <bits/stdc++.h>
using namespace std;
const int maxn = 25;
int a[25], b[25];
long long dp[25][25];
struct mat {
  long long a[maxn][maxn];
} ans;
mat mul(mat m1, mat m2) {
  mat res;
  for (int i = 0; i < maxn; ++i) {
    for (int j = 0; j < maxn; ++j) {
      res.a[i][j] = 0x3f3f3f3f3f3f3f3fLL;
      for (int k = 0; k < maxn; ++k) {
        res.a[i][j] = min(res.a[i][j], m1.a[i][k] + m2.a[k][j]);
      }
    }
  }
  return res;
}
mat qmod(mat m1, int num) {
  mat res;
  for (int i = 0; i < maxn; ++i) {
    res.a[i][i] = 0;
    for (int j = 0; j < maxn; ++j)
      if (i != j) res.a[i][j] = 0x3f3f3f3f3f3f3f3fLL;
  }
  while (num) {
    if (num & 1) res = mul(res, m1);
    m1 = mul(m1, m1);
    num >>= 1;
  }
  return res;
}
int main() {
  int n;
  int m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < n; i++) scanf("%d", &b[i]);
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = 0x3f3f3f3f;
    }
  }
  mat ans;
  for (int i = 0; i < maxn; ++i) {
    for (int j = 0; j < maxn; ++j) {
      ans.a[i][j] = 0x3f3f3f3f3f3f3f3fLL;
    }
  }
  for (int k = 0; k <= n; k++) {
    for (int i = 0; i <= n + 1; i++) {
      for (int j = 0; j <= n + 1; j++) {
        dp[i][j] = 0x3f3f3f3f3f3f3f3fLL;
      }
    }
    dp[0][k] = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= n; j++) {
        if (j > 0) dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - 1] + a[i]);
        dp[i + 1][j] = min(dp[i + 1][j], dp[i][j + 1] + b[i]);
      }
    }
    for (int i = 0; i <= n; i++) {
      ans.a[k][i] = dp[n][i];
    }
  }
  printf("%lld\n", qmod(ans, m).a[0][0]);
  return 0;
}
