#include <bits/stdc++.h>
using namespace std;
const long long inf = 4557430888798830399ll;
int n, m, a[25], b[25];
struct node {
  int x, y;
  long long a[25][25];
  node operator*(const node &b) const {
    node c;
    c.x = x, c.y = y;
    memset(c.a, 63, sizeof(c.a));
    for (int i = 0; i < x; i++)
      for (int j = 0; j < y; j++)
        for (int k = 0; k < x; k++)
          c.a[i][j] = min(c.a[i][j], a[i][k] + b.a[k][j]);
    return c;
  }
  void print() {
    printf("%d %d\n", x, y);
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++)
        printf("%lld ", a[i][j] == inf ? -1 : a[i][j]);
      printf("\n");
    }
    printf("---------\n");
  }
} ans, nw;
inline int read() {
  int red = 0, f_f = 1;
  char ch = getchar();
  while (ch > '9' || ch < '0') {
    if (ch == '-') f_f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') red = red * 10 + ch - '0', ch = getchar();
  return red * f_f;
}
void mk(node &t, int a, int b) {
  t.x = n + 1, t.y = n + 1;
  memset(t.a, 63, sizeof(t.a));
  t.a[0][1] = a;
  for (int i = 1; i < n; i++) t.a[i][i - 1] = b, t.a[i][i + 1] = a;
  t.a[n][n - 1] = b;
}
node qpow(node x, int r) {
  node re = x;
  r--;
  while (r) {
    if (r & 1) re = re * x;
    x = x * x, r >>= 1;
  }
  return re;
}
int main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  for (int i = 1; i <= n; i++) b[i] = read();
  mk(ans, a[1], b[1]);
  for (int i = 2; i <= n; i++) {
    mk(nw, a[i], b[i]);
    ans = ans * nw;
  }
  ans = qpow(ans, m);
  printf("%lld\n", ans.a[0][0]);
  return 0;
}
