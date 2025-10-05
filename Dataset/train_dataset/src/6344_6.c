#include <bits/stdc++.h>
using namespace std;
const int dd[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
struct edge {
  int v, next, first, cap, cost;
} e[222222];
const int inf = int(1e9);
int n, m, a[111][111], ff, first[111111], phi[111111], d[111111], with[111111],
    N, S, T, color[111111], cc;
priority_queue<pair<int, int>, vector<pair<int, int> >,
               greater<pair<int, int> > >
    pq;
void addEdge(int u, int v, int c) {
  e[ff].v = v, e[ff].next = first[u], e[ff].first = 0, e[ff].cost = c,
  e[ff].cap = 1, first[u] = ff++;
  e[ff].v = u, e[ff].next = first[v], e[ff].first = 0, e[ff].cost = -c,
  e[ff].cap = 0, first[v] = ff++;
}
bool exist(int i, int j) { return (i >= 0 && j >= 0 && i < n && j < m); }
int minCostFlow() {
  int res = 0;
  for (int iter = 0; iter < n * m / 2; ++iter) {
    for (int i = 0; i < N; ++i) d[i] = inf;
    d[S] = 0;
    ++cc;
    int u = S;
    while (u != -1) {
      color[u] = cc;
      for (int i = first[u]; i != -1; i = e[i].next)
        if (e[i].first < e[i].cap) {
          int v = e[i].v;
          if (d[v] > d[u] + phi[u] - phi[v] + e[i].cost) {
            d[v] = d[u] + phi[u] - phi[v] + e[i].cost;
            with[v] = i;
          }
        }
      u = -1;
      for (int v = 0; v < N; ++v)
        if (color[v] != cc) {
          if (u == -1 || d[v] < d[u]) u = v;
        }
    }
    for (int u = T; u != S;) {
      int i = with[u];
      int v = e[i ^ 1].v;
      ++e[i].first;
      --e[i ^ 1].first;
      res += e[i].cost;
      u = v;
    }
  }
  return res;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) scanf("%d", &a[i][j]);
  memset(first, -1, sizeof(first));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((i + j) & 1) {
        for (int k = 0; k < 4; ++k) {
          int ii = i + dd[k][0], jj = j + dd[k][1];
          if (exist(ii, jj)) {
            addEdge(i * m + j, ii * m + jj, a[i][j] != a[ii][jj]);
          }
        }
      }
    }
  }
  S = n * m;
  T = S + 1;
  N = T + 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if ((i + j) & 1)
        addEdge(S, i * m + j, 0);
      else
        addEdge(i * m + j, T, 0);
    }
  }
  cout << minCostFlow() << endl;
  return 0;
}
