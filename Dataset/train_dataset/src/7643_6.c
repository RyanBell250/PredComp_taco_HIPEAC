#include <bits/stdc++.h>
using namespace std;
const int T = 998244353;
const int maxn = 4000;
long long fac[maxn], inv[maxn];
int exgcd(int a, int b, int& x, int& y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  int d = exgcd(b, a % b, y, x);
  y -= (a / b) * x;
  return d;
}
void init() {
  fac[0] = inv[0] = 1;
  for (int i = 1; i < maxn; i++) {
    fac[i] = fac[i - 1] * i % T;
    int x, y;
    exgcd(i, T, x, y);
    x = (x + T) % T;
    inv[i] = inv[i - 1] * x % T;
  }
}
inline long long C(int n, int k) {
  if (k > n) return 0;
  return fac[n] * inv[k] % T * inv[n - k] % T;
}
long long f[maxn], g[maxn], sum[maxn], dp[maxn][maxn];
bool vr[maxn], vc[maxn];
vector<int> r, c;
void work(vector<int> a, long long* f) {
  memset(sum, 0, sizeof(sum));
  memset(dp, 0, sizeof(dp));
  int n = a.size();
  a.insert(a.begin(), -1);
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    if (a[i] == a[i - 1] + 1) {
      for (int j = 0; j < n; j++) sum[j] = (sum[j] + dp[i - 2][j]) % T;
    }
    dp[i][0] = 1;
    for (int j = 1; j <= n; j++) dp[i][j] = sum[j - 1];
  }
  for (int i = 0; i <= n; i++) f[i] = dp[n][i];
}
int main() {
  init();
  int h, w, tot;
  cin >> h >> w >> tot;
  for (int i = 1; i <= tot; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    vr[x] = vc[y] = 1;
    scanf("%d%d", &x, &y);
    vr[x] = vc[y] = 1;
  }
  for (int i = 1; i <= h; i++)
    if (!vr[i]) r.push_back(i);
  for (int i = 1; i <= w; i++)
    if (!vc[i]) c.push_back(i);
  work(r, f);
  work(c, g);
  long long ans = 0;
  int n = r.size(), m = c.size();
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n - 2 * i; j++) {
      if (m - 2 * j < i) continue;
      ans = (ans + f[i] * g[j] % T * C(n - 2 * i, j) % T * C(m - 2 * j, i) % T *
                       fac[i] % T * fac[j] % T) %
            T;
    }
  cout << ans << endl;
  return 0;
}
