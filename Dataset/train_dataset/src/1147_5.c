#include <bits/stdc++.h>
using namespace std;
int match[200009], dist[200009], q[200009], n, match1[200009];
vector<int> adj[200009];
vector<pair<int, pair<int, int> > > v;
bool bfs() {
  int f = 0, b = 0;
  for (int i = 1; i <= n; i++) {
    if (match1[i] == 0) {
      dist[i] = 0;
      q[f++] = i;
    } else
      dist[i] = 1000000007;
  }
  dist[0] = 1000000007;
  while (b < f) {
    int x = q[b++];
    if (x == 0) continue;
    int sz = adj[x].size();
    for (int i = 0; i < sz; i++) {
      int y = adj[x][i];
      if (dist[match[y]] == 1000000007) {
        dist[match[y]] = dist[x] + 1;
        q[f++] = match[y];
      }
    }
  }
  return dist[0] != 1000000007;
}
bool dfs(int x) {
  if (x) {
    int sz = adj[x].size();
    for (int i = 0; i < sz; i++) {
      int y = adj[x][i];
      if (dist[match[y]] == dist[x] + 1 && dfs(match[y])) {
        match1[x] = y;
        match[y] = x;
        return 1;
      }
    }
    dist[x] = 1000000007;
    return 0;
  }
  return 1;
}
int hopcropt(int val) {
  for (int i = 1; i <= n; i++) adj[i].clear();
  for (int i = 0; i < v.size(); i++) {
    if (v[i].first > val) continue;
    adj[v[i].second.first].push_back(v[i].second.second);
  }
  for (int i = 1; i <= n; i++) dist[i] = match[i] = q[i] = match1[i] = 0;
  int matching = 0;
  while (bfs()) {
    for (int i = 1; i <= n; i++) {
      if (match1[i] == 0 && dfs(i)) {
        matching++;
      }
    }
  }
  return matching;
}
int main() {
  int m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    v.push_back({c, {a, b}});
  }
  int lo = 0, hi = 1e9 + 10, ans = hi + 1, cnt = 0;
  while (lo <= hi) {
    int mi = (lo + hi) / 2;
    int a = hopcropt(mi);
    if (a >= n) {
      cnt++;
      ans = mi;
      hi = mi - 1;
    } else
      lo = mi + 1;
  }
  if (!cnt)
    printf("-1\n");
  else
    printf("%d\n", ans);
  return 0;
}
