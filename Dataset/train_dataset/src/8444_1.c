#include <bits/stdc++.h>
using namespace std;
struct qnode {
  int id;
  long long val;
  bool operator<(qnode b) const { return val > b.val; }
};
queue<int> qu[200100];
int w[200100], vis[200100], add[200100];
int n, m, Q, opt, x, y, z;
long long dis[200100];
priority_queue<qnode> q;
vector<pair<int, int> > edge[200100];
void Dijkstra() {
  memset(dis, 0x3f, sizeof(dis));
  dis[1] = 0;
  memset(vis, false, sizeof(vis));
  q.push((qnode){1, 0});
  while (!q.empty()) {
    int x = q.top().id;
    q.pop();
    if (vis[x]) continue;
    vis[x] = true;
    for (auto i : edge[x]) {
      int upup = i.first, z = w[i.second];
      dis[upup] = min(dis[upup], dis[x] + z);
      if (!vis[upup]) q.push((qnode){upup, dis[upup]});
    }
  }
}
int main() {
  scanf("%d%d%d", &n, &m, &Q);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%lld", &x, &y, &w[i]);
    edge[x].push_back(make_pair(y, i));
  }
  Dijkstra();
  while (Q--) {
    scanf("%d", &opt);
    if (opt == 1) {
      scanf("%d", &x);
      if (dis[x] == 0x3f3f3f3f3f3f3f3f)
        puts("-1");
      else
        printf("%lld\n", dis[x]);
    } else {
      scanf("%d", &x);
      for (int i = 1; i <= x; i++) {
        scanf("%d", &y);
        w[y]++;
      }
      for (int i = 1; i <= n; i++) add[i] = x + 1;
      qu[add[1] = 0].push(1);
      for (int i = 0; i <= x; i++)
        for (; !qu[i].empty(); qu[i].pop()) {
          int now = qu[i].front();
          if (add[now] != i) continue;
          for (auto j : edge[now]) {
            int y = j.first, z = w[j.second];
            long long d = dis[now] + z + add[now] - dis[y];
            if (d < add[y]) qu[add[y] = d].push(y);
          }
        }
      for (int i = 1; i <= n; i++)
        if (add[i] != x + 1) dis[i] += add[i];
    }
  }
}
