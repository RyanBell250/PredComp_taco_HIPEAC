#include <bits/stdc++.h>
using namespace std;
const int mo = 1000000007;
long long p[100010], p0[100010], s[1510], f[1510], pl[1510], pr[1510],
    d[100010], inv[100010], sl[1510];
int n, m, a, b, k;
long long quick(long long x, int y) {
  long long s = 1;
  while (y) {
    if (y & 1) s = s * x % mo;
    x = x * x % mo;
    y >>= 1;
  }
  return s;
}
long long c(int n, int m) { return d[n] * inv[m] % mo * inv[n - m] % mo; }
int main() {
  scanf("%d%d", &n, &m);
  scanf("%d%d", &a, &b);
  scanf("%d", &k);
  p[0] = p0[0] = 1;
  p[1] = 1ll * a * quick(b, mo - 2) % mo;
  p0[1] = 1ll * (b - a) * quick(b, mo - 2) % mo;
  for (int i = 2; i <= k; i++) {
    p0[i] = p0[i - 1] * p0[1] % mo;
    p[i] = p[i - 1] * p[1] % mo;
  }
  d[0] = inv[0] = 1;
  for (int i = 1; i <= k; i++) {
    d[i] = d[i - 1] * i % mo;
    inv[i] = quick(d[i], mo - 2);
  }
  for (int i = 1; i <= m; i++) {
    if (i - 1 > k) break;
    pl[i] = c(k, i - 1) * p[i - 1] % mo * p0[k - i + 1] % mo;
    pr[m - i + 1] = pl[i];
  }
  for (int i = 1; i <= m; i++) sl[i] = (sl[i - 1] + pl[i]) % mo;
  for (int i = 1; i <= m; i++) s[i] = (s[i - 1] + sl[i] * pr[i] % mo) % mo;
  for (int i = 2; i <= n; i++) {
    long long w = 0;
    for (int j = 1; j <= m; j++) {
      w = (w + pl[j] * s[j - 1] % mo) % mo;
      f[j] = (pr[j] * sl[j] % mo * (s[m] - s[m - j] + mo) % mo -
              w * pr[j] % mo + mo) %
             mo;
    }
    s[0] = 0;
    for (int j = 1; j <= m; j++) s[j] = (s[j - 1] + f[j]) % mo;
  }
  printf("%lld\n", s[m]);
}
