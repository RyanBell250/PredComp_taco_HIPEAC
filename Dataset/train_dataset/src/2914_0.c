#include <bits/stdc++.h>
using namespace std;
int dp[1 << 10][1 << 10];
int use[1 << 10][1 << 10];
int g[10][10];
struct node {
  int s1, s2;
};
queue<node> q;
int n, m, k;
int p1[20], p2[20];
void bfs() {
  memset(use, 0, sizeof(use));
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++) {
      if (g[i][j] == 0) continue;
      node tmp;
      tmp.s1 = tmp.s2 = 0;
      tmp.s1 |= (1 << i);
      tmp.s1 |= (1 << j);
      tmp.s2 = tmp.s1;
      q.push(tmp);
      use[tmp.s1][tmp.s2] = 1;
      dp[tmp.s1][tmp.s2] = 1;
    }
  while (!q.empty()) {
    node hh = q.front();
    q.pop();
    for (int i = 0; i < n; i++) {
      if (!(hh.s1 & (1 << i))) continue;
      for (int j = 0; j < n; j++) {
        if (g[i][j] == 0) continue;
        if (hh.s1 & (1 << j)) continue;
        int ns1 = hh.s1, ns2 = hh.s2;
        ns1 |= (1 << j);
        if (ns2 & (1 << i)) ns2 -= (1 << i);
        ns2 |= (1 << j);
        if (ns2 & ((1 << j) - 1)) continue;
        dp[ns1][ns2] += dp[hh.s1][hh.s2];
        if (!use[ns1][ns2]) {
          use[ns1][ns2] = 1;
          node tmp;
          tmp.s1 = ns1;
          tmp.s2 = ns2;
          q.push(tmp);
        }
      }
    }
  }
}
int main() {
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    memset(g, 0, sizeof(g));
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--;
      v--;
      g[u][v] = g[v][u] = 1;
    }
    bfs();
    int ans = 0;
    for (int i = 0; i < (1 << n); i++) {
      int cntt = 0, num = i;
      for (; num != 0; cntt += num % 2, num /= 2)
        ;
      if (cntt == k) ans += dp[(1 << n) - 1][i];
    }
    printf("%d\n", ans);
  }
  return 0;
}
