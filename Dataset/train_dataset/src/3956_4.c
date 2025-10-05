#include <bits/stdc++.h>
using namespace std;
int read() {
  int ans = 0, w = 1;
  char s = getchar();
  while (!isdigit(s)) {
    if (s == '-') w = -1;
    s = getchar();
  }
  while (isdigit(s)) {
    ans = ans * 10 + s - '0';
    s = getchar();
  }
  return ans * w;
}
const int MOD = 1e9 + 7;
long long Pow(long long a, int o) {
  long long ans = 1;
  while (o) {
    if (o & 1) ans = (ans * a) % MOD;
    a = (a * a) % MOD;
    o >>= 1;
  }
  return ans;
}
int n, k;
long long jc[1000500], ny[1000500];
long long C(long long n, long long m) {
  if (n > m) return 0;
  return jc[m] * ny[n] % MOD * ny[m - n] % MOD;
}
long long dp[1000500];
int main() {
  n = read();
  k = read();
  jc[0] = 1;
  for (int i = 1; i <= n; ++i) jc[i] = (jc[i - 1] * i) % MOD;
  ny[n] = Pow(jc[n], MOD - 2);
  for (int i = n; i >= 1; --i) ny[i - 1] = (ny[i] * i) % MOD;
  dp[0] = 1;
  long long Sum = 1, ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (i - k - 1 >= 0)
      Sum -= dp[i - k - 1] * ny[i - k - 1] % MOD, Sum = (Sum + MOD) % MOD;
    dp[i] = jc[i - 1] * Sum % MOD;
    Sum = (Sum + dp[i] * ny[i]) % MOD;
    ans = (ans + dp[i - 1] * C(n - i, n - 1) % MOD * jc[n - i]) % MOD;
  }
  printf("%lld\n", (jc[n] - ans + MOD) % MOD);
  return 0;
}
