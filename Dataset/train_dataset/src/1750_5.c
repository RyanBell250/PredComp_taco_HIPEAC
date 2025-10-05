#include <bits/stdc++.h>
using namespace std;
const int P = 1000000007;
inline int Pow(int a, int b) {
  int c = 1;
  for (; b; b >>= 1, a = a * 1ll * a % P)
    if (b & 1) c = c * 1ll * a % P;
  return c;
}
const int N = 65;
int n, m;
int f[N][N];
int g[N][N];
int inv[N << 1], fac[N << 1];
void initfac(int n) {
  fac[0] = 1;
  for (int i = (int)1; i <= (int)n; i++) fac[i] = fac[i - 1] * 1ll * i % P;
  inv[n] = Pow(fac[n], P - 2);
  for (int i = (int)n - 1; i >= (int)0; i--)
    inv[i] = inv[i + 1] * 1ll * (i + 1) % P;
}
int C(int a, int b) {
  if (a < b) return 0;
  int ans = 1;
  for (int i = (int)0; i <= (int)b - 1; i++) ans = ans * 1ll * (a - i) % P;
  return ans * 1ll * inv[b] % P;
}
int main() {
  initfac(100);
  scanf("%d%d", &n, &m);
  g[0][1] = 1;
  for (int i = (int)1; i <= (int)n; i++) {
    for (int j = (int)1; j <= (int)n + 1; j++) {
      for (int k = (int)0; k <= (int)i - 1; k++) {
        int sum0 = 0;
        int sum1 = 0;
        for (int l = (int)j + 1; l <= (int)n + 1; l++) {
          sum0 = (sum0 + g[k][l]) % P;
          sum1 = (sum1 + g[i - 1 - k][l]) % P;
        }
        int w = sum0 * 1ll * g[i - 1 - k][j] % P;
        w = (w + sum1 * 1ll * g[k][j]) % P;
        w = (w + g[i - 1 - k][j] * 1ll * g[k][j]) % P;
        f[i][j] = (f[i][j] + w) % P;
      }
    }
    memset(g, 0, sizeof g);
    g[0][1] = 1;
    for (int d1 = (int)1; d1 <= (int)i; d1++)
      for (int d2 = (int)1; d2 <= (int)n + 1; d2++)
        if (f[d1][d2]) {
          for (int d3 = (int)i; d3 >= (int)d1; d3--)
            for (int d4 = (int)n + 1; d4 >= (int)d2; d4--) {
              int up = min(d3 / d1, d4 / d2);
              for (int c = (int)1; c <= (int)up; c++) {
                int w = C((f[d1][d2] + c - 1) % P, c);
                g[d3][d4] =
                    (g[d3][d4] + g[d3 - d1 * c][d4 - d2 * c] * 1ll * w) % P;
              }
            }
        }
  }
  printf("%d\n", g[n][m]);
  return 0;
}
