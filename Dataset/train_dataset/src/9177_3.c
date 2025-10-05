#include <bits/stdc++.h>
const int N = 2e3;
using namespace std;
int n1, n2, m, id1[N + 5], id2[N + 5], S, T, idc, d1[N + 5], d2[N + 5], lim,
    num1[N + 5], num2[N + 5];
vector<int> ans[N + 5];
namespace F {
const int N = 3e6;
const long long inf = 2e18;
struct edges {
  int to;
  long long cost;
} edge[N * 2 + 5];
int nxt[N * 2 + 5], head[N + 5], edge_cnt = 1, dis[N + 5], q[N + 5], cur[N + 5],
                                 S, T;
void add_edge(int u, int v, long long w) {
  edge[++edge_cnt] = (edges){v, w};
  nxt[edge_cnt] = head[u];
  head[u] = edge_cnt;
}
void add(int u, int v, long long w) {
  add_edge(u, v, w);
  add_edge(v, u, 0);
}
int bfs() {
  for (int i = 1; i <= idc; i++) cur[i] = head[i], dis[i] = 0;
  int l = 1, r = 0;
  dis[S] = 1;
  q[++r] = S;
  while (l <= r) {
    int u = q[l++];
    for (int i = head[u]; i; i = nxt[i]) {
      int v = edge[i].to, w = edge[i].cost;
      if (w && !dis[v]) {
        dis[v] = dis[u] + 1;
        q[++r] = v;
      }
    }
  }
  return dis[T];
}
long long dfs(int u, long long flow) {
  if (u == T) return flow;
  long long sm = 0;
  for (int &i = cur[u]; i; i = nxt[i]) {
    int v = edge[i].to;
    long long w = edge[i].cost;
    if (dis[v] == dis[u] + 1 && w) {
      long long res = dfs(v, min(w, flow));
      edge[i].cost -= res;
      edge[i ^ 1].cost += res;
      sm += res;
      flow -= res;
      if (!flow) break;
    }
  }
  return sm;
}
long long dinic(int s, int t) {
  S = s;
  T = t;
  long long ans = 0;
  while (bfs()) ans += dfs(S, inf);
  return ans;
}
void clear() {
  edge_cnt = 1;
  for (int i = 1; i <= idc; i++) head[i] = 0;
  idc = 0;
}
void update(int k) {
  for (int i = 1; i <= m; i++)
    if (edge[i << 1].cost == 1) ans[k].push_back(i);
}
}  
int main() {
  scanf("%d%d%d", &n1, &n2, &m);
  S = ++idc;
  T = ++idc;
  for (int i = 1; i <= n1; i++) id1[i] = ++idc;
  for (int i = 1; i <= n2; i++) id2[i] = ++idc;
  int u, v;
  lim = m + 5;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    F::add(id1[u], id2[v], 1);
    d1[u]++;
    d2[v]++;
  }
  for (int i = 1; i <= n1; i++) lim = min(lim, d1[i]);
  for (int i = 1; i <= n2; i++) lim = min(lim, d2[i]);
  for (int i = 1; i <= n1; i++) {
    F::add(S, id1[i], d1[i] - lim);
    num1[i] = F::edge_cnt ^ 1;
  }
  for (int i = 1; i <= n2; i++) {
    F::add(id2[i], T, d2[i] - lim);
    num2[i] = F::edge_cnt ^ 1;
  }
  int x = F::dinic(S, T);
  F::update(lim);
  for (int i = 1; i <= lim; i++) {
    for (int j = 1; j <= n1; j++) F::edge[num1[j]].cost++;
    for (int j = 1; j <= n2; j++) F::edge[num2[j]].cost++;
    x = F::dinic(S, T);
    F::update(lim - i);
  }
  for (int i = 0; i <= lim; i++) {
    printf("%d ", ans[i].size());
    for (int j = 0; j < ans[i].size(); j++) printf("%d ", ans[i][j]);
    putchar(10);
  }
  return 0;
}
