#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, u, r, d[33], F[33][33];
  int a[33], b[33], k[33], p[33];
  long long res = -1000000000000000LL;
  scanf("%d%d%d", &n, &u, &r);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &k[i]);
  for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
  for (int i = 1; i <= n; i++) F[0][i] = a[i];
  d[0] = 0;
  if (u % 2 == 0) {
    long long s = 0;
    for (int i = 1; i <= n; i++) s += (long long)k[i] * F[0][i];
    if (s > res) res = s;
  }
  for (int j = 1; j <= u; j++) {
    d[j] = 0;
    for (int i = 1; i <= n; i++) F[j][i] = F[j - 1][p[i]] + r;
    if ((u - j) % 2 == 0) {
      long long s = 0;
      for (int i = 1; i <= n; i++) s += (long long)k[i] * F[j][i];
      if (s > res) res = s;
    }
  }
  bool stop;
  while (1) {
    stop = true;
    for (int j = u; j > 0; j--)
      if (d[j] == 0 && d[j - 1] == 0) {
        d[j] = 1;
        for (int i = 1; i <= n; i++) F[j][i] = F[j - 1][i] ^ b[i];
        if ((u - j) % 2 == 0) {
          long long s = 0;
          for (int i = 1; i <= n; i++) s += (long long)k[i] * F[j][i];
          if (s > res) res = s;
        }
        for (int t = j + 1; t <= u; t++) {
          d[t] = 0;
          for (int i = 1; i <= n; i++) F[t][i] = F[t - 1][p[i]] + r;
          if ((u - t) % 2 == 0) {
            long long s = 0;
            for (int i = 1; i <= n; i++) s += (long long)k[i] * F[t][i];
            if (s > res) res = s;
          }
        }
        stop = false;
        break;
      }
    if (stop) break;
  }
  printf("%I64d\n", res);
  return 0;
}
