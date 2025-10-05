#include <bits/stdc++.h>
using namespace std;
int const maxn = 35;
int const maxk = 205;
int p[maxn];
double ans[maxn][maxn][maxk];
int to(int x, int l, int r) {
  if (x < l || x > r) return x;
  return l + r - x;
}
double solve(int n, int i, int j, int k) {
  if (k == 0) {
    if (p[i] > p[j])
      return 1.0;
    else
      return 0.0;
  }
  if (ans[i][j][k] >= 0) return ans[i][j][k];
  double koef = 2.0 / (n * (n + 1));
  double ret = 0.0;
  for (int l = 1; l <= n; ++l)
    for (int r = l; r <= n; ++r) {
      ret += koef * solve(n, to(i, l, r), to(j, l, r), k - 1);
    }
  ans[i][j][k] = ret;
  return ret;
}
int main() {
  ios_base::sync_with_stdio(false);
  cout << fixed << setprecision(10);
  for (int i = 0; i < (int)(maxn); ++i)
    for (int j = 0; j < (int)(maxn); ++j)
      for (int k = 0; k < (int)(maxk); ++k) ans[i][j][k] = -1.0;
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < (int)(n); ++i) cin >> p[i + 1];
  double ans = 0.0;
  for (int i = 1; i <= n; ++i)
    for (int j = i + 1; j <= n; ++j) ans += solve(n, i, j, k);
  cout << ans << endl;
  return 0;
}
