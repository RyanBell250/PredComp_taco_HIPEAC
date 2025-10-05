#include <bits/stdc++.h>
using namespace std;
const int N = 405, K = 5005, inf = 1e9 + 7;
int n, m, k, t, S, T, tot;
int de[N], hd[N], dis[N], fl[N], pre[N];
bool vis[N];
struct point {
  int x, y, c;
} a[K];
struct edge {
  int n, v, flow, w;
} e[K << 2];
void add(int u, int v, int flow, int w) {
  e[++tot] = (edge){hd[u], v, flow, w}, hd[u] = tot;
  e[++tot] = (edge){hd[v], u, 0, -w}, hd[v] = tot;
}
bool SPFA() {
  memset(fl + 1, 0, T << 2), memset(dis + 1, 63, T << 2), memset(vis + 1, 0, T);
  queue<int> Q;
  Q.push(S);
  fl[S] = inf, dis[S] = 0;
  int u;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    for (int i = hd[u]; i; i = e[i].n)
      if (e[i].flow && dis[e[i].v] > dis[u] + e[i].w) {
        dis[e[i].v] = dis[u] + e[i].w;
        pre[e[i].v] = i, fl[e[i].v] = min(fl[u], e[i].flow);
        if (!vis[e[i].v]) Q.push(e[i].v), vis[e[i].v] = 1;
      }
    vis[u] = 0;
  }
  if (!fl[T]) return 0;
  u = T;
  int nf = fl[T];
  while (u ^ S) {
    e[pre[u]].flow -= nf, e[pre[u] ^ 1].flow += nf;
    u = e[pre[u] ^ 1].v;
  }
  return 1;
}
void solve(int nt) {
  tot = 1;
  memset(hd + 1, 0, T << 2);
  for (int i = 1; i <= k; ++i)
    if (!a[i].c) add(a[i].x, n + a[i].y, 1, 0);
  for (int i = 1; i <= n; ++i)
    if (de[i]) add(S, i, de[i] / nt, 0), (de[i] % nt && (add(S, i, 1, 1), 1));
  for (int i = 1; i <= m; ++i)
    if (de[i + n])
      add(i + n, T, de[i + n] / nt, 0),
          (de[i + n] % nt && (add(i + n, T, 1, 1), 1));
  while (SPFA())
    ;
  int now = 2;
  for (int i = 1; i <= k; ++i)
    if (!a[i].c)
      (!e[now].flow && (a[i].c = nt, de[a[i].x]--, de[a[i].y + n]--, 1)),
          now += 2;
}
int main() {
  cin >> n >> m >> k >> t;
  for (int i = 1; i <= k; ++i)
    cin >> a[i].x >> a[i].y, de[a[i].x]++, de[a[i].y + n]++;
  S = n + m + 1, T = n + m + 2;
  int ans = 0;
  for (int i = 1; i <= n + m; ++i) ans += (de[i] % t != 0);
  cout << ans << '\n';
  for (int i = t; i >= 1; --i) solve(i);
  for (int i = 1; i <= k; ++i) cout << a[i].c << ' ';
  return 0;
}
