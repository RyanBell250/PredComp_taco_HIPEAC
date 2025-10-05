#include <bits/stdc++.h>
using namespace std;
const long long maxn = 5e2 + 7;
const long long mod = 1e9 + 7;
const long long INF = 1e9 + 7;
const long long mlog = 20;
const long long SQ = 400;
struct Edge {
  long long u, v, w;
};
long long dis[maxn][maxn];
long long cnt[maxn][maxn];
long long ans[maxn][maxn];
vector<Edge> edges;
int32_t main() {
  ios_base::sync_with_stdio(false), cin.tie(), cout.tie();
  ;
  long long n, m;
  cin >> n >> m;
  for (long long i = 1; i <= n; i++)
    for (long long j = 1; j <= n; j++) dis[i][j] = +INF;
  for (long long i = 1; i <= n; i++) dis[i][i] = 0;
  for (long long i = 0; i < m; i++) {
    long long u, v, w;
    cin >> u >> v >> w;
    dis[u][v] = w;
    dis[v][u] = w;
    edges.push_back({u, v, w});
  }
  for (long long k = 1; k <= n; k++)
    for (long long i = 1; i <= n; i++)
      for (long long j = 1; j <= n; j++)
        dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
  for (auto edge : edges) {
    long long u = edge.u;
    long long v = edge.v;
    long long w = edge.w;
    for (long long i = 1; i <= n; i++) {
      if (dis[i][u] + w == dis[i][v]) cnt[i][v]++;
      if (dis[i][v] + w == dis[i][u]) cnt[i][u]++;
    }
  }
  for (long long v = 1; v <= n; v++)
    for (long long u = v + 1; u <= n; u++)
      for (long long k = 1; k <= n; k++)
        if (dis[v][k] + dis[k][u] == dis[v][u]) ans[v][u] += cnt[v][k];
  for (long long i = 1; i <= n; i++)
    for (long long j = i + 1; j <= n; j++) cout << ans[i][j] << " ";
  cout << "\n";
  return 0;
}
