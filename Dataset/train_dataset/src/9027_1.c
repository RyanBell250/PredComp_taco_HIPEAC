#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
const int N = 2e3 + 2;
const int H = 2e5;
int h, w, n, s;
pair<int, int> a[N];
long long ft[H], inv[H], f[2][N];
long long Pow(long long x, long long n) {
  if (n == 1) return x;
  long long t = Pow(x, n / 2);
  t = t * t % MOD;
  return n & 1 ? t * x % MOD : t;
}
void Prep() {
  ft[0] = inv[0] = 1;
  for (int i = 1; i < H; ++i) {
    ft[i] = ft[i - 1] * i % MOD;
    inv[i] = Pow(ft[i], MOD - 2);
  }
}
long long C(int n, int k) { return ft[n] * inv[k] % MOD * inv[n - k] % MOD; }
inline long long CountPath(pair<int, int> a, pair<int, int> b) {
  long long dx = b.first - a.first, dy = b.second - a.second;
  return C(dx + dy, dx);
}
void Solve() {
  sort(a, a + n);
  if (a[n - 1] != pair<int, int>(h, w))
    a[n++] = pair<int, int>(h, w);
  else
    s -= s / 2;
  long long res = 0, tot = CountPath({1, 1}, {h, w});
  for (int k = 0, pre = 0, cur = 1; k <= 21; ++k, swap(pre, cur)) {
    for (int i = 0; i < n; ++i) {
      if (k == 0)
        f[cur][i] = CountPath({1, 1}, a[i]);
      else
        f[cur][i] = 0;
      for (int j = 0; j < i; ++j)
        if (a[j].second <= a[i].second)
          f[cur][i] = (f[cur][i] +
                       (f[pre][j] - f[cur][j] + MOD) * CountPath(a[j], a[i])) %
                      MOD;
    }
    res = (res + f[cur][n - 1] * s) % MOD;
    tot = (tot - f[cur][n - 1] + MOD) % MOD;
    s -= s / 2;
  }
  res += tot;
  res = res * Pow(CountPath({1, 1}, {h, w}), MOD - 2) % MOD;
  printf("%lld", res);
}
int main() {
  scanf("%d %d %d %d", &h, &w, &n, &s);
  for (int i = 0; i < n; ++i) scanf("%d %d", &a[i].first, &a[i].second);
  Prep();
  Solve();
  return 0;
}
