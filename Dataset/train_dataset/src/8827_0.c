#include <bits/stdc++.h>
using namespace std;
const int Maxn = 14;
int n, m, g[Maxn];
bool path[Maxn + 1][Maxn + 1][1 << Maxn | 1];
int pre[Maxn + 1][Maxn + 1][1 << Maxn | 1];
int dp[1 << Maxn | 1], last[1 << Maxn | 1][3];
int main(int argc, const char *argv[]) {
  ios_base ::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(12);
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    g[u] |= (1 << v);
    g[v] |= (1 << u);
  }
  for (int u = 0; u < n; ++u)
    for (int v = 0; v < n; ++v)
      if (g[u] & (1 << v)) path[u][v][0] = 1, pre[u][v][0] = u;
  for (int mask = 0; mask < (1 << n); ++mask)
    for (int u = 0; u < n; ++u) {
      if (mask & (1 << u)) continue;
      for (int v = 0; v < n; ++v) {
        if (mask & (1 << v)) continue;
        if (u == v) continue;
        if (!path[u][v][mask]) continue;
        for (int to = 0; to < n; ++to)
          if (g[v] & (1 << to)) {
            if (mask & (1 << to)) continue;
            if (to == pre[u][v][mask]) continue;
            if (path[u][to][mask | (1 << v)]) continue;
            path[u][to][mask | (1 << v)] = 1;
            pre[u][to][mask | (1 << v)] = v;
          }
      }
    }
  __builtin_memset(dp, 0x3f, sizeof dp), dp[1] = 0;
  for (int mask = 0; mask < (1 << n); ++mask)
    for (int smask = mask; smask; smask = smask - 1 & mask) {
      int pmask = smask ^ mask;
      int cnt = __builtin_popcount(smask) + 1;
      if (dp[pmask] + cnt >= dp[mask]) continue;
      for (int u = 0; u < n; ++u) {
        if (!(pmask & (1 << u))) continue;
        for (int v = 0; v < n; ++v) {
          if (!(pmask & (1 << v))) continue;
          if (path[u][v][smask])
            dp[mask] = dp[pmask] + cnt, last[mask][0] = smask,
            last[mask][1] = u, last[mask][2] = v;
        }
      }
    }
  cout << dp[(1 << n) - 1] << endl;
  int mask = (1 << n) - 1;
  while (mask != 1) {
    int pmask = last[mask][0], tmp;
    int u = last[mask][1], v = last[mask][2];
    for (mask ^= pmask; pmask; pmask ^= 1 << (v = tmp))
      cout << (tmp = pre[u][v][pmask]) + 1 << ' ' << v + 1 << endl;
    cout << u + 1 << ' ' << v + 1 << endl;
  }
  return 0;
}
