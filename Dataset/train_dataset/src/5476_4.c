#include <bits/stdc++.h>
using namespace std;
vector<int> g[100010], cc[100010];
vector<long long> pref_cc[100010];
int color[100010], dp1[100010], dp2[100010], dp[100010], best[100010], cnt;
void dfs1(int v, int p) {
  color[v] = cnt;
  for (int u : g[v])
    if (u != p) {
      dfs1(u, v);
      if (dp1[u] + 1 >= dp1[v]) {
        dp2[v] = dp1[v];
        dp1[v] = dp1[u] + 1;
      } else
        dp2[v] = max(dp2[v], dp1[u] + 1);
    }
}
void dfs2(int v, int p, int up = 0) {
  dp[v] = max(up, dp1[v]);
  best[color[v]] = max(best[color[v]], dp[v]);
  for (int u : g[v])
    if (u != p) dfs2(u, v, max(up, dp1[v] == dp1[u] + 1 ? dp2[v] : dp1[v]) + 1);
}
int bin_search(const vector<int> &v, int key) {
  int r(v.size()), l(-1);
  while (l + 1 < r)
    if (v[(l + r) >> 1] > key)
      r = (l + r) >> 1;
    else
      l = (l + r) >> 1;
  return r;
}
map<int, float> was[100010];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  fixed(cout);
  cout << setprecision(15);
  int n, m, q;
  cin >> n >> m >> q;
  for (int u, v; m; --m) {
    cin >> u >> v;
    g[v].push_back(u);
    g[u].push_back(v);
  }
  for (int i(1); i <= n; ++i) {
    if (!color[i]) {
      ++cnt;
      dfs1(i, 0);
      dfs2(i, 0);
    }
    cc[color[i]].push_back(dp[i]);
  }
  for (int i(1); i <= cnt; ++i) {
    sort((cc[i]).begin(), (cc[i]).end());
    pref_cc[i].resize(cc[i].size());
    pref_cc[i][0] = cc[i][0];
    for (int j(1); j < cc[i].size(); ++j)
      pref_cc[i][j] = pref_cc[i][j - 1] + cc[i][j];
  }
  for (int u, v; q; --q) {
    cin >> u >> v;
    u = color[u];
    v = color[v];
    if (u == v) {
      cout << "-1\n";
      continue;
    }
    if (cc[u].size() > cc[v].size()) swap(u, v);
    if (!was[u].count(v)) {
      float sum(0);
      int cur(max(best[u], best[v]));
      for (int z : cc[u]) {
        int p = bin_search(cc[v], cur - z - 1);
        sum += (float)p * cur + ((float)z + 1) * (cc[v].size() - p) +
               pref_cc[v][cc[v].size() - 1] - (p ? pref_cc[v][p - 1] : 0);
      }
      was[u][v] = sum / ((float)cc[v].size() * cc[u].size());
    }
    cout << was[u][v] << '\n';
  }
}
