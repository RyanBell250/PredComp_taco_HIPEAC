#include <bits/stdc++.h>
using namespace std;
struct node {
  int x, y, z;
  node() {}
  node(int _x, int _y, int _z) {
    x = _x;
    y = _y;
    z = _z;
  }
};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char s[30][30];
int a[30][30], w[30], f[30][30][2000], c[30][30][4];
int main() {
  int N, M, T, i, j, k, sx, sy;
  scanf("%d%d", &N, &M);
  for (i = 1; i <= N; i++) scanf("%s", s[i] + 1);
  int t = 0;
  for (i = 1; i <= N; i++)
    for (j = 1; j <= M; j++)
      if (isdigit(s[i][j])) t = max(t, s[i][j] - '0');
  T = t;
  for (i = 0; i < T; i++) scanf("%d", &w[i]);
  queue<node> Q;
  memset(a, -1, sizeof(a));
  memset(f, -1, sizeof(f));
  for (i = 1; i <= N; i++)
    for (j = 1; j <= M; j++) {
      if (s[i][j] == 'S') {
        s[i][j] = '.';
        sx = i;
        sy = j;
      } else if (isdigit(s[i][j]))
        a[i][j] = s[i][j] - '1';
      else if (s[i][j] == 'B')
        a[i][j] = t++;
    }
  for (i = 1; i <= N; i++)
    for (j = 1; j <= M; j++) {
      for (k = 1; k < j; k++) {
        if (~a[i - 1][k]) c[i][j][0] |= 1 << a[i - 1][k];
        if (~a[i][k]) c[i][j][1] |= 1 << a[i][k];
      }
    }
  memset(f, -1, sizeof(f));
  f[sx][sy][0] = 0;
  Q.push(node(sx, sy, 0));
  while (!Q.empty()) {
    int x = Q.front().x, y = Q.front().y, z = Q.front().z, xx, yy, zz;
    Q.pop();
    for (i = 0; i < 4; i++) {
      xx = x + dx[i];
      yy = y + dy[i];
      if (1 <= xx && xx <= N && 1 <= yy && yy <= M && s[xx][yy] == '.') {
        zz = z ^ c[x][y][i];
        if (f[xx][yy][zz] < 0) {
          f[xx][yy][zz] = f[x][y][z] + 1;
          Q.push(node(xx, yy, zz));
        }
      }
    }
  }
  int ans = 0;
  for (k = 0; k < 1 << T; k++) {
    int s = 0, x;
    for (x = 0; x < T; x++)
      if (k & 1 << x) s += w[x];
    if (~f[sx][sy][k]) ans = max(ans, s - f[sx][sy][k]);
  }
  printf("%d\n", ans);
}
