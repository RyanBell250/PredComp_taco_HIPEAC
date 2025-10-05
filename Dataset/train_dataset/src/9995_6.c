#include <bits/stdc++.h>
using namespace std;
const int maxn = 78000;
int n, m;
int w[4][4];
struct tree {
  int l, r;
  long long f[4][4];
  tree() { memset(f, 0, sizeof(f)); }
} tr[maxn << 2];
void Init() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= 3; i++)
    for (int j = 1; j <= 3; j++) scanf("%d", &w[i][j]);
}
void update(int x) {
  int L = (x << 1), R = ((x << 1) + 1);
  memset(tr[x].f, 0, sizeof(tr[x].f));
  for (int i = 1; i <= 3; i++)
    for (int j = 1; j <= 3; j++)
      for (int k = 1; k <= 3; k++)
        if (w[j][k])
          for (int l = 1; l <= 3; l++) {
            tr[x].f[i][l] += tr[L].f[i][j] * tr[R].f[k][l];
            if (tr[x].f[i][l] >= 777777777) tr[x].f[i][l] %= 777777777;
          }
}
void build(int t, int l, int r) {
  tr[t].l = l, tr[t].r = r;
  if (l == r) {
    for (int i = 1; i <= 3; i++) tr[t].f[i][i] = 1;
    return;
  }
  int mid = (l + r) >> 1;
  build((t << 1), l, mid);
  build(((t << 1) + 1), mid + 1, r);
  update(t);
}
void modify(int t, int x, int c) {
  if (tr[t].l == tr[t].r) {
    memset(tr[t].f, 0, sizeof(tr[t].f));
    if (c != 0)
      tr[t].f[c][c] = 1;
    else
      tr[t].f[1][1] = tr[t].f[2][2] = tr[t].f[3][3] = 1;
    return;
  }
  int mid = (tr[t].l + tr[t].r) >> 1;
  if (x <= mid)
    modify((t << 1), x, c);
  else
    modify(((t << 1) + 1), x, c);
  update(t);
}
void doit() {
  build(1, 1, n);
  for (int i = 1; i <= m; i++) {
    int x, c, ans = 0;
    scanf("%d%d", &x, &c);
    modify(1, x, c);
    for (int i = 1; i <= 3; i++)
      for (int j = 1; j <= 3; j++) {
        ans += tr[1].f[i][j];
        if (ans >= 777777777) ans %= 777777777;
      }
    printf("%d\n", ans);
  }
}
int main() {
  Init();
  doit();
  return 0;
}
