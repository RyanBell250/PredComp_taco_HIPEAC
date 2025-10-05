#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7, N = 1e6;
int n, k, m, fac[200005], inv[200005], phi[N + 5], cnt[N + 5], ans;
void Pre() {
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i <= n + m; i++)
    fac[i] = 1ll * fac[i - 1] * i % mod,
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
  for (int i = 2; i <= n + m; i++) inv[i] = 1ll * inv[i] * inv[i - 1] % mod;
  phi[1] = 1;
  static int p[N / 5], cnt = 0;
  static bool v[N + 5];
  for (int i = 2; i <= N; i++) {
    if (!v[i]) p[++cnt] = i, phi[i] = i - 1;
    for (int j = 1, k; j <= cnt && (k = i * p[j]) <= N; j++) {
      v[k] = 1;
      if (i % p[j] == 0) {
        phi[k] = phi[i] * p[j];
        break;
      }
      phi[k] = phi[i] * (p[j] - 1);
    }
  }
}
int C(int n, int m) { return 1ll * fac[n] * inv[m] % mod * inv[n - m] % mod; }
void ins(int x) {
  for (int i = 1; i * i <= x; i++)
    if (x % i == 0) {
      if (++cnt[i] >= k)
        ans = (ans + 1ll * C(cnt[i] - 1, k - 1) * phi[i]) % mod;
      if (i * i != x && ++cnt[x / i] >= k)
        ans = (ans + 1ll * C(cnt[x / i] - 1, k - 1) * phi[x / i]) % mod;
    }
}
int main() {
  scanf("%d%d%d", &n, &k, &m);
  Pre();
  for (int i = 1, x; i <= n; i++) scanf("%d", &x), ins(x);
  for (int i = 1, x; i <= m; i++)
    scanf("%d", &x), ins(x), printf("%d\n", (ans + mod) % mod);
}
