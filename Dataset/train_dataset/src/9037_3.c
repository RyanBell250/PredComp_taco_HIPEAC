#include <bits/stdc++.h>
const int maxnm = 9 + 2;
int n, m;
char map[maxnm][maxnm], best[maxnm][maxnm];
bool shape[4][3][3] = {{{1, 1, 1}, {0, 1, 0}, {0, 1, 0}},
                       {{0, 1, 0}, {0, 1, 0}, {1, 1, 1}},
                       {{1, 0, 0}, {1, 1, 1}, {1, 0, 0}},
                       {{0, 0, 1}, {1, 1, 1}, {0, 0, 1}}};
inline bool valid(int x, int y, int k) {
  if (x < 1 || x + 2 > n || y < 1 || y + 2 > m) return false;
  for (int i = 0; i <= 2; ++i)
    for (int j = 0; j <= 2; ++j) {
      if (shape[k][i][j] && map[x + i][y + j] != '.') return false;
    }
  return true;
}
inline void set(int x, int y, int k, char c) {
  for (int i = 0; i <= 2; ++i)
    for (int j = 0; j <= 2; ++j) {
      if (shape[k][i][j]) map[x + i][y + j] = c;
    }
}
int ans;
void dfs(int x, int y, int now) {
  if (now + ((n - x - 1) * m + m - y + 1) / 5 <= ans) return;
  if (y > m) return dfs(x + 1, 1, now);
  if (x <= n) {
    for (int i = x; i <= n; ++i)
      for (int j = (i == x ? y : 1); j <= m; ++j) {
        for (int k = 0; k < 4; ++k) {
          if (!valid(i, j, k)) continue;
          set(i, j, k, 'A' + now);
          dfs(i, j + 1, now + 1);
          set(i, j, k, '.');
        }
      }
  }
  if (now > ans) {
    ans = now;
    memcpy(best, map, sizeof(map));
  }
}
int main() {
  int a;
  a = 1;
  a = 0;
  a = (a == 1);
  scanf("%d%d", &n, &m);
  memset(map, '.', sizeof(map));
  memset(best, '.', sizeof(best));
  dfs(1, 1, 0);
  printf("%d\n", ans);
  for (int i = 1; i <= n; ++i, putchar('\n'))
    for (int j = 1; j <= m; ++j) {
      putchar(best[i][j]);
    }
  return 0;
}
