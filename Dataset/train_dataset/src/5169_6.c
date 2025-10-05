#include <bits/stdc++.h>
using namespace std;
vector<int> g[220 * 2];
bool ad[440][440] = {{}};
int n, m, type[128], N;
char s[220], t[220] = {};
bool color[220 * 2] = {};
bool tmp[220][440];
char e;
bool solve(int x, bool fg = false) {
  if (x == n) return true;
  bool vt[2] = {};
  memcpy(tmp[x], color, 440);
  for (char c = fg ? 'a' : s[x]; c <= e; ++c, fg = true) {
    if (color[x + x + type[c] ^ 1]) continue;
    if (vt[type[c]]) continue;
    if (fg) vt[type[c]] = true;
    t[x] = c;
    int pos = x + x + type[c];
    for (int y : g[pos]) color[y] = true;
    if (solve(x + 1, fg)) return true;
    memcpy(color, tmp[x], 440);
  }
  return false;
}
int main() {
  char l[32];
  scanf("%s", l);
  e = strlen(l) + 'a' - 1;
  for (int i = 0; l[i]; ++i) {
    type['a' + i] = l[i] == 'V';
  }
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int x, y;
    char a[4], b[4];
    scanf("%d%s%d%s", &x, a, &y, b);
    x--;
    y--;
    int aa = x + x + (a[0] == 'V');
    int bb = y + y + (b[0] == 'V');
    ad[aa][bb] = true;
    ad[bb ^ 1][aa ^ 1] = true;
  }
  N = n * 2;
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      for (int k = 0; k < N; ++k) ad[i][j] |= ad[i][k] & ad[k][j];
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < i; ++j)
      if (ad[j][i]) g[j].push_back(i);
  for (int i = 0; i < n; ++i) {
    int aa = i + i;
    int bb = i + i + 1;
    if (ad[aa][bb] && ad[bb][aa]) {
      puts("-1");
      return 0;
    } else if (ad[aa][bb])
      color[bb] = true;
    else if (ad[bb][aa])
      color[aa] = true;
  }
  scanf("%s", s);
  if (solve(0))
    puts(t);
  else
    puts("-1");
  return 0;
}
