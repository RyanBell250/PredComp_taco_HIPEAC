#include <bits/stdc++.h>
using namespace std;
const int N = 105, L = 1e4 + 5;
int n, x;
int a[N];
long double C[N][N];
long double f[N][L];
int main() {
  scanf("%d%d", &n, &x);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    C[i][0] = 1, C[i][i] = 1;
    for (int j = 1; j < i; j++) {
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
    }
  }
  f[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    sum += a[i];
    for (int j = i; j; j--) {
      for (int k = sum; k >= a[i]; k--) {
        f[j][k] += f[j - 1][k - a[i]];
      }
    }
  }
  long double ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= sum; j++) {
      ans += f[i][j] / C[n][i] *
             min((long double)(sum - j) / (n - i),
                 (((long double)0.5) * x * (1.0 * n / (n - i) + 1)));
    }
  }
  printf("%.12lf\n", (double)ans);
  return 0;
}
