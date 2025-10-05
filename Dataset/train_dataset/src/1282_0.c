#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
int n, m, k, par[maxn], h[maxn], p[maxn], bound[maxn], ga[maxn], gb[maxn],
    fa[maxn], fb[maxn], w[maxn];
bool marked[maxn];
vector<int> g[maxn], newVers;
int root(int v) { return (par[v] == v ? v : par[v] = root(par[v])); }
void merge(int v, int u) {
  v = root(v);
  u = root(u);
  if (v == u) return;
  par[v] = u;
}
void dfs(int v) {
  newVers.push_back(v);
  for (int u : g[v]) {
    if (u != p[v]) {
      h[u] = h[v] + 1;
      p[u] = v;
      dfs(u);
    }
  }
}
int main() {
  cin >> n >> k >> m;
  for (int i = 1; i <= n; i++) par[i] = i;
  for (int i = 0; i < k; i++) {
    scanf("%d%d", &ga[i], &gb[i]);
    merge(ga[i], gb[i]);
  }
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &fa[i], &fb[i], &w[i]);
    if (root(fa[i]) != root(fb[i])) {
      marked[i] = true;
      merge(fa[i], fb[i]);
    }
  }
  for (int i = 1; i <= n; i++) par[i] = i;
  for (int i = 0; i < m; i++) {
    if (marked[i]) merge(fa[i], fb[i]);
  }
  for (int i = 0; i < k; i++) {
    ga[i] = root(ga[i]);
    gb[i] = root(gb[i]);
    g[ga[i]].push_back(gb[i]);
    g[gb[i]].push_back(ga[i]);
  }
  for (int i = 0; i < m; i++) {
    fa[i] = root(fa[i]);
    fb[i] = root(fb[i]);
  }
  for (int i = 1; i <= n; i++) par[i] = i;
  dfs(ga[0]);
  memset(bound, 0x3f, sizeof bound);
  for (int i = 0; i < m; i++) {
    int v = root(fa[i]), u = root(fb[i]);
    while (v != u) {
      if (h[v] < h[u]) swap(v, u);
      bound[v] = w[i];
      par[v] = root(p[v]);
      v = par[v];
    }
  }
  long long ans = 0;
  int inf = 1e9;
  for (int v : newVers)
    if (v != ga[0]) {
      if (bound[v] > inf) {
        cout << -1 << endl;
        return 0;
      }
      ans += 1LL * bound[v];
    }
  cout << ans << endl;
  return 0;
}
