#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 5;
const long long int inf = 1e18 + 9;
long long int n;
vector<int> g[maxn];
std::vector<long long int> dist(maxn, 0);
std::vector<long long int> tree(maxn, 0);
std::vector<std::pair<int, long long int> > q[maxn];
std::vector<long long int> val(maxn);
void update_tree(int idx, long long int val) {
  while (idx < maxn) {
    tree[idx] += val;
    idx += idx & -idx;
  }
}
long long int node_value(int index) {
  long long int ans = 0;
  for (; index > 0; index -= index & -index) {
    ans += tree[index];
  }
  return ans;
}
void dfs(int u, int papa) {
  for (int i = 0; i < q[u].size(); i++) {
    int d = q[u][i].first + dist[u];
    long long int w = q[u][i].second;
    update_tree(dist[u], w);
    update_tree(d + 1, -w);
  }
  val[u] = node_value(dist[u]);
  for (int i = 0; i < g[u].size(); i++) {
    int v = g[u][i];
    if (v == papa) continue;
    dist[v] = dist[u] + 1;
    dfs(v, u);
  }
  for (int i = 0; i < q[u].size(); i++) {
    int d = q[u][i].first + dist[u];
    long long int w = q[u][i].second;
    update_tree(dist[u], -w);
    update_tree(d + 1, w);
  }
}
int main() {
  long long int m, x, y, v, d;
  scanf("%lld", &n);
  for (int i = 1; i < n; i++) {
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  scanf("%lld", &m);
  for (int i = 0; i < m; i++) {
    scanf("%lld %lld %lld", &v, &d, &x);
    if (d > n) d = n;
    q[v].push_back({d, x});
  }
  dist[1] = 1;
  dfs(1, 0);
  for (int i = 1; i <= n; i++) {
    printf("%lld ", val[i]);
  }
  return 0;
}
