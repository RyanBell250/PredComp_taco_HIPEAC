#include <bits/stdc++.h>
using namespace std;
int n, s, m;
int pos[55];
int dis[55][55], deg[55];
int dp[55][55];
int leaves;
vector<int> leaf;
vector<int> tmp;
vector<int> g[55], hasleaf[55];
int haster[55], up[55];
void buildtree(int x, int fa, int rt) {
  if (rt != -1) {
    up[x] = rt;
    if (deg[x] == 1) hasleaf[rt].push_back(x);
    if (rt != x) haster[rt] += haster[x];
  }
  for (int i = 0; i < g[x].size(); i++) {
    if (g[x][i] != fa) buildtree(g[x][i], x, rt == -1 ? g[x][i] : rt);
  }
}
bool check(int tim, int rt, int lft) {
  int sum = 0;
  for (int ii = 0; ii < leaves; ii++) {
    int i = leaf[ii];
    if (i == rt) continue;
    for (int j = lft; j; j--) {
      if (dis[rt][i] + dp[i][lft - j] >= tim) {
        sum += j;
        break;
      }
    }
  }
  return sum >= lft;
}
bool final(int tim) {
  for (int i = 0; i < g[s].size(); i++) {
    int rt = g[s][i];
    int sum = 0;
    for (int j = 0; j < hasleaf[rt].size(); j++) {
      int le = hasleaf[rt][j];
      for (int k = haster[rt]; k; k--) {
        if (dis[s][le] + dp[le][m - k] >= tim) {
          sum += k;
          break;
        }
      }
    }
    if (sum < haster[rt]) return 0;
  }
  return true;
}
int main() {
  cin >> n;
  int u, v, w;
  memset(dis, 0x3f, sizeof(dis));
  for (int i = 1; i < n; i++) {
    cin >> u >> v >> w;
    g[u].emplace_back(v);
    g[v].emplace_back(u);
    dis[u][v] = dis[v][u] = w;
    deg[u]++;
    deg[v]++;
  }
  for (int i = 1; i <= n; i++)
    if (deg[i] == 1) {
      leaves++;
      leaf.emplace_back(i);
    }
  cin >> s;
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> pos[i];
    haster[pos[i]]++;
  }
  for (int i = 1; i <= n; i++) dis[i][i] = 0;
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      if (i != k && dis[i][k] < 0x3f3f3f3f)
        for (int j = 1; j <= n; j++)
          if (i != j && j != k && dis[k][j] < 0x3f3f3f3f)
            dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  for (int j = 1; j <= m; j++) {
    for (int ii = 0; ii < leaves; ii++) {
      int i = leaf[ii];
      int l = 0, r = 0x3f3f3f3f;
      while (r - l > 1) {
        int mid = (l + r) / 2;
        if (check(mid, i, j))
          l = mid;
        else
          r = mid;
      }
      dp[i][j] = l;
    }
  }
  buildtree(s, 0, -1);
  int l = 0, r = 0x3f3f3f3f;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    if (final(mid))
      l = mid;
    else
      r = mid;
  }
  cout << l;
  return 0;
}
