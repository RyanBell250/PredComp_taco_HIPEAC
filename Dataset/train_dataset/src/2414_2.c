#include <bits/stdc++.h>
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
constexpr int kN = 9, kL = 10001000;
int f[2][kN][kN];
int n, m, cnt[kL];
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    int x;
    std::cin >> x;
    ++cnt[x];
  }
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    while (cnt[i] > 8) {
      ++ans;
      cnt[i] -= 3;
    }
  }
  int idx = 0;
  memset(f, -127, sizeof(f));
  f[idx][cnt[1]][cnt[2]] = 0;
  for (int l = 3; l <= m; ++l) {
    memset(f[!idx], -127, sizeof(f[!idx]));
    for (int i = 0; i < kN; ++i) {
      for (int j = 0; j < kN; ++j) {
        if (f[idx][i][j] >= 0) {
          int up = std::min({i, j, cnt[l]});
          for (int k = 0; k <= up; ++k) {
            int &x = f[!idx][j - k][cnt[l] - k];
            x = std::max(x, f[idx][i][j] + k + (i - k) / 3);
          }
        }
      }
    }
    idx = !idx;
  }
  int tmp = 0;
  for (int i = 0; i < kN; ++i) {
    for (int j = 0; j < kN; ++j) {
      if (f[idx][i][j] >= 0) {
        tmp = std::max(tmp, f[idx][i][j] + i / 3 + j / 3);
      }
    }
  }
  ans += tmp;
  std::cout << ans << std::endl;
}
