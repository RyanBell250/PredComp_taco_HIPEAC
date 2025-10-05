#include <bits/stdc++.h>
using namespace std;
int a[1003];
int b[1003];
int n, p, k;
int dp[2][1002][55][55];
short int max(short int a, int b) { return a > b ? a : b; }
int main() {
  scanf("%d %d %d", &n, &p, &k);
  int u, x;
  scanf("%d", &x);
  while (x--) {
    scanf("%d", &u);
    a[u - 1] = 1;
  }
  scanf("%d", &x);
  while (x--) {
    scanf("%d", &u);
    b[u - 1] = 1;
  }
  p = min(p, 2 * ((n + k - 1) / k));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= p; j++) {
      for (int l = 0; l < k; l++) {
        for (int r = 0; r < k; r++) {
          int &ans = dp[(i) % 2][j][l][r];
          ans = 0;
          int prox = (i + 1) % 2;
          if (j < p) {
            {
              if (r > 0)
                ans = max(ans, (a[i] | b[i]) + dp[prox][j + 1][k - 1][r - 1]);
              else
                ans = max(ans, a[i] + dp[prox][j + 1][k - 1][0]);
            }
            {
              if (l > 0)
                ans = max(ans, (a[i] | b[i]) + dp[prox][j + 1][l - 1][k - 1]);
              else
                ans = max(ans, b[i] + dp[prox][j + 1][0][k - 1]);
            }
          }
          if (l > 0 && r > 0) {
            ans = max(ans, (a[i] | b[i]) + dp[prox][j][l - 1][r - 1]);
          } else if (l > 0 && r == 0)
            ans = max(ans, a[i] + dp[prox][j][l - 1][0]);
          else if (l == 0 && r > 0) {
            ans = max(ans, b[i] + dp[prox][j][0][r - 1]);
          } else if (l == 0 && r == 0) {
            ans = max(ans, dp[prox][j][0][0]);
          }
        }
      }
    }
  }
  printf("%d\n", dp[0][0][0][0]);
  return 0;
}
