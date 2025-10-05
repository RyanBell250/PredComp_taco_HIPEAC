#include <bits/stdc++.h>
using namespace std;
const int N = 30005;
int n, k;
int a[N], f[N][205][4];
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  memset(f, -0x3f, sizeof(f));
  for (int i = 0; i <= n; i++)
    f[i][0][0] = f[i][0][1] = f[i][0][2] = f[i][0][3] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= k; j++) {
      int v = 1 + (j != 1 && j != k);
      f[i][j][0] = max(f[i - 1][j][0], f[i - 1][j - 1][3]) - v * a[i];
      f[i][j][1] = max(f[i - 1][j][1], f[i][j][0]);
      f[i][j][2] = max(f[i - 1][j][2], f[i - 1][j - 1][1]) + v * a[i];
      f[i][j][3] = max(f[i - 1][j][3], f[i][j][2]);
      if (j != 1 && j != k) {
        f[i][j][1] = max(f[i][j][1], f[i - 1][j - 1][1]);
        f[i][j][3] = max(f[i][j][3], f[i - 1][j - 1][3]);
      }
    }
  printf("%d", max(f[n][k][1], f[n][k][3]));
  return 0;
}
