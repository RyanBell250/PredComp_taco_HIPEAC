#include <bits/stdc++.h>
using namespace std;
bool debug = 0;
const int maxn = 123470;
struct Edge {
  int y;
  bool can;
  Edge(int _y, bool _can = 0) : y(_y), can(_can) {}
};
vector<Edge> e;
vector<int> h[maxn];
int ecnt = 0, n, m, stcnt = 0;
bool can[maxn] = {0};
vector<int> atak;
bool batk[maxn] = {0};
int dis[maxn];
void dfs(int x, int d, int fa) {
  dis[x] = d;
  for (auto &i : h[x])
    if (e[i].can && e[i].y != fa) dfs(e[i].y, d + 1, x);
}
queue<int> q;
int pre[maxn];
bool vis[maxn] = {0};
void bfs(int x) {
  if (debug)
    cerr << "[L~" << 27 << "] "
         << "x"
         << " = " << x << endl;
  vis[x] = 1;
  memset(pre, -1, sizeof(pre));
  q.push(x);
  while (!q.empty()) {
    if (debug)
      cerr << "[L~" << 32 << "] "
           << "x"
           << " = " << x << endl;
    if (debug)
      cerr << "[L~" << 33 << "] "
           << "pre[x]"
           << " = " << pre[x] << endl;
    x = q.front();
    q.pop();
    if (batk[x]) {
      for (int i = x; !vis[i]; i = e[pre[i]].y) {
        stcnt++;
        e[pre[i]].can = e[pre[i] ^ 1].can = 1;
        vis[i] = 1;
      }
    }
    for (auto &j : h[x])
      if (j != pre[x]) {
        if (debug)
          cerr << "[L~" << 45 << "] "
               << "e[j].y"
               << " = " << e[j].y << endl;
        q.push(e[j].y);
        pre[e[j].y] = j ^ 1;
      }
  }
}
int main() {
  scanf("%d%d", &m, &n);
  for (int i = 0; i < m - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    e.push_back(Edge(v));
    h[u].push_back(ecnt++);
    e.push_back(Edge(u));
    h[v].push_back(ecnt++);
  }
  for (int i = 0; i < n; i++) {
    int u;
    scanf("%d", &u);
    atak.push_back(u);
    batk[u] = 1;
  }
  if (debug)
    cerr << "[L~" << 67 << "] "
         << "\"bfs in\""
         << " = "
         << "bfs in" << endl;
  bfs(atak[0]);
  if (debug)
    cerr << "[L~" << 69 << "] "
         << "\"bfs done\""
         << " = "
         << "bfs done" << endl;
  dfs(atak[0], 0, atak[0]);
  sort(atak.begin(), atak.end());
  int best = -1, j, k;
  for (auto i : atak)
    if (dis[i] > best) best = dis[i], j = i;
  dfs(j, 0, j);
  best = -1;
  for (auto i : atak)
    if (dis[i] > best) best = dis[i], k = i;
  if (j > k) swap(j, k);
  if (debug)
    cerr << "[L~" << 80 << "] "
         << "best"
         << " = " << best << endl;
  if (debug)
    cerr << "[L~" << 81 << "] "
         << "stcnt"
         << " = " << stcnt << endl;
  printf("%d\n%d\n", j, 2 * (stcnt)-best);
  return 0;
}
