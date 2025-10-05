#include <bits/stdc++.h>
using namespace std;
char buf[0xff];
const int inf = 1e9;
int bitcount(int x) {
  int c = 0;
  for (; x; c++) x &= x - 1;
  return c;
}
int bit(int x, int i) {
  if (i < 0) return 0;
  return x >> i & 1;
}
int solve(int n, int m) {
  if (m > n) swap(n, m);
  int maxmask = 1 << m;
  int dp[n + 1][maxmask][maxmask];
  for (int i = 0; i < (int)(n + 1); i++)
    for (int j = 0; j < (int)(maxmask); j++)
      for (int k = 0; k < (int)(maxmask); k++) dp[i][j][k] = inf;
  for (int i = 0; i < (int)(maxmask); i++) dp[0][0][i] = bitcount(i);
  for (int i = 1; i <= n; i++)
    for (int b = 0; b < (int)(maxmask); b++)
      for (int c = 0; c < (int)(maxmask); c++)
        for (int a = 0; a < (int)(maxmask); a++) {
          bool nospider = false;
          for (int j = 0; j < (int)(m); j++)
            if (!(bit(a, j) || bit(c, j) || bit(b, j - 1) || bit(b, j) ||
                  bit(b, j + 1))) {
              nospider = true;
              break;
            }
          if (nospider) continue;
          dp[i][b][c] = min(dp[i][b][c], dp[i - 1][a][b] + bitcount(c));
        }
  int res = inf;
  for (int b = 0; b < (int)(maxmask); b++) res = min(res, dp[n][b][0]);
  return n * m - res;
}
int main() {
  int n, m;
  ios::sync_with_stdio(false);
  while (cin >> n >> m) cout << solve(n, m) << endl;
  return 0;
}
