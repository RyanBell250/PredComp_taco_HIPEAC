#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int N = 504;
int n, m, dist[N][N], cnt[N];
vector<pair<int, int>> adj[N];
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) dist[i][j] = INF;
    dist[i][i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
    dist[u][v] = w;
    dist[v][u] = w;
  }
  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        if (dist[i][j] > dist[i][k] + dist[k][j])
          dist[i][j] = dist[i][k] + dist[k][j];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cnt[j] = 0;
      for (auto v : adj[j])
        if (dist[i][v.first] + v.second == dist[i][j]) cnt[j]++;
    }
    for (int j = i + 1; j <= n; j++) {
      int sum = 0;
      for (int p = 1; p <= n; p++) {
        if (dist[i][p] + dist[p][j] == dist[i][j]) sum += cnt[p];
      }
      cout << sum << " ";
    }
  }
}
