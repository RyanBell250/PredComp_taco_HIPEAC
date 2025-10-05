#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-12;
const int INF = 999999999;
int m, n;
char g[30][31];
int f[30][30];
int domino_id[7][7];
vector<int> nei[14];
int c[7];
int p[14], ans[14];
int used[28];
int sum;
void Add(int x1, int y1, int x2, int y2) {
  if (g[x1][y1] != g[x2][y2]) return;
  int c1 = f[x1][y1], c2 = f[x2][y2];
  if (c1 <= c2)
    nei[c2].push_back(c1);
  else
    nei[c1].push_back(c2);
}
void Go(int t) {
  if (t == 14) {
    if (sum == 0) memcpy(ans, p, sizeof(ans));
    ++sum;
    return;
  }
  for (int i = 0; i < 7; ++i)
    if (c[i] < 2) {
      p[t] = i;
      bool ok = 1;
      for (typeof((nei[t]).begin()) j = (nei[t]).begin(); j != (nei[t]).end();
           j++) {
        if (used[domino_id[i][p[*j]]] != -1) {
          ok = 0;
          break;
        }
        used[domino_id[i][p[*j]]] = t;
      }
      if (ok) {
        ++c[i];
        Go(t + 1);
        --c[i];
      }
      for (typeof((nei[t]).begin()) j = (nei[t]).begin(); j != (nei[t]).end();
           j++) {
        if (used[domino_id[i][p[*j]]] == t) used[domino_id[i][p[*j]]] = -1;
      }
    }
}
int main() {
  scanf("%d%d", &m, &n);
  for (int i = 0; i < m; ++i) scanf("%s", g[i]);
  {
    int k = 0;
    memset(f, -1, sizeof(f));
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (g[i][j] != '.' && f[i][j] == -1) {
          f[i][j] = f[i][j + 1] = f[i + 1][j] = f[i + 1][j + 1] = k++;
        }
    k = 0;
    for (int i = 0; i < 7; ++i)
      for (int j = i; j < 7; ++j) {
        domino_id[i][j] = domino_id[j][i] = k++;
      }
    for (int i = 0; i < 14; ++i) nei[i].clear();
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (g[i][j] != '.') {
          if (j + 1 < n) Add(i, j, i, j + 1);
          if (i + 1 < m) Add(i, j, i + 1, j);
        }
  }
  sum = 0;
  memset(c, 0, sizeof(c));
  memset(used, -1, sizeof(used));
  Go(0);
  printf("%d\n", sum);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j)
      if (g[i][j] == '.')
        printf(".");
      else
        printf("%d", ans[f[i][j]]);
    printf("\n");
  }
  return 0;
}
