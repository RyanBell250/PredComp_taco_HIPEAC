#include <bits/stdc++.h>
using namespace std;
const int maxn = 50, maxm = 5e3 + 100;
int n, lim, f[maxn + 3], s[maxn + 3];
double p[maxn + 3], q[maxn + 3], dp[maxn + 3][maxm + 3];
bool check(double x) {
  for (int i = n; i; i--) {
    for (int j = lim + 1; j <= lim + 100; j++) {
      dp[i + 1][j] = x;
    }
    for (int j = 0; j <= lim; j++) {
      dp[i][j] = min(x, (dp[i + 1][j + f[i]] + f[i]) * p[i] +
                            (dp[i + 1][j + s[i]] + s[i]) * q[i]);
    }
  }
  return dp[1][0] == x;
}
int main() {
  scanf("%d %d", &n, &lim);
  for (int i = 1, x; i <= n; i++) {
    scanf("%d %d %d", &f[i], &s[i], &x);
    p[i] = x / 100., q[i] = (100 - x) / 100.;
  }
  double l = 0, r = 1e9, mid;
  for (int k = 0; k < 70; k++) {
    mid = (l + r) / 2;
    if (check(mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  printf("%.12lf\n", (l + r) / 2);
  return 0;
}
