#include <bits/stdc++.h>
using namespace std;
long long read() {
  long long xx = 0, flagg = 1;
  char ch = getchar();
  while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
  if (ch == '-') {
    flagg = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    xx = xx * 10 + ch - '0';
    ch = getchar();
  }
  return xx * flagg;
}
void pus(long long xx, long long flagg) {
  if (xx < 0) {
    putchar('-');
    xx = -xx;
  }
  if (xx >= 10) pus(xx / 10, 0);
  putchar(xx % 10 + '0');
  if (flagg == 1) putchar(' ');
  if (flagg == 2) putchar('\n');
  return;
}
int n, m, flag, i, j, k, l, a[1005], f[1005][1005], sum[1005][1005],
    ans[100005], ans2;
int add(int u, int v) { return u + v >= 998244353 ? u + v - 998244353 : u + v; }
int minn(int u, int v) { return u < v ? u : v; }
int main() {
  n = read();
  m = read();
  for (i = 1; i <= n; i++) {
    a[i] = read();
  }
  sort(a + 1, a + n + 1);
  for (k = 1; k <= 100000 && m <= 100000 / k + 1; k++) {
    l = 0;
    f[0][0] = 1;
    sum[0][0] = 1;
    for (i = 1; i <= n; i++) {
      while (a[i] - a[l + 1] >= k) l++;
      for (j = 1; j <= i && j <= m; j++) {
        if (l >= j - 1)
          f[i][j] = sum[l][j - 1];
        else
          f[i][j] = 0;
        sum[i][j] = add(sum[i - 1][j], f[i][j]);
      }
      sum[i][0] = 1;
    }
    ans[k] = sum[n][m];
  }
  for (i = 100000; i >= 1; i--)
    ans2 = (ans2 + 1LL * (ans[i] - ans[i + 1] + 998244353) * i % 998244353) %
           998244353;
  pus(ans2, 2);
  return 0;
}
