#include <bits/stdc++.h>
using namespace std;
int n, m, from, to, d;
int read() {
  int x = 0;
  char ch = getchar();
  while (ch < '0' || ch > '9') ch = getchar();
  while (ch >= '0' && ch <= '9') {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x;
}
struct xx {
  int from, to, d;
} way[155];
bool cmp(xx a, xx b) { return a.d < b.d; }
struct xxx {
  bitset<155> s[155];
} M, f[33], a, g[33];
xxx operator*(xxx a, xxx b) {
  xxx d;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      if (a.s[i][j]) d.s[i] |= b.s[j];
    }
  return d;
}
int main() {
  n = read();
  m = read();
  for (int i = 1; i <= m; ++i) {
    way[i].from = read();
    way[i].to = read();
    way[i].d = read();
  }
  sort(way + 1, way + m + 1, cmp);
  way[m + 1].d = 0x3f3f3f3f;
  if (way[1].d > 0) {
    cout << "Impossible";
    return 0;
  }
  a.s[1][1] = 1;
  for (int i = 1; i <= m; ++i) {
    M.s[way[i].from][way[i].to] = 1;
    while (i + 1 <= m && way[i].d == way[i + 1].d) {
      i++;
      M.s[way[i].from][way[i].to] = 1;
    }
    f[0] = M;
    for (int j = 1; j <= n; ++j) f[0].s[j][j] = 1;
    int w = (way[i + 1].d - way[i].d);
    int e = 0;
    for (int j = 0; j <= 30; ++j)
      if ((1 << j) <= w)
        e = j;
      else
        break;
    for (int j = 1; j <= e; ++j) f[j] = f[j - 1] * f[j - 1];
    int cnt = 0;
    xxx now = a;
    for (int j = e; j >= 0; --j) {
      if ((cnt + (1 << j)) <= w) {
        xxx g = now * f[j];
        bool flag = 0;
        for (int k = 1; k <= n; ++k)
          if (g.s[k][n]) flag = 1;
        if (!flag) cnt += (1 << j), now = g;
      }
    }
    if (cnt != w) {
      cout << cnt + 1 + way[i].d;
      return 0;
    }
    f[0] = M;
    for (int j = 1; j <= e; ++j) f[j] = f[j - 1] * f[j - 1];
    for (int j = e; j >= 0; --j)
      if (w >= (1 << j)) w -= (1 << j), a = a * f[j];
    xxx u = a;
    for (int j = 1; j <= n; ++j) a.s[j].reset();
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= n; ++k)
        if (u.s[j][k]) a.s[k][k] = 1;
  }
  cout << "Impossible";
  return 0;
}
