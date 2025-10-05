#include <bits/stdc++.h>
using namespace std;
const int N = 42;
int n, m;
int fa[N], siz[N];
long long G[N];
long long f[1 << (N / 2)];
int Find(int x) { return fa[x] = (fa[x] == x ? x : Find(fa[x])); }
void Link(int x, int y) {
  int fx = Find(x), fy = Find(y);
  if (fx != fy) fa[fx] = fy, siz[fy] += siz[fx];
}
int d[N];
long long Check(int x) {
  for (int i = 0; i < n; i++) d[i] = -1;
  queue<int> Q;
  Q.push(x), d[x] = 0;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (int v = 0; v < n; v++)
      if ((G[u] >> v) & 1) {
        if (d[v] == -1) {
          d[v] = d[u] ^ 1;
          Q.push(v);
        } else if (d[v] != d[u] ^ 1)
          return 0;
      }
  }
  return 2;
}
long long Solve1() {
  long long f3 = 1, f5 = 1, f6 = 1, f8 = 1;
  for (int i = 0; i < n; i++)
    if (fa[i] == i) {
      f3 <<= 1;
      if (siz[i] == 1) f5 <<= 1;
      f6 = f6 * Check(i);
      if (siz[i] != 1) f8 = 0;
      f8 <<= 1;
    }
  return -f3 + f5 + f6 + f5 - f8;
}
int mid, lim;
void Dfs1(int d, int mxd, int s1, int s2) {
  if (d == mxd) {
    f[s1]++;
    return;
  }
  Dfs1(d + 1, mxd, s1, s2);
  if (!(s2 & (1LL << d))) Dfs1(d + 1, mxd, s1 | (1LL << d), s2 | G[d]);
}
long long Dfs2(int d, int mxd, long long s) {
  if (d == mxd) {
    s = s & lim, s = s ^ lim;
    return f[s];
  }
  long long ret = Dfs2(d + 1, mxd, s);
  if (!(s & (1LL << d))) ret += Dfs2(d + 1, mxd, s | G[d]);
  return ret;
}
long long Solve2() {
  mid = (n >> 1), lim = (1 << mid) - 1;
  Dfs1(0, mid, 0, 0);
  for (int i = 0; i < mid; i++)
    for (int j = 0; j <= lim; j++)
      if (j & (1LL << i)) f[j] += f[j ^ (1LL << i)];
  return Dfs2(mid, n, 0);
}
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i++) fa[i] = i, siz[i] = 1;
  for (int i = 1, x, y; i <= m; i++) {
    scanf("%d %d", &x, &y);
    x--, y--;
    G[x] |= (1LL << y), G[y] |= (1LL << x);
    Link(x, y);
  }
  printf("%lld\n", (1LL << n) + Solve1() - 2 * Solve2());
  return 0;
}
