#include <bits/stdc++.h>
using namespace std;
const long double PI = acos(-1);
const long double eps = 1e-9;
const int seed = 131;
const int M = 1e5 + 7;
const int mod = 1e9 + 7;
long long dp[2][(1 << 19) + 7];
long long a[M], b[M];
int prime[100], id[100], sz, zt[72];
int p[30], c[30];
long long h[M];
long long qpow(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % mod;
    a = a * a % mod;
    b /= 2;
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  long long n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i], b[a[i]]++;
  for (int i = 2; i <= 70; i++) {
    bool f = true;
    for (int j = 2; j <= sqrt(i); j++)
      if (i % j == 0) f = false;
    if (f) prime[++sz] = i, id[i] = sz;
  }
  h[0] = 1;
  for (int i = 1; i <= n; i++) h[i] = h[i - 1] * 2 % mod;
  zt[1] = 0;
  for (int i = 2; i <= 70; i++) {
    long long ans = 0;
    int tp = i;
    for (int j = 2; j <= tp; j++) {
      if (tp % j == 0) {
        int z = 0;
        while (tp % j == 0) tp /= j, z++;
        z = z % 2;
        ans += (1 << (id[j] - 1)) * z;
      }
    }
    zt[i] = ans;
  }
  dp[0 & 1][0] = 1;
  for (int i = 1; i <= 70; i++) {
    int tp = zt[i];
    if (b[i] == 0) {
      for (int j = 0; j < (1 << sz); j++) dp[i & 1][j] = dp[(i - 1) & 1][j];
      continue;
    }
    for (int j = 0; j < (1 << sz); j++) {
      dp[i & 1][j] = dp[(i - 1) & 1][j ^ tp] * h[b[i] - 1] % mod;
      dp[i & 1][j] = (dp[i & 1][j] + dp[(i - 1) & 1][j] * h[b[i] - 1]) % mod;
    }
  }
  long long ans = (dp[70 & 1][0] - 1 + mod) % mod;
  cout << ans << endl;
  return 0;
}
