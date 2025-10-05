#include <bits/stdc++.h>
using namespace std;
const int N = 210000;
const long long mod = 998244353;
int n, m;
int a[N];
int w[N];
long long f[2][3100];
long long n0, n1;
long long extended_gcd(long long a, long long b, long long &x, long long &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  } else {
    long long r = extended_gcd(b, a % b, y, x);
    y -= x * (a / b);
    return r;
  }
}
long long inv(long long a) {
  long long xx, yy, d = extended_gcd(a, mod, xx, yy);
  return (xx % mod + mod) % mod;
}
long long fm0[3100], fm1[3100];
long long ff0[3100], ff1[3100];
int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &w[i]);
    if (a[i])
      n1 += w[i];
    else
      n0 += w[i];
  }
  int p = 0;
  f[0][0] = 1;
  for (int i = 0; i < m; i++) {
    memset(f[p ^ 1], 0, sizeof(f[p ^ 1]));
    for (int j = 0; j <= i; j++)
      if (f[p][j]) {
        long long w0 = n0 - j, w1 = n1 + (i - j);
        long long f0 = w0 * inv(w0 + w1) % mod;
        long long f1 = w1 * inv(w0 + w1) % mod;
        f[p ^ 1][j] = (f[p ^ 1][j] + f[p][j] * f1) % mod;
        f[p ^ 1][j + 1] = (f[p ^ 1][j + 1] + f[p][j] * f0) % mod;
      }
    p ^= 1;
  }
  for (int i = 0; i <= m; i++) {
    if (n0 - i <= 0)
      fm0[i] = 0;
    else
      fm0[i] = inv(n0 - i);
    fm1[i] = inv(n1 + i);
  }
  for (int i = m; i >= 1; i--) ff0[i] = (f[p][i] + ff0[i + 1]) % mod;
  for (int i = m; i >= 1; i--) ff1[i] = (f[p][m - i] + ff1[i + 1]) % mod;
  for (int i = 1; i <= n; i++) {
    long long ans = w[i];
    long long sum = w[i];
    for (int j = 0; j < m; j++) {
      if (a[i]) {
        long long fp = sum * fm1[j] % mod;
        sum = (sum * (1 - fp + mod) + (sum + 1) * fp) % mod;
        ans = (ans + fp * ff1[j + 1]) % mod;
      } else {
        long long fp = sum * fm0[j] % mod;
        sum = (sum * (1 - fp + mod) + (sum - 1) * fp) % mod;
        ans = (ans - (fp * ff0[j + 1] % mod) + mod) % mod;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
