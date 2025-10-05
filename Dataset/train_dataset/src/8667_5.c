#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> adj[100030];
int vis[100300], ord[100300], BinarySearchMid, deg[100300];
int dfs(int x) {
  if (vis[x] == 1) return 0;
  if (vis[x] == 2) return 1;
  vis[x] = 2;
  int ok = 0;
  for (auto u : adj[x])
    if (u.second > BinarySearchMid) ok = max(ok, dfs(u.first));
  vis[x] = 1;
  return ok;
}
int U[100030], V[100300], C[100300];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    adj[u].push_back({v, c});
    U[i] = u;
    V[i] = v;
    C[i] = c;
  }
  int st = 0, en = 1e9;
  while (st < en) {
    int mid = (st + en) / 2;
    BinarySearchMid = mid;
    bool ok = 0;
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++) {
      if (!vis[i]) ok |= dfs(i);
    }
    if (ok) {
      st = mid + 1;
    } else
      en = mid;
  }
  vector<int> zbr;
  memset(vis, 0, sizeof vis);
  vector<vector<int>> adj2(n + 1);
  for (int i = 1; i <= m; i++) {
    int u = U[i], v = V[i], c = C[i];
    if (c > en) {
      adj2[u].push_back(v);
      deg[v]++;
    }
  }
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 0) q.push(i);
  }
  int cnt = 0;
  while (!q.empty()) {
    int nxt = q.front();
    q.pop();
    ord[nxt] = ++cnt;
    for (auto u : adj2[nxt]) {
      deg[u]--;
      if (deg[u] == 0) q.push(u);
    }
  }
  for (int i = 1; i <= m; i++) {
    int u = U[i], v = V[i], c = C[i];
    if (ord[u] > ord[v]) {
      zbr.push_back(i);
    }
  }
  cout << en << ' ' << zbr.size() << endl;
  for (auto u : zbr) printf("%d ", u);
  return 0;
}
