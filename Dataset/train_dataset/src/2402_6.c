#include <bits/stdc++.h>
using namespace std;
template <class T>
void read(T& x) {
  char c = getchar();
  T p = 1, n = 0;
  while (c < '0' || c > '9') {
    if (c == '-') p = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    n = n * 10 + c - '0';
    c = getchar();
  }
  x = p * n;
}
template <class T, class U>
void read(T& x, U& y) {
  read(x), read(y);
}
template <class T, class U, class V>
void read(T& x, U& y, V& z) {
  read(x), read(y), read(z);
}
const int maxn = 1000 + 10;
const double eps = 1e-7;
double f[maxn][maxn];
void dfs(int n, int m) {
  if (f[n][m] > eps) return;
  if (m == 0) {
    f[n][m] = 1;
    return;
  }
  if (n == 0) {
    f[n][m] = 1. / ((double)m + 1);
    return;
  }
  dfs(m, n - 1);
  dfs(m - 1, n);
  double p = (m + 1) * f[m][n - 1] / ((double)(m + 1) * f[m][n - 1] + 1);
  f[n][m] = p * (double)m * (1.0 - f[m - 1][n]) / ((double)m + 1) + (1.0 - p);
}
int main() {
  int n, m;
  read(n, m);
  dfs(n, m);
  printf("%.15lf %.15lf\n", f[n][m], 1. - f[n][m]);
  return 0;
}
