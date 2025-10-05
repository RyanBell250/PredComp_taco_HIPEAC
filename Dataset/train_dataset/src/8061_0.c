#include <bits/stdc++.h>
using namespace std;
long long n, m, a, b, g[19][19], dp[1 << 19][19], ans;
int main() {
  scanf("%lld%lld", &n, &m);
  for (int i = 0; i < m; i++) {
    scanf("%lld%lld", &a, &b);
    g[--a][--b] = g[b][a] = 1;
    dp[(1 << a) | (1 << b)][max(a, b)] = 1;
  }
  for (int i = 1; i < 1 << n; i++) {
    int k = 0;
    while (!(i & (1 << k))) k++;
    for (int j = k + 1; j < n; j++)
      if (dp[i][j]) {
        if (g[j][k]) ans += dp[i][j];
        for (int p = k + 1; p < n; p++)
          if (g[p][j] && !(i & (1 << p))) dp[i | (1 << p)][p] += dp[i][j];
      }
  }
  printf("%lld\n", (ans - m) / 2);
}
