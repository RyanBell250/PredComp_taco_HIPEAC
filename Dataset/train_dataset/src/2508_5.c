#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0') ch == '-' && (f = 0) || (ch = getchar());
  while (ch <= '9' && ch >= '0')
    x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
  return f ? x : -x;
}
long long dp[13][1 << 13];
int ex[13], ey[13];
int ax[102], ay[102], az[102];
int n, m, q;
bool mp[13][13];
inline bool in(int x, int s) { return s & (1 << x); }
long long dfs(int u, int mask) {
  long long &res = dp[u][mask];
  if (~res) return res;
  res = 0;
  mask ^= 1 << u;
  int pos = 0;
  while (pos < n) {
    if (in(pos, mask))
      break;
    else
      ++pos;
  }
  for (int submask = mask; submask; submask = (submask - 1) & mask) {
    if (in(pos, submask)) {
      int flag = 1, cnt = 0;
      for (int i = 1; i <= q; ++i) {
        if (az[i] == u && in(ax[i], submask) && in(ay[i], submask)) {
          flag = 0;
          break;
        }
      }
      for (int i = 1; i <= q; ++i) {
        if (in(az[i], submask) &&
            (!in(ax[i], submask) || !in(ay[i], submask))) {
          flag = 0;
          break;
        }
      }
      for (int i = 1; i <= m; ++i) {
        if (ex[i] != u && ey[i] != u &&
            (in(ex[i], submask) ^ in(ey[i], submask))) {
          flag = 0;
          break;
        }
      }
      int v = 0;
      for (int i = 0; i < n; ++i) {
        if (mp[u][i] && in(i, submask)) {
          ++cnt;
          v = i;
        }
      }
      if (!flag || cnt > 1) continue;
      if (cnt == 1) {
        res += dfs(v, submask) * dfs(u, mask ^ submask ^ (1 << u));
      } else {
        for (v = 0; v < n; ++v) {
          if (in(v, submask)) {
            res += dfs(v, submask) * dfs(u, mask ^ submask ^ (1 << u));
          }
        }
      }
    }
  }
  return res;
}
int main(int argc, char const *argv[]) {
  n = read(), m = read(), q = read();
  for (int i = 1; i <= m; ++i) {
    ex[i] = read() - 1;
    ey[i] = read() - 1;
    mp[ex[i]][ey[i]] = 1;
    mp[ey[i]][ex[i]] = 1;
  }
  for (int i = 1; i <= q; ++i) {
    ax[i] = read() - 1;
    ay[i] = read() - 1;
    az[i] = read() - 1;
  }
  memset(dp, -1, sizeof dp);
  for (int i = 0; i < n; ++i) dp[i][1 << i] = 1;
  printf("%lld\n", dfs(0, (1 << n) - 1));
  return 0;
}
