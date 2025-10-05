#include <bits/stdc++.h>
using namespace std;
inline int Rd() {
  int s = 0;
  char fl = 0, c = getchar();
  while (c < '0' || c > '9') fl |= (c == '-'), c = getchar();
  while (c >= '0' && c <= '9')
    s = (s << 3) + (s << 1) + (c ^ 48), c = getchar();
  return fl ? -s : s;
}
const int N = 3e5 + 5;
const int mod = 998244353;
int to[N << 1], nxt[N << 1], h[N];
int dep[N], md[N], son[N], p[N][22], lg[N], top[N], len[N];
int rx[N], xr[N], base[N], inv[N];
char c[N];
vector<int> U[N], D[N];
int n, m, cnt;
inline void AddEdge(int x, int y) {
  to[++cnt] = y, nxt[cnt] = h[x], h[x] = cnt;
}
void DFS(int x) {
  dep[x] = md[x] = dep[p[x][0]] + 1;
  rx[x] = (rx[p[x][0]] * 31ll % mod + (c[x] - 'a' + 1)) % mod;
  xr[x] = (1ll * base[dep[x] - 1] * (c[x] - 'a' + 1) % mod + xr[p[x][0]]) % mod;
  for (int i = h[x]; i; i = nxt[i]) {
    int y = to[i];
    if (y == p[x][0]) continue;
    p[y][0] = x, DFS(y);
    if (md[y] > md[son[x]]) son[x] = y, md[x] = md[y];
  }
}
void DFS(int x, int tp) {
  top[x] = tp, len[x] = md[x] - dep[top[x]];
  if (son[x]) DFS(son[x], tp);
  for (int i = h[x]; i; i = nxt[i]) {
    int y = to[i];
    if (y == p[x][0] || y == son[x]) continue;
    DFS(y, y);
  }
}
inline void ST() {
  for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
  for (int j = 1; j <= lg[n]; j++)
    for (int i = 1; i <= n; i++) p[i][j] = p[p[i][j - 1]][j - 1];
  for (int i = 1; i <= n; i++)
    if (i == top[i]) {
      for (int x = i, j = 1; j <= len[i]; j++) x = p[x][0], U[i].push_back(x);
      for (int x = i, j = 1; j <= len[i]; j++) x = son[x], D[i].push_back(x);
    }
}
inline int LCA(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  for (int i = lg[dep[x] - dep[y]]; i >= 0; i--)
    if (dep[p[x][i]] >= dep[y]) x = p[x][i];
  if (x == y) return x;
  for (int i = lg[dep[x]]; i >= 0; i--)
    if (p[x][i] != p[y][i]) x = p[x][i], y = p[y][i];
  return p[x][0];
}
inline int Getkfa(int x, int k) {
  if (dep[x] <= k) return 0;
  if (!k) return x;
  x = p[x][lg[k]], k ^= (1 << lg[k]);
  if (!k) return x;
  if (dep[x] - dep[top[x]] == k) return top[x];
  if (dep[x] - dep[top[x]] > k) return D[top[x]][dep[x] - dep[top[x]] - k - 1];
  return U[top[x]][k - dep[x] + dep[top[x]] - 1];
}
inline int Getrx(int x, int fa) {
  return (rx[x] - 1ll * rx[fa] * base[dep[x] - dep[fa]] % mod + mod) % mod;
}
inline int Getxr(int x, int fa) {
  return 1ll * (xr[x] - xr[p[fa][0]] + mod) % mod * inv[dep[p[fa][0]]] % mod;
}
inline int Gethash(int x, int y, int z, int k) {
  if (k <= dep[x] - dep[z] + 1)
    y = Getkfa(x, k - 1), z = y;
  else
    y = Getkfa(y, (dep[x] + dep[y] - (dep[z] << 1) + 1) - k);
  return (1ll * Getxr(x, z) * base[dep[y] - dep[z]] % mod + Getrx(y, z)) % mod;
}
inline int qpow(int x, int y) {
  int res = 1;
  for (; y; y >>= 1) {
    if (y & 1) res = 1ll * res * x % mod;
    x = 1ll * x * x % mod;
  }
  return res;
}
int main() {
  n = Rd();
  scanf("%s", c + 1);
  base[0] = inv[0] = 1;
  int tmp = qpow(31ll, mod - 2);
  for (int i = 1; i <= n; i++)
    base[i] = base[i - 1] * 31ll % mod, inv[i] = 1ll * inv[i - 1] * tmp % mod;
  for (int i = 1; i < n; i++) {
    int x = Rd(), y = Rd();
    AddEdge(x, y), AddEdge(y, x);
  }
  rx[0] = xr[0] = 0;
  DFS(1);
  DFS(1, 1), ST();
  m = Rd();
  while (m--) {
    int la = Rd(), lb = Rd(), ra = Rd(), rb = Rd();
    if (c[la] != c[ra]) {
      puts("0");
      continue;
    }
    int lf = LCA(la, lb), rf = LCA(ra, rb);
    int l = 1,
        r = min(dep[la] + dep[lb] - (dep[lf] << 1) + 1,
                dep[ra] + dep[rb] - (dep[rf] << 1) + 1),
        res = 0;
    while (l <= r) {
      int mid = l + r >> 1;
      if (Gethash(la, lb, lf, mid) == Gethash(ra, rb, rf, mid))
        res = mid, l = mid + 1;
      else
        r = mid - 1;
    }
    printf("%d\n", res);
  }
  return 0;
}
