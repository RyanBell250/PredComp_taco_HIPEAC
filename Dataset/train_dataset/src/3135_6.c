#include <bits/stdc++.h>
using namespace std;
const int N = 10, M = 1e6 + 7, K = 200, p = 1e9 + 7;
int n, e[N], s[M], wf[K], q[N][K], f[N][N], ans[N][M];
bitset<40> op, wq[N][M];
unordered_map<bitset<40>, int> rt[N];
inline int read() {
  int num = 0;
  char g = getchar();
  while (g < 48 || 57 < g) g = getchar();
  while (47 < g && g < 58)
    num = (num << 1) + (num << 3) + g - 48, g = getchar();
  return num;
}
inline long long pows(long long u, int v) {
  long long ans = 1;
  while (v > 0) {
    if (v & 1) ans = ans * u % p;
    u = u * u % p, v = v >> 1;
  }
  return ans;
}
inline void find(int u) {
  q[u][0] = 0;
  int os = 0, of = 0;
  for (int i = 0; i < (1 << n); i++)
    if (s[i] == u) q[u][++q[u][0]] = i, wf[i] = ++os;
  for (int i = 1; i <= e[u - 1]; i++) {
    if (!ans[u - 1][i]) continue;
    for (int h = 1; h < (1 << n); h++) {
      long long opq = 1;
      for (int c = 0; c < n; c++)
        if ((1 << c) & h)
          opq = opq * f[u][c + 1] % p;
        else
          opq = opq * (1 - f[u][c + 1] + p) % p;
      bitset<40> c = wq[u - 1][i], hc = op;
      bool tg = 0;
      for (int x = 1; x <= q[u - 1][0]; x++) {
        if (c[x] == 1) {
          for (int t = 0; t < n; t++)
            if (((1 << t) & h) && (!(q[u - 1][x] & (1 << t)))) {
              hc[wf[q[u - 1][x] | (1 << t)]] = 1, tg = 1;
            }
        }
      }
      if (!tg) continue;
      int pos;
      if (rt[u][hc] == 0) rt[u][hc] = ++of, e[u]++, wq[u][e[u]] = hc;
      pos = rt[u][hc];
      ans[u][pos] = (ans[u][pos] + opq * ans[u - 1][i]) % p;
    }
  }
}
int main() {
  n = read();
  for (int i = 0; i <= (1 << n); i++) s[i] = __builtin_popcount(i);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) f[i][j] = read() * pows(100, p - 2) % p;
  q[0][0] = 1;
  e[0] = 1, ans[0][1] = 1, wq[0][1][1] = 1;
  for (int i = 1; i <= n; i++) find(i);
  cout << ans[n][1] << endl;
  return 0;
}
