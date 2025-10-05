#include <bits/stdc++.h>
using namespace std;
const int N = 80;
int n, ord[N * 2 + 9], co;
struct seg {
  int l, r;
} a[N + 9];
void into() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &a[i].l, &a[i].r);
    ord[++co] = a[i].l;
    ord[++co] = a[i].r;
  }
}
double dp[N + 9][N + 9][N + 9];
double ans[N + 9][N + 9];
void Divide_dp(const int l, const int r, const int d, const int x, const int y,
               const int c) {
  if (l == r) {
    if (y <= a[l].l || x >= a[l].r) return;
    double v = 1.0 * (y - x) / (a[l].r - a[l].l);
    for (int i = 0; i < n; ++i)
      for (int j = 0; i + j < n; ++j) {
        int c = n - i - j;
        double t = v / c * dp[d][i][j];
        ans[l][i + 1] += t;
        ans[l][i + c + 1] -= t;
      }
    return;
  }
  int mid = l + r >> 1, lc = c, rc = c;
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= n; ++j) dp[d + 1][i][j] = dp[d][i][j];
  for (int id = mid + 1; id <= r; ++id) {
    int tl = a[id].l, tr = a[id].r;
    double u = 1.0 * (y - x) / (tr - tl),
           v = 1.0 * (min(x, tr) - tl) / (tr - tl),
           w = 1.0 * (tr - max(y, tl)) / (tr - tl);
    ++lc;
    for (int i = lc; i >= 0; --i)
      for (int j = lc; j >= 0; --j) {
        dp[d + 1][i][j] = x >= tl && y <= tr ? dp[d + 1][i][j] * u : 0;
        if (i && tl < x) dp[d + 1][i][j] += dp[d + 1][i - 1][j] * v;
        if (j && tr > y) dp[d + 1][i][j] += dp[d + 1][i][j - 1] * w;
      }
  }
  Divide_dp(l, mid, d + 1, x, y, lc);
  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= n; ++j) dp[d + 1][i][j] = dp[d][i][j];
  for (int id = l; id <= mid; ++id) {
    int tl = a[id].l, tr = a[id].r;
    double u = 1.0 * (y - x) / (tr - tl),
           v = 1.0 * (min(x, tr) - tl) / (tr - tl),
           w = 1.0 * (tr - max(y, tl)) / (tr - tl);
    ++rc;
    for (int i = rc; i >= 0; --i)
      for (int j = rc; j >= 0; --j) {
        dp[d + 1][i][j] = x >= tl && y <= tr ? dp[d + 1][i][j] * u : 0;
        if (i && tl < x) dp[d + 1][i][j] += dp[d + 1][i - 1][j] * v;
        if (j && tr > y) dp[d + 1][i][j] += dp[d + 1][i][j - 1] * w;
      }
  }
  Divide_dp(mid + 1, r, d + 1, x, y, rc);
}
void Get_ans() {
  sort(ord + 1, ord + co + 1);
  co = unique(ord + 1, ord + co + 1) - ord - 1;
  for (int i = 1; i < co; ++i) {
    dp[0][0][0] = 1;
    Divide_dp(1, n, 0, ord[i], ord[i + 1], 0);
  }
}
void work() { Get_ans(); }
void outo() {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) printf("%.7lf ", (ans[i][j] += ans[i][j - 1]));
    putchar('\n');
  }
}
int main() {
  into();
  work();
  outo();
  return 0;
}
