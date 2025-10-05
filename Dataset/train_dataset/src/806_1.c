#include <bits/stdc++.h>
using namespace std;
const long double PI = 3.14159265359;
const long long MOD = (long long)1e9 + 7;
const long long MAXN = (long long)1e5 + 10;
const long long INF = (long long)9223372036854775;
const long double EPS = (long double)1e-8;
long long fact[MAXN], im[MAXN];
long long pow_mod(long long base, long long power) {
  long long x;
  if (power == 0) return 1;
  if (power == 1) return base % MOD;
  if (power % 2 == 0) {
    x = pow_mod(base, power / 2);
    return (x * x) % MOD;
  }
  x = pow_mod(base, power / 2);
  return (((x * x) % MOD) * base) % MOD;
}
long long C(long long n, long long k) {
  if (k == 0 or k == n) return 1;
  if (k > n) return 0;
  return (((fact[n] * im[k]) % MOD) * im[n - k]) % MOD;
}
long long ps[MAXN], val[MAXN];
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  fact[0] = 1;
  for (int i = 1; i < MAXN; i++) fact[i] = (fact[i - 1] * i) % MOD;
  for (int i = 0; i < MAXN; i++) im[i] = pow_mod(fact[i], MOD - 2);
  val[0] = 1;
  for (int i = 1; i < MAXN; i++) val[i] = (val[i - 1] * 10ll) % MOD;
  long long n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  ps[0] = s[0] - '0';
  for (int i = 1; i < n; i++) ps[i] = ps[i - 1] + (s[i] - '0');
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = ans + ((((C(n - i, k) * (s[n - i] - '0')) % MOD) * val[i - 1]) % MOD);
    ans %= MOD;
    if (i != n)
      ans =
          ans +
          ((((C(n - i - 1, k - 1) * ps[n - i - 1]) % MOD) * val[i - 1]) % MOD);
    ans %= MOD;
  }
  cout << ans;
  return 0;
}
