#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int const N = 100 * 1000 + 16;
int const M = 1000 * 1000 * 1000 + 7;
int n, root;
int e, dist[N], tour[N], tin[N], tout[N];
int a[N];
vector<int> g[N];
vector<int> fl[1 << 18];
vector<int> fr[1 << 18];
vector<pair<int, int>> t[1 << 18];
void dfs(int u, int p) {
  dist[u] = dist[p] + 1;
  tin[u] = e;
  tour[e++] = u;
  for (int v : g[u])
    if (v != p) dfs(v, u);
  tout[u] = e - 1;
}
void build(int i, int l, int r) {
  if (l == r) {
    t[i].emplace_back(dist[tour[l]], a[tour[l]]);
    return;
  }
  int m = (l + r) >> 1;
  build(i << 1, l, m);
  build(i << 1 | 1, m + 1, r);
  int len = r - l + 1;
  t[i].resize(len);
  merge(t[i << 1].begin(), t[i << 1].end(), t[i << 1 | 1].begin(),
        t[i << 1 | 1].end(), t[i].begin());
  for (int j = 1; j < len; ++j)
    t[i][j].second = min(t[i][j].second, t[i][j - 1].second);
  int idx;
  int len_left = m - l + 1;
  int len_right = len - len_left;
  idx = 0;
  fl[i].resize(len, -1);
  for (int j = 0; j < len; ++j) {
    int x = t[i][j].first;
    while (idx < len_left && t[i << 1][idx].first <= x) ++idx;
    fl[i][j] = idx - 1;
  }
  idx = 0;
  fr[i].resize(len, -1);
  for (int j = 0; j < len; ++j) {
    int x = t[i][j].first;
    while (idx < len_right && t[i << 1 | 1][idx].first <= x) ++idx;
    fr[i][j] = idx - 1;
  }
}
int ql, qr;
int query(int i, int L, int R, int k) {
  if (ql <= L && R <= qr) return t[i][k].second;
  int m = (L + R) >> 1;
  int ans = M;
  if (ql <= m && fl[i][k] >= 0) ans = query(i << 1, L, m, fl[i][k]);
  if (m < qr && fr[i][k] >= 0)
    ans = min(ans, query(i << 1 | 1, m + 1, R, fr[i][k]));
  return ans;
}
int query(int u, int k) {
  ql = tin[u];
  qr = tout[u];
  int idx =
      lower_bound(t[1].begin(), t[1].end(), make_pair(k + dist[u] + 1, 0)) -
      t[1].begin();
  return query(1, 0, n - 1, idx - 1);
}
int main() {
  cin.tie(0);
  cin.sync_with_stdio(0);
  cin >> n >> root;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
  }
  dfs(root, 0);
  build(1, 0, n - 1);
  int m;
  cin >> m;
  int last = 0;
  while (m--) {
    int p, q;
    cin >> p >> q;
    int x = (p + last) % n + 1;
    int k = (q + last) % n;
    last = query(x, k);
    cout << last << "\n";
  }
}
