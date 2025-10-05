#include <bits/stdc++.h>
using namespace std;
const int maxn = 55, mo = 1000000007;
int n, m;
int E[maxn][maxn];
int g[2][2][maxn][maxn][maxn << 1], f[maxn << 1][maxn][2],
    A[maxn][maxn][maxn << 1], B[maxn][maxn][maxn << 1];
vector<int> ed[maxn * maxn];
int stk[maxn * 3], l, r;
void add(int &x, int y) {
  x += y;
  if (x >= mo) x -= mo;
}
pair<int, int> Go(int x, bool s) {
  int i, len = 1, y, t;
  while (l < r && r <= n + n) {
    y = stk[l++];
    if (t = E[x][y], !t || (t > m) != s) return pair<int, int>(111, 111);
    x = y;
    len++;
    for (i = 0; i < (int)ed[t].size(); i++) stk[r++] = ed[t][i];
  }
  if (l == r) return pair<int, int>(len, x);
  return pair<int, int>(111, 111);
}
void Work(bool s) {
  memset(A, 0, sizeof A);
  memset(B, 0, sizeof B);
  int i, j, k, p, t;
  pair<int, int> tmp1, tmp2;
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      if (t = E[i][j], t && (t > m) == s)
        for (k = 0; k < (int)ed[t].size(); k++)
          if (ed[t][k] == i) {
            l = r = 0;
            for (p = k - 1; p >= 0; p--) stk[r++] = ed[t][p];
            tmp1 = Go(i, s ^ 1);
            if (tmp1.first > n + n) continue;
            if (k == (int)ed[t].size() - 1)
              A[tmp1.second][j][tmp1.first]++;
            else if (ed[t][k + 1] == j) {
              l = r = 0;
              for (p = k + 2; p < (int)ed[t].size(); p++) stk[r++] = ed[t][p];
              tmp2 = Go(j, s);
              if (tmp2.first + tmp1.first - 1 <= n + n)
                B[tmp1.second][tmp2.second][tmp1.first + tmp2.first - 1]++;
            }
          }
}
int main() {
  int i, j, k, l, u, v, tmp, ans;
  scanf("%d%d", &n, &m);
  for (i = 1; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &k);
    E[u][v] = i;
    E[v][u] = i + m;
    if (!k)
      g[0][0][u][v][1] = 1;
    else {
      for (j = k; j; j--) {
        scanf("%d", &k);
        ed[i].push_back(k);
      }
      ed[i + m] = ed[i];
      reverse(ed[i + m].begin(), ed[i + m].end());
    }
  }
  Work(0);
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      for (k = 1; k <= n + n; k++)
        g[1][0][i][j][k] = A[i][j][k], g[1][1][i][j][k] = B[i][j][k];
  Work(1);
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      for (k = 1; k <= n + n; k++) g[0][1][i][j][k] = A[j][i][k];
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      for (k = 1; k <= n + n; k++)
        for (v = 0; v < 2; v++) add(f[k][j][v], g[1][v][i][j][k]);
  for (i = 1; i <= n + n; i++) {
    ans = 0;
    for (j = 1; j <= n; j++) {
      add(ans, f[i][j][1]);
      for (v = 0; v < 2; v++)
        for (l = 1; i + l <= n + n; l++)
          for (k = 1; k <= n; k++)
            for (u = 0; u < 2; u++)
              if ((tmp = g[v ^ 1][u][j][k][l]))
                add(f[i + l][k][u], 1LL * f[i][j][v] * tmp);
    }
    printf("%d\n", ans);
  }
  return 0;
}
