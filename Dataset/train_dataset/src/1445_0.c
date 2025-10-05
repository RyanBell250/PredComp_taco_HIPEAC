#include <bits/stdc++.h>
using namespace std;
int n, k, a[16], b[16];
bitset<2005> f[1 << 16];
bool vis[16];
void solve(int s, int i) {
  if (!(s & (s - 1))) return;
  for (int u = 0; u <= n - 1; ++u)
    if (s >> u & 1 && a[u] < i && f[s ^ (1 << u)][i - a[u]]) {
      solve(s ^ (1 << u), i - a[u]);
      return;
    }
  solve(s, i * k);
  for (int u = 0; u <= n - 1; ++u)
    if (s >> u & 1) ++b[u];
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i <= n - 1; ++i) scanf("%d", a + i);
  for (int i = 0; i <= n - 1; ++i) f[1 << i][a[i]] = 1;
  for (int s = 1; s <= (1 << n) - 1; ++s)
    if (s & (s - 1)) {
      int z = 0;
      for (int u = 0; u <= n - 1; ++u)
        if (s >> u & 1) {
          z += a[u];
          f[s] |= f[s ^ (1 << u)] << a[u];
        }
      for (int i = z / k; i >= 1; --i)
        if (f[s][i * k]) f[s][i] = 1;
    }
  if (!f[(1 << n) - 1][1]) return puts("NO"), 0;
  puts("YES");
  solve((1 << n) - 1, 1);
  for (int T = 1; T <= n - 1; ++T) {
    int mx = 0;
    for (int i = 0; i <= n - 1; ++i)
      if (!vis[i]) mx = max(mx, b[i]);
    int x = -1, y = -1;
    for (int i = 0; i <= n - 1; ++i)
      if (!vis[i] && mx == b[i]) {
        if (!~x)
          x = i;
        else if (!~y)
          y = i;
      }
    printf("%d %d\n", a[x], a[y]);
    vis[y] = 1;
    a[x] += a[y];
    while (a[x] % k == 0) a[x] /= k, --b[x];
  }
  return 0;
}
