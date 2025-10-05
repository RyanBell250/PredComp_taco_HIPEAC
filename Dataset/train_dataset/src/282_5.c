#include <bits/stdc++.h>
const int N = 3e5 + 5;
struct Query {
  int u, v, lca;
  long long ans;
};
int n, m, depth[N], par[N][20];
long long dp[N], val[N], a[N], bit[N];
std::vector<std::pair<int, int> > g[N];
std::vector<int> q[N];
std::vector<Query> ans;
std::map<std::pair<int, int>, long long> dto;
void add(int x, long long val) {
  for (; x <= n; x += x & -x) bit[x] += val;
}
long long sum(int x) {
  long long res = 0;
  for (; x; x -= x & -x) res += bit[x];
  return res;
}
void dfs1(int u, int fa, int dep) {
  par[u][0] = fa;
  depth[u] = dep;
  dp[u] = a[u];
  for (std::pair<int, int> &v : g[u]) {
    if (v.first == fa) continue;
    dfs1(v.first, u, dep + 1);
    dp[u] += std::max(0LL, dp[v.first] - 2LL * v.second);
    dto[std::pair<int, int>(u, v.first)] =
        std::max(0LL, dp[v.first] - 2LL * v.second);
  }
}
void dfs2(int u, int fa) {
  for (std::pair<int, int> &v : g[u]) {
    if (v.first == fa) continue;
    dp[u] -= dto[std::pair<int, int>(u, v.first)];
    dp[v.first] += std::max(0LL, dp[u] - 2LL * v.second);
    dto[std::pair<int, int>(v.first, u)] =
        std::max(0LL, dp[u] - 2LL * v.second);
    dfs2(v.first, u);
    dp[u] += dto[std::pair<int, int>(u, v.first)];
  }
}
void pr() {
  int k = 0;
  while (1 << (k + 1) <= n) k++;
  for (int i = 1; i <= k; i++)
    for (int j = 1; j <= n; j++) par[j][i] = par[par[j][i - 1]][i - 1];
}
int LCA(int u, int v) {
  if (depth[u] < depth[v]) std::swap(u, v);
  int t = depth[u] - depth[v];
  for (int i = 0; 1 << i <= t; i++)
    if (t >> i & 1) u = par[u][i];
  if (u == v) return u;
  for (int i = 19; ~i; i--)
    if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
  return par[u][0];
}
void dfs3(int u, int fa) {
  long long tmp = dto[std::pair<int, int>(u, fa)];
  add(depth[u], dp[u] - tmp - val[depth[u]]);
  val[depth[u]] = dp[u] - tmp;
  for (int v : q[u]) {
    int lca = ans[v].lca;
    ans[v].ans += sum(depth[u]) - sum(depth[lca] - 1);
  }
  for (std::pair<int, int> &v : g[u]) {
    if (v.first == fa) continue;
    tmp = dto[std::pair<int, int>(u, v.first)] + v.second;
    add(depth[u], -tmp);
    dfs3(v.first, u);
    add(depth[u], tmp);
  }
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%lld", a + i);
  int u, v, w;
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    g[u].push_back(std::pair<int, int>(v, w));
    g[v].push_back(std::pair<int, int>(u, w));
  }
  dfs1(1, 0, 1);
  dfs2(1, 0);
  pr();
  while (m--) {
    scanf("%d%d", &u, &v);
    int lca = LCA(u, v);
    if (lca != u) q[u].push_back(int(ans.size()));
    if (lca != v) q[v].push_back(int(ans.size()));
    ans.push_back((Query){u, v, lca, 0});
  }
  dfs3(1, 0);
  for (Query &t : ans) {
    if (t.u == t.v)
      t.ans = dp[t.u];
    else if (t.lca != t.u && t.lca != t.v)
      t.ans -= dp[t.lca] - 2LL * dto[std::pair<int, int>(t.lca, par[t.lca][0])];
    else
      t.ans += dto[std::pair<int, int>(t.lca, par[t.lca][0])];
    printf("%lld\n", t.ans);
  }
  return 0;
}
