#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int dp[405][55][55], dp2[105][55][55];
int n, k, a, cnt1 = 0, cnt2 = 0;
int comb[55][55];
int main() {
  comb[0][0] = 1;
  for (int i = 1; i <= 50; i++) {
    comb[i][0] = comb[i][i] = 1;
    for (int j = 1; j < i; j++) {
      comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
    }
  }
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a);
    if (a == 50)
      cnt1++;
    else
      cnt2++;
  }
  memset(dp, -1, sizeof(dp));
  dp[0][0][0] = 0;
  dp2[0][0][0] = 1;
  for (int y = 1; y <= 8 * n; y++) {
    for (int i = 0; i <= cnt1; i++) {
      for (int j = 0; j <= cnt2; j++) {
        if (dp[y - 1][i][j] == -1) continue;
        if (y % 2 == 1) {
          for (int l = 0; l <= cnt1 - i; l++) {
            if (l * 50 > k) continue;
            int rem = k - l * 50;
            for (int r = 0; r <= min(cnt2 - j, rem / 100); r++) {
              if (l + r == 0) continue;
              int ni = i + l, nj = j + r;
              if (dp[y][ni][nj] == -1 || dp[y][ni][nj] > dp[y - 1][i][j] + 1) {
                dp[y][ni][nj] = dp[y - 1][i][j] + 1;
                dp2[y][ni][nj] = (dp2[y - 1][i][j] * 1ll * comb[cnt1 - i][l] %
                                  mod * comb[cnt2 - j][r]) %
                                 mod;
              } else if (dp[y][ni][nj] == dp[y - 1][i][j] + 1) {
                dp2[y][ni][nj] = (dp2[y][ni][nj] + dp2[y - 1][i][j] * 1ll *
                                                       comb[cnt1 - i][l] % mod *
                                                       comb[cnt2 - j][r]) %
                                 mod;
              }
            }
          }
        } else {
          for (int l = 0; l <= i; l++) {
            if (l * 50 > k) continue;
            int rem = k - l * 50;
            for (int r = 0; r <= min(j, rem / 100); r++) {
              if (l + r == 0) continue;
              int ni = i - l, nj = j - r;
              if (dp[y][ni][nj] == -1 || dp[y][ni][nj] > dp[y - 1][i][j] + 1) {
                dp[y][ni][nj] = dp[y - 1][i][j] + 1;
                dp2[y][ni][nj] =
                    (dp2[y - 1][i][j] * 1ll * comb[i][l] % mod * comb[j][r]) %
                    mod;
              } else if (dp[y][ni][nj] == dp[y - 1][i][j] + 1) {
                dp2[y][ni][nj] =
                    (dp2[y][ni][nj] +
                     dp2[y - 1][i][j] * 1ll * comb[i][l] % mod * comb[j][r]) %
                    mod;
              }
            }
          }
        }
      }
    }
  }
  int ans1 = -1, ans2 = 0;
  for (int i = 1; i <= 8 * n; i += 2) {
    if (dp[i][cnt1][cnt2] != -1) {
      ans1 = dp[i][cnt1][cnt2];
      ans2 = dp2[i][cnt1][cnt2];
      break;
    }
  }
  printf("%d\n%d\n", ans1, ans2);
}
