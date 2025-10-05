#include <bits/stdc++.h>
using namespace std;
const long long int N = 3e5 + 5;
vector<long long int> g[N], sz(N), par(N), ans(N, 0), temp, dep(N, 0);
vector<bool> vis(N, 0);
long long int fp(long long int x) {
  if (x == par[x]) return x;
  return par[x] = fp(par[x]);
}
void Union(long long int a, long long int b) {
  long long int pa = fp(a);
  long long int pb = fp(b);
  if (pa != pb) {
    if (sz[pa] < sz[pb]) swap(pa, pb);
    par[pb] = pa;
    sz[pa] += sz[pb];
    sz[pb] = 0;
    ans[pa] = max(
        ans[pb], max(ans[pa], (ans[pb] / 2 + ans[pa] / 2) + (ans[pb] % 2 == 1) +
                                  (ans[pa] % 2 == 1) + 1));
    ans[pb] = 0;
  }
  return;
}
void dfs(long long int v, long long int p) {
  temp.push_back(v);
  vis[v] = 1;
  dep[v] = dep[p] + 1;
  for (auto &it : g[v]) {
    if (it != p) dfs(it, v);
  }
  return;
}
int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  srand(time(NULL));
  long long int n, m, q;
  cin >> n >> m >> q;
  for (long long int i = 1; i <= n; i++) par[i] = i, sz[i] = 1;
  for (long long int i = 1; i <= m; i++) {
    long long int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
    Union(u, v);
  }
  dep[0] = -1;
  for (long long int i = 1; i <= n; i++) {
    if (!vis[i]) {
      dfs(i, 0);
      long long int maxi = 0;
      long long int id = i;
      for (auto &v : temp) {
        vis[v] = 0;
        if (maxi < dep[v]) maxi = dep[v], id = v;
        dep[v] = 0;
      }
      long long int p = fp(i);
      temp.clear();
      dfs(id, 0);
      maxi = 0;
      for (auto &v : temp) {
        if (maxi < dep[v]) maxi = dep[v];
      }
      ans[p] = maxi;
      temp.clear();
    }
  }
  while (q--) {
    long long int type;
    cin >> type;
    if (type == 1) {
      long long int v;
      cin >> v;
      cout << ans[fp(v)] << "\n";
    } else {
      long long int u, v;
      cin >> u >> v;
      Union(u, v);
    }
  }
}
