#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 2e5 + 5;
long long jc[maxn], inv[maxn];
long long qp(long long x, long long y) {
  long long res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    y >>= 1;
    x = x * x % mod;
  }
  return res;
}
void pre() {
  jc[0] = 1;
  for (int i = 1; i < maxn; i++) {
    jc[i] = jc[i - 1] * i % mod;
  }
  inv[maxn - 1] = qp(jc[maxn - 1], mod - 2);
  for (int i = maxn - 1; i > 0; i--) {
    inv[i - 1] = inv[i] * i % mod;
  }
}
long long C(int n, int m) {
  if (n < m) return 0;
  return jc[n] * inv[n - m] % mod * inv[m] % mod;
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  pre();
  long long tmp = C(m, n - 1) * (n - 2) % mod, ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = (ans + tmp * C(n - 2, i - 1) % mod) % mod;
  }
  printf("%lld\n", ans * qp(2, mod - 2) % mod);
  return 0;
}
