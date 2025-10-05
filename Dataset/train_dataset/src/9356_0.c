#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
const long long MOD = 1000000007;
const long long INF = 0x3f3f3f3f;
int val[111][111];
int n, m, k;
vector<pair<int, int> > pos;
int ddist[111][111], way[10][10], dist[211][10];
int used[111][111];
pair<int, int> pre[211][1 << 8];
int dp[211][1 << 8];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
queue<pair<int, int> > que;
void bfs(int x, int y, int o) {
  int i, j, u, v;
  while (!que.empty()) que.pop();
  que.push(make_pair(x, y));
  for (i = 0; i <= n + 1; i++)
    for (j = 0; j <= m + 1; j++) ddist[i][j] = -1;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= m; j++) ddist[i][j] = MOD;
  ddist[x][y] = val[x][y];
  dp[(x - 1) * m + y][1 << o] = val[x][y];
  while (!que.empty()) {
    u = que.front().first, v = que.front().second;
    que.pop();
    for (i = 0; i < 4; i++) {
      x = u + dx[i];
      y = v + dy[i];
      if (ddist[x][y] == -1) continue;
      if (ddist[x][y] > ddist[u][v] + val[x][y]) {
        ddist[x][y] = ddist[u][v] + val[x][y];
        dp[(x - 1) * m + y][1 << o] = ddist[x][y];
        pre[(x - 1) * m + y][1 << o] = make_pair((u - 1) * m + v, 1 << o);
        que.push(make_pair(x, y));
      }
    }
  }
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= m; j++) {
      dist[(i - 1) * m + j][o] = ddist[i][j];
    }
  }
}
set<pair<int, int> > S[2];
void doit(int p, int sta) {
  int u = (p - 1) / m + 1, v = (p - 1) % m + 1;
  used[u][v] = 1;
  if (pre[p][sta].first == -1) return;
  doit(pre[p][sta].first, pre[p][sta].second);
  doit(p, sta - pre[p][sta].second);
}
int main() {
  int i, j, l, ll, u, v, w, st, pt;
  int x, y, p, q;
  while (scanf("%d%d%d", &n, &m, &k) != EOF) {
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= m; j++) {
        scanf("%d", &val[i][j]);
      }
    }
    pos.clear();
    for (i = 0; i < 211; i++)
      for (j = 0; j < 1 << 8; j++) pre[i][j] = make_pair(-1, -1);
    for (u = 1; u <= n; u++) {
      for (v = 1; v <= m; v++) {
        i = (u - 1) * m + v;
        for (j = 0; j < 1 << k; j++) {
          dp[i][j] = MOD;
        }
      }
    }
    for (i = 0; i < k; i++) {
      scanf("%d%d", &u, &v);
      pos.push_back(make_pair(u, v));
      dp[(u - 1) * m + v][1 << i] = val[u][v];
    }
    S[0].clear();
    S[1].clear();
    for (i = 0; i < k; i++) S[0].insert(make_pair(pos[i].first, pos[i].second));
    int uu = 0, vv = 1;
    for (j = 1; j <= n * m; j++) {
      S[vv].clear();
      if (S[uu].size() == 0) break;
      while (S[uu].size()) {
        u = S[uu].begin()->first;
        v = S[uu].begin()->second;
        S[uu].erase(S[uu].begin());
        p = (u - 1) * m + v;
        for (i = 0; i < 4; i++) {
          x = u + dx[i];
          y = v + dy[i];
          if (x < 1 || x > n || y < 1 || y > m) continue;
          q = (x - 1) * m + y;
          for (l = 0; l < (1 << k); l++) {
            if (dp[q][l] > dp[p][l] + val[x][y]) {
              dp[q][l] = dp[p][l] + val[x][y];
              pre[q][l] = make_pair(p, l);
              S[vv].insert(make_pair(x, y));
            }
            for (ll = 0; ll < (1 << k); ll++) {
              if (ll & l) continue;
              if (dp[q][ll | l] > dp[p][l] + dp[q][ll]) {
                dp[q][ll | l] = dp[p][l] + dp[q][ll];
                pre[q][ll | l] = make_pair(p, l);
                S[vv].insert(make_pair(x, y));
              }
            }
          }
        }
      }
      swap(uu, vv);
    }
    int ans = MOD;
    for (i = 1; i <= n; i++)
      for (j = 1; j <= m; j++) used[i][j] = 0;
    for (i = 1; i <= n * m; i++) {
      if (ans > dp[i][((1 << k) - 1)]) {
        ans = dp[i][((1 << k) - 1)];
        p = i;
      }
    }
    doit(p, ((1 << k) - 1));
    printf("%d\n", ans);
    for (i = 1; i <= n; i++) {
      for (j = 1; j <= m; j++) {
        if (used[i][j])
          putchar('X');
        else
          putchar('.');
      }
      puts("");
    }
  }
  return 0;
}
