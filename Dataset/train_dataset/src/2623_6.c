#include <bits/stdc++.h>
int a[705][705], b[705][705], c[705][705], u, v, n, m, d[705];
long long ans;
int main() {
  scanf("%d %d", &n, &m);
  for (int i = (1); i <= (m); ++i) {
    scanf("%d %d", &u, &v);
    ++a[u][v];
    ++a[v][u];
    ++d[u];
    ++d[v];
  }
  for (int i = (1); i <= (n); ++i)
    for (int j = (1); j <= (n); ++j)
      for (int k = (1); k <= (n); ++k) b[i][j] += (a[i][k] * a[k][j]);
  for (int i = (1); i <= (n); ++i)
    for (int j = (1); j <= (n); ++j)
      for (int k = (1); k <= (n); ++k) c[i][j] += (a[i][k] * b[k][j]);
  for (int i = (1); i <= (n); ++i)
    for (int j = (1); j <= (n); ++j) ans += b[i][j] * c[i][j];
  ans /= 10;
  for (int i = (1); i <= (n); ++i)
    for (int j = (1); j <= (i); ++j)
      if (a[i][j])
        for (int k = (1); k <= (j); ++k) {
          if (!(a[i][k] && a[j][k])) continue;
          ans -= d[i] + d[j] + d[k] - 3;
        }
  printf("%lld\n", ans);
  return 0;
}
