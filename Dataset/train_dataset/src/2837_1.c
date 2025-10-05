#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
int n, cnt[100005], sum, f[100005], ans;
inline long long fpow(long long x, int k) {
  long long ret = 1;
  while (k) {
    if (k & 1) ret = ret * x % mod;
    x = x * x % mod;
    k >>= 1;
  }
  return ret;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &cnt[i]), sum += cnt[i];
  f[1] = 1ll * (sum - 1) * (sum - 1) % mod * fpow(sum, mod - 2) % mod;
  f[2] = (2ll * f[1] + mod - 1) % mod;
  for (int i = 2; i < 100005 - 1; ++i)
    f[i + 1] = ((2ll * f[i] % mod - f[i - 1] + mod) % mod -
                1ll * (sum - 1) * fpow(sum - i, mod - 2) % mod + mod) %
               mod;
  for (int i = 1; i <= n; ++i) (ans += f[cnt[i]]) %= mod;
  printf("%d\n", ans);
  return 0;
}
