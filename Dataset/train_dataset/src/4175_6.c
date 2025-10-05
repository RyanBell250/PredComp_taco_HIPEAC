#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x) {
  x = 0;
  char c = getchar();
  bool flag = false;
  while (!isdigit(c)) {
    if (c == '-') flag = true;
    c = getchar();
  }
  while (isdigit(c)) {
    x = (x << 1) + (x << 3) + (c ^ 48);
    c = getchar();
  }
  if (flag) x = -x;
}
int n;
int siz[110];
double fac[110], f[110][110], g[110];
struct edge {
  int to, nxt;
  edge(int a = 0, int b = 0) { to = a, nxt = b; }
} e[110];
int head[110], edge_cnt;
void add(int from, int to) {
  e[++edge_cnt] = edge(to, head[from]), head[from] = edge_cnt;
}
double C(int n, int m) { return fac[n] / fac[m] / fac[n - m]; }
void dfs(int x, int fa) {
  f[x][0] = siz[x] = 1;
  for (int i = head[x]; i; i = e[i].nxt) {
    int y = e[i].to;
    if (y == fa) continue;
    dfs(y, x);
    for (int j = 0; j <= siz[y]; ++j)
      for (int k = 1; k <= siz[y]; ++k)
        f[0][j] += k <= j ? f[y][k - 1] / 2 : f[y][j];
    for (int j = siz[x] - 1; j >= 0; --j)
      for (int k = siz[y]; k >= 0; --k)
        g[j + k] += f[x][j] * f[0][k] * C(j + k, j) *
                    C(siz[x] - 1 - j + siz[y] - k, siz[x] - 1 - j);
    siz[x] += siz[y];
    for (int i = 0; i < siz[x]; ++i) f[x][i] = g[i];
    memset(g, 0, sizeof(g)), memset(f[0], 0, sizeof(f[0]));
  }
}
int main() {
  read(n);
  for (int i = 1; i < n; ++i) {
    int x, y;
    read(x), read(y);
    add(x, y), add(y, x);
  }
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
  for (int i = 1; i <= n; ++i) {
    memset(f, 0, sizeof(f)), dfs(i, 0);
    printf("%.10lf\n", f[i][n - 1] / fac[n - 1]);
  }
  return 0;
}
