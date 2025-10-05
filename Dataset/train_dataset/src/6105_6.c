#include <bits/stdc++.h>
using namespace std;
const int maxn = 210;
struct matrix {
  int M;
  long double a[60][60];
  matrix() { memset(a, 0, sizeof(a)); }
  matrix(int M) : M(M) { memset(a, 0, sizeof(a)); }
  matrix operator*(const matrix& ma) const {
    matrix ret(M);
    for (int i = 1; i <= M; ++i)
      for (int k = 1; k <= M; ++k)
        for (int j = 1; j <= M; ++j) ret.a[i][j] += a[i][k] * ma.a[k][j];
    return ret;
  }
  void setM(int m) { M = m; }
  void I() {
    for (int i = 1; i <= M; ++i) a[i][i] = 1;
  }
} A;
long double dp[60][maxn], a[60][maxn], b[60][maxn], p;
long double f[60][maxn], g[60][maxn];
int n;
matrix qpow(matrix A, int n) {
  matrix ret(A.M);
  ret.I();
  for (; n; n >>= 1, A = A * A)
    if (n & 1) ret = ret * A;
  return ret;
}
int main() {
  int na;
  scanf("%d%d", &n, &na);
  p = (long double)na / (long double)1e9;
  int K = 50;
  for (int i = 1; i <= K; ++i) a[1][i] = p;
  a[2][1] = (1 - p);
  for (int i = 2; i <= K; ++i) a[2][i] = (1 - p) + p * p;
  for (int i = 1; i <= K; ++i) b[2][i] = 1 - p;
  for (int i = 3; i <= K; ++i) {
    for (int j = 1; j <= K; ++j)
      a[i][j] = a[i - 1][j] * a[i - 1][j - 1],
      b[i][j] = b[i - 1][j] * a[i - 1][j - 1];
  }
  for (int i = 1; i <= K; ++i) {
    for (int j = 1; j <= K; ++j)
      f[i][j] = a[i][j] * (1 - a[i][j - 1]),
      g[i][j] = b[i][j] * (1 - a[i][j - 1]);
  }
  dp[1][1] = 1, dp[2][1] = 2;
  for (int j = 2; j <= K; ++j) {
    for (int i = 1; i <= K; ++i) {
      if (i == 1) {
        long double all = 0;
        for (int k = 2; k <= K; ++k) all += g[k][j - 1];
        dp[i][j] = i;
        for (int k = 2; k <= K; ++k)
          dp[i][j] += dp[k][j - 1] * g[k][j - 1] / all;
      } else {
        long double all = 0;
        for (int k = 1; k <= i - 1; ++k) all += f[k][j - 1];
        dp[i][j] = i;
        for (int k = 1; k <= i - 1; ++k)
          dp[i][j] += dp[k][j - 1] * f[k][j - 1] / all;
      }
    }
  }
  if (n <= K) {
    long double ans = 0;
    for (int i = 1; i <= K; ++i) ans += dp[i][n] * f[i][n];
    printf("%.15lf", (double)ans);
  } else {
    long double ans = 0;
    A.setM(K + 1);
    for (int i = 1; i <= K; ++i) {
      if (i == 1) {
        long double all = 0;
        for (int k = 2; k <= K; ++k) all += g[k][K];
        A.a[K + 1][i] = i;
        for (int k = 2; k <= K; ++k) A.a[k][i] += g[k][K] / all;
      } else {
        long double all = 0;
        for (int k = 1; k <= i - 1; ++k) all += f[k][K];
        A.a[K + 1][i] = i;
        for (int k = 1; k <= i - 1; ++k) A.a[k][i] += f[k][K] / all;
      }
    }
    A.a[K + 1][K + 1] = 1;
    A = qpow(A, n - K);
    for (int i = 1; i <= K; ++i) {
      long double sum = 0;
      for (int j = 1; j <= K; ++j) sum += dp[j][K] * A.a[j][i];
      sum += A.a[K + 1][i];
      ans += sum * f[i][K];
    }
    printf("%.15lf", (double)ans);
  }
}
