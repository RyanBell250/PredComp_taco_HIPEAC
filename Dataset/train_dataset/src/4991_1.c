#include <bits/stdc++.h>
using namespace std;
vector<pair<int, bool>> edg[300001];
int id = 1, vis[300001], low[300001];
void dfs(int a, int p) {
  vis[a] = low[a] = id++;
  for (auto& b : edg[a]) {
    if (!vis[b.first]) {
      dfs(b.first, a);
      if (low[b.first] > vis[a]) {
        b.second = 1;
        for (auto& c : edg[b.first])
          if (c.first == a) c.second = 1;
      }
      low[a] = min(low[a], low[b.first]);
    } else if (b.first != p)
      low[a] = min(low[a], vis[b.first]);
  }
}
int ma = -1, u;
bool v[300001];
void f1(int a, int d) {
  if (v[a]) return;
  v[a] = 1;
  if (d > ma) {
    ma = d;
    u = a;
  }
  for (auto& b : edg[a]) {
    if (b.second)
      f1(b.first, d + 1);
    else
      f1(b.first, d);
  }
}
int main() {
  ios::sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    edg[a].push_back({b, 0});
    edg[b].push_back({a, 0});
  }
  dfs(1, 1);
  f1(1, 0);
  ma = 0;
  memset(v, 0, sizeof v);
  f1(u, 0);
  cout << ma;
  return 0;
}
