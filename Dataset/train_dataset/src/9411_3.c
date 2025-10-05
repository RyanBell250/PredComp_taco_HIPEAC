#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
int n, m, k, a[22], b[22], l[1000005], r[1000005], p[22], f[1000005],
    dp[1048666], dp2[1048666];
void u(int &x, int y) {
  if (x > y) x = y;
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < k; ++i) scanf("%1d", a + i);
  for (int i = 0; i < k; ++i) scanf("%1d", b + i);
  for (int i = 1; i <= n; ++i) scanf("%d%d", l + i, r + i), --l[i], --r[i];
  for (int i = 0; i < k; ++i) p[i] = i;
  for (int i = 0; i < (1 << k); ++i) dp[i] = n + 1;
  for (int i = n; i; --i) {
    swap(p[l[i]], p[r[i]]);
    int o = 0;
    for (int i = 0; i < k; ++i)
      if (a[i]) o ^= (1 << p[i]);
    dp[o] = i;
    o = 0;
    for (int i = 0; i < k; ++i)
      if (b[i]) o ^= (1 << p[i]);
    f[i] = o;
  }
  for (int i = 0; i < k; ++i)
    if (b[i]) f[n + 1] ^= (1 << i);
  int _ = 0;
  while (1) {
    for (int i = m + 1; i <= n + 1; ++i) {
      if (dp[f[i]] <= i - m) {
        printf("%d\n%d %d\n", k - _, dp[f[i]], i - 1);
        return 0;
      }
    }
    ++_;
    for (int i = 0; i < (1 << k); ++i) dp2[i] = dp[i];
    for (int i = 0; i < (1 << k); ++i) {
      for (int j = (1 << (k - 1)); j; j >>= 1) u(dp2[i], dp[i ^ j]);
    }
    for (int i = 0; i < (1 << k); ++i) dp[i] = dp2[i];
  }
  return 0;
}
