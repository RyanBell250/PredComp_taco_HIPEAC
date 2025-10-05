#include <bits/stdc++.h>
using namespace std;
const long long INF = 1LL << 60;
namespace mcmf {
const int MAX = 31000;
long long cap[MAX], flow[MAX], cost[MAX], dis[MAX];
int n, m, s, t, Q[MAX * 10], adj[MAX], link[MAX], last[MAX], from[MAX],
    visited[MAX];
void init(int nodes, int source, int sink) {
  m = 0, n = nodes, s = source, t = sink;
  for (int i = 0; i <= n; i++) last[i] = -1;
}
void addEdge(int u, int v, long long c, long long w) {
  adj[m] = v, cap[m] = c, flow[m] = 0, cost[m] = +w, link[m] = last[u],
  last[u] = m++;
  adj[m] = u, cap[m] = 0, flow[m] = 0, cost[m] = -w, link[m] = last[v],
  last[v] = m++;
}
bool spfa() {
  int i, j, x, f = 0, l = 0;
  for (i = 0; i <= n; i++) visited[i] = 0, dis[i] = INF;
  dis[s] = 0, Q[l++] = s;
  while (f < l) {
    i = Q[f++];
    for (j = last[i]; j != -1; j = link[j]) {
      if (flow[j] < cap[j]) {
        x = adj[j];
        if (dis[x] > dis[i] + cost[j]) {
          dis[x] = dis[i] + cost[j], from[x] = j;
          if (!visited[x]) {
            visited[x] = 1;
            if (f && rand() & 7)
              Q[--f] = x;
            else
              Q[l++] = x;
          }
        }
      }
    }
    visited[i] = 0;
  }
  return (dis[t] != INF);
}
pair<long long, long long> solve() {
  int i, j;
  long long mincost = 0, maxflow = 0;
  while (spfa()) {
    long long aug = INF;
    for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]) {
      aug = min(aug, cap[j] - flow[j]);
    }
    for (i = t, j = from[i]; i != s; i = adj[j ^ 1], j = from[i]) {
      flow[j] += aug, flow[j ^ 1] -= aug;
    }
    maxflow += aug, mincost += aug * dis[t];
  }
  return make_pair(mincost, maxflow);
}
}  // namespace mcmf
const int N = 55;
int ej_id[N][N], ej[N][N];
int node_id[N];
int res_id[N][N];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int source = 0;
  int tot = 0;
  int n, m;
  cin >> n >> m;
  memset(ej, -1, sizeof(ej));
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    ej[u][v] = 1;
    ej[v][u] = 0;
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      ej_id[i][j] = ++tot;
    }
  }
  for (int i = 1; i <= n; i++) {
    node_id[i] = ++tot;
  }
  int sink = ++tot;
  mcmf::init(tot + 1, source, sink);
  int fid = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (ej[i][j] == 1)
        mcmf::addEdge(ej_id[i][j], node_id[i], 1, -INF);
      else if (ej[i][j] == 0)
        mcmf::addEdge(ej_id[i][j], node_id[i], 1, INF);
      else
        mcmf::addEdge(ej_id[i][j], node_id[i], 1, 0);
      res_id[i][j] = fid;
      fid += 2;
      if (ej[i][j] == 1)
        mcmf::addEdge(ej_id[i][j], node_id[j], 1, INF);
      else if (ej[i][j] == 0)
        mcmf::addEdge(ej_id[i][j], node_id[j], 1, -INF);
      else
        mcmf::addEdge(ej_id[i][j], node_id[j], 1, 0);
      res_id[j][i] = fid;
      fid += 2;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      mcmf::addEdge(source, ej_id[i][j], +1, 0);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int k = 1; k <= n - 1; k++) {
      mcmf::addEdge(node_id[i], sink, +1, k);
    }
  }
  mcmf::solve();
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (i == j or mcmf::flow[res_id[i][j]] == 0)
        ej[i][j] = 0;
      else
        ej[i][j] = 1;
      cout << ej[i][j];
    }
    cout << endl;
  }
  return 0;
}
