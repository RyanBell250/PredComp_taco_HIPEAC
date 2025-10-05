#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
struct Edge {
  int u, v, w;
} e[N];
vector<int> g[N];
struct SegmentTree {
  int tg[N << 2], mx[N << 2][2];
  int l[N], r[N], rk[N], fa[N], dep[N], c[N], n;
  void build(int k, int l, int r) {
    tg[k] = 0;
    if (l == r) {
      mx[k][c[rk[l]]] = dep[rk[l]];
      mx[k][c[rk[l]] ^ 1] = 0;
      return;
    }
    int lk = k << 1, rk = k << 1 | 1, mid = (l + r) >> 1;
    build(lk, l, mid);
    build(rk, mid + 1, r);
    mx[k][0] = max(mx[lk][0], mx[rk][0]);
    mx[k][1] = max(mx[lk][1], mx[rk][1]);
  }
  void update(int a, int b, int k, int l, int r) {
    if (a > r || b < l) return;
    if (a <= l && r <= b) {
      tg[k] ^= 1;
      swap(mx[k][0], mx[k][1]);
      return;
    }
    int lk = k << 1, rk = k << 1 | 1, mid = (l + r) >> 1;
    if (tg[k]) {
      tg[k] = 0;
      tg[lk] ^= 1;
      tg[rk] ^= 1;
      swap(mx[lk][0], mx[lk][1]);
      swap(mx[rk][0], mx[rk][1]);
    }
    update(a, b, lk, l, mid);
    update(a, b, rk, mid + 1, r);
    mx[k][0] = max(mx[lk][0], mx[rk][0]);
    mx[k][1] = max(mx[lk][1], mx[rk][1]);
  }
  int query(int k) {
    int u = e[k].u, v = e[k].v;
    if (fa[u] == v) swap(u, v);
    update(l[v], r[v], 1, 1, n);
    return mx[1][0];
  }
  void dfs(int u, int f) {
    l[u] = ++n;
    fa[u] = f;
    rk[n] = u;
    for (auto i : g[u]) {
      int v = e[i].u ^ e[i].v ^ u;
      if (v == f) continue;
      dep[v] = dep[u] + 1;
      c[v] = c[u] ^ e[i].w;
      dfs(v, u);
    }
    r[u] = n;
  }
} tx, ty;
int n, m, x, y;
int main() {
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
    g[e[i].u].push_back(i);
    g[e[i].v].push_back(i);
  }
  tx.dep[1] = tx.c[1] = tx.n = 0;
  tx.dfs(1, 1);
  x = 1;
  for (int i = 1; i <= n; ++i)
    if (tx.dep[i] > tx.dep[x]) x = i;
  tx.dep[x] = tx.c[x] = tx.n = 0;
  tx.dfs(x, x);
  y = 1;
  for (int i = 1; i <= n; ++i)
    if (tx.dep[i] > tx.dep[y]) y = i;
  ty.dep[y] = ty.c[y] = ty.n = 0;
  ty.dfs(y, y);
  tx.build(1, 1, n);
  ty.build(1, 1, n);
  scanf("%d", &m);
  while (m--) {
    int o;
    scanf("%d", &o);
    printf("%d\n", max(tx.query(o), ty.query(o)));
  }
}
