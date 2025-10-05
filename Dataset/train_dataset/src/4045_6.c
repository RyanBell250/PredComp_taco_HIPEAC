#include <bits/stdc++.h>
const int N = 15000;
const int M = 1000000;
const int INF = 1 << 29;
struct Edge {
  int to, flow, capa, next;
  Edge(int v = 0, int c = 0, int n = 0) : to(v), flow(0), capa(c), next(n) {}
} g[M];
int first[N], arc[N], edge_count;
int vs, vt;
void add_edge(int u, int v, int c) {
  edge_count++;
  g[edge_count] = Edge(v, c, first[u]), first[u] = edge_count;
  g[M - edge_count] = Edge(u, 0, first[v]), first[v] = M - edge_count;
}
int queue[N], label[N];
bool bfs() {
  memset(label, 0, sizeof(label));
  queue[0] = vs;
  label[vs] = 1;
  for (int head = 0, tail = 0; head <= tail; ++head) {
    int u = queue[head];
    for (int iter = first[u]; iter; iter = g[iter].next) {
      int v = g[iter].to;
      if (g[iter].flow < g[iter].capa && label[v] == 0) {
        label[v] = label[u] + 1;
        queue[++tail] = v;
      }
    }
  }
  return label[vt];
}
int dfs(int u, int d) {
  if (u == vt) {
    return d;
  }
  int delta = 0;
  for (int &iter = arc[u]; iter; iter = g[iter].next) {
    int v = g[iter].to;
    if (g[iter].flow < g[iter].capa && label[u] + 1 == label[v]) {
      int r = dfs(v, std::min(d - delta, g[iter].capa - g[iter].flow));
      g[iter].flow += r;
      g[M - iter].flow -= r;
      delta += r;
      if (delta == d) {
        break;
      }
    }
  }
  return delta;
}
int sex[N];
int n, m, delta;
int main() {
  scanf("%d%d%d", &n, &m, &delta);
  vs = n + m + 1;
  vt = n + m + 2;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", sex + i);
  }
  for (int i = 1; i <= n; ++i) {
    int cost;
    scanf("%d", &cost);
    if (sex[i] == 0) {
      add_edge(vs, i, cost);
    } else {
      add_edge(i, vt, cost);
    }
  }
  int sum = 0;
  for (int i = 1; i <= m; ++i) {
    int appoint, weight, amount;
    scanf("%d%d%d", &appoint, &weight, &amount);
    sum += weight;
    while (amount--) {
      int x;
      scanf("%d", &x);
      if (appoint == 0) {
        add_edge(n + i, x, INF);
      } else {
        add_edge(x, n + i, INF);
      }
    }
    int is_friend;
    scanf("%d", &is_friend);
    int cost = is_friend ? weight + delta : weight;
    if (appoint == 0) {
      add_edge(vs, n + i, cost);
    } else {
      add_edge(n + i, vt, cost);
    }
  }
  int flow = 0;
  while (bfs()) {
    memcpy(arc, first, sizeof(first));
    flow += dfs(vs, INF);
  }
  printf("%d\n", sum - flow);
  return 0;
}
