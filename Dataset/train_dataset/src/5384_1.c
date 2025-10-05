#include <bits/stdc++.h>
using namespace std;
const long long mod = 998244353;
long long inv(long long i) {
  if (i == 1) return 1;
  return (mod - ((mod / i) * inv(mod % i)) % mod) % mod;
}
long long mod_mul(long long a, long long b) {
  a = a % mod;
  b = b % mod;
  return (((a * b) % mod) + mod) % mod;
}
long long mod_add(long long a, long long b) {
  a = a % mod;
  b = b % mod;
  return (((a + b) % mod) + mod) % mod;
}
long long gcd(long long a, long long b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
long long ceil_div(long long a, long long b) {
  return a % b == 0 ? a / b : a / b + 1;
}
long long pwr(long long a, long long b) {
  a %= mod;
  long long res = 1;
  while (b > 0) {
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return res;
}
long long N = 200005;
vector<long long> fact(N + 1, 1);
vector<long long> ifact(N + 1, 1);
long long C(long long n, long long r) {
  if (r > n) return 0;
  long long ans = fact[n];
  ans = mod_mul(ans, ifact[r]);
  ans = mod_mul(ans, ifact[n - r]);
  return ans;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t, n, i, j, ans, temp, sum;
  string sans;
  t = 1;
  for (i = 2; i <= N; i++) {
    fact[i] = mod_mul(fact[i - 1], i);
  }
  ifact[N] = inv(fact[N]);
  for (i = N - 1; i > 0; i--) {
    ifact[i] = mod_mul(i + 1, ifact[i + 1]);
  }
  while (t--) {
    sans = "NO";
    ans = temp = sum = 0;
    cin >> n;
    long long b, w;
    vector<string> a(n + 1);
    b = w = 0;
    for (i = 1; i <= n; i++) {
      cin >> a[i];
      for (j = 0; j <= 1; j++) {
        if (a[i][j] == 'W')
          w++;
        else if (a[i][j] == 'B')
          b++;
      }
    }
    if (w > n or b > n) {
      cout << 0;
      continue;
    }
    ans = C(2 * n - w - b, n - w);
    long long tot, sub1, sub2;
    tot = sub1 = sub2 = 1;
    for (i = 1; i <= n; i++) {
      if (a[i][0] == '?' and a[i][1] == '?') {
        tot = mod_mul(tot, 2LL);
      } else if (a[i][0] == a[i][1]) {
        tot = 0;
      }
    }
    for (i = 1; i <= n; i++) {
      if (a[i][0] == 'W' or a[i][1] == 'B') sub1 = 0;
      if (a[i][0] == 'B' or a[i][1] == 'W') sub2 = 0;
    }
    long long tot_sub = (tot - sub1 - sub2 + 5 * mod) % mod;
    ans = (ans - tot_sub + mod) % mod;
    cout << ans;
  }
  return 0;
}
