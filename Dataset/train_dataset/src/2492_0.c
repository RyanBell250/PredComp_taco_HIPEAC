#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int n, m;
int a[N];
double dp[N][N][N];
long long C[N][N];
double qmod(double a, long long b) {
  double res = 1;
  while (b) {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}
int main() {
  for (int i = 0; i < int(N); i++) {
    C[i][0] = 1;
    for (int j = 1; j < int(i + 1); j++)
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
  }
  scanf("%d%d", &n, &m);
  for (int i = 1; i < int(m + 1); i++) scanf("%d", &a[i]);
  for (int i = 0; i < int(n + 1); i++) dp[0][0][i] = i;
  for (int i = 1; i < int(m + 1); i++) {
    for (int j = 0; j < int(n + 1); j++) {
      for (int k = 0; k < int(n + 1); k++) {
        for (int c = 0; c < int(j + 1); c++) {
          int p = max(k, (c + a[i] - 1) / a[i]);
          dp[i][j][k] +=
              dp[i - 1][j - c][p] * C[j][c] * qmod(i - 1, j - c) / qmod(i, j);
        }
      }
    }
  }
  printf("%.12lf\n", dp[m][n][0]);
  return 0;
}
