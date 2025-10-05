#include <bits/stdc++.h>
using namespace std;
void du(long long& d) {
  char t = getchar();
  bool Mark = false;
  for (; t < '0' || t > '9'; t = getchar())
    if (t == '-') Mark = !Mark;
  for (d = 0; t >= '0' && t <= '9'; t = getchar()) d = d * 10 + t - '0';
  if (Mark) d = -d;
}
const int maxn = 100 + 10;
const int maxp = 10000 + 100;
const long long Mod = 1e9 + 7;
long long sum[maxn];
long long dp[maxn][maxp];
long long x[maxn], y[maxn];
long long inv[maxp], fact[maxp];
long long Montgomery(long long a, long long b, long long c);
long long cal_com(long long m, long long k);
void pre(int n);
int main() {
  long long M;
  du(M);
  long long i, j, k;
  for (i = 1; i <= M; i++) du(x[i]);
  for (i = 1; i <= M; i++) du(y[i]);
  for (i = 1; i <= M; i++) sum[i] = sum[i - 1] + x[i];
  pre(sum[M]);
  long long ans = fact[sum[M]];
  for (i = 1; i <= M; i++) ans = ans * inv[x[i]] % Mod;
  dp[0][0] = 1;
  for (i = 1; i <= M; i++) {
    for (j = 0; j <= sum[i]; j++) {
      for (k = 0; k <= y[i] && k <= j; k++) {
        dp[i][j] += dp[i - 1][j - k] * cal_com(sum[i] - (j - k), k) % Mod;
        if (dp[i][j] >= Mod) dp[i][j] -= Mod;
      }
    }
  }
  ans = ans * dp[M][sum[M]] % Mod;
  cout << ans;
}
long long Montgomery(long long a, long long b, long long c) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % c;
    a = a * a % c;
    b >>= 1;
  }
  return ans;
}
void pre(int n) {
  fact[0] = fact[1] = 1;
  inv[0] = inv[1] = 1;
  for (long long i = 2; i <= n; i++) {
    fact[i] = fact[i - 1] * i % Mod;
    inv[i] = inv[i - 1] * Montgomery(i, Mod - 2, Mod) % Mod;
  }
}
long long cal_com(long long n, long long k) {
  long long ans = fact[n] * inv[k] % Mod * inv[n - k] % Mod;
  return ans;
}
