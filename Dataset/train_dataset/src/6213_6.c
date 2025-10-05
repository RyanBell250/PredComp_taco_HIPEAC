#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000 * 1000 * 1000 + 7;
long long mod(long long n) {
  if (n < 0) {
    return (n % MOD + MOD) % MOD;
  } else {
    if (n < MOD)
      return n;
    else if (n < 2 * MOD)
      return n - MOD;
    else
      return n % MOD;
  }
}
long long fp(long long a, long long p) {
  long long ans = 1, cur = a;
  for (long long i = 0; (1ll << i) <= p; ++i) {
    if ((p >> i) & 1) ans = mod(ans * cur);
    cur = mod(cur * cur);
  }
  return ans;
}
long long dv(long long a, long long b) { return mod(a * fp(b, MOD - 2)); }
const long long N = 103;
long long m[N][N], ans[N][N], t[N][N];
void add(long long a[N][N], long long b[N][N]) {
  for (long long i = 0; i < N; ++i) {
    for (long long j = 0; j < N; ++j) {
      t[i][j] = 0;
    }
  }
  for (long long i = 0; i < N; ++i) {
    for (long long j = 0; j < N; ++j) {
      for (long long k = 0; k < N; ++k) {
        t[i][j] = mod(t[i][j] + a[i][k] * b[k][j]);
      }
    }
  }
  for (long long i = 0; i < N; ++i) {
    for (long long j = 0; j < N; ++j) {
      a[i][j] = t[i][j];
    }
  }
}
void pw(long long p) {
  for (long long i = 0; i < N; ++i) ans[i][i] = 1;
  for (long long i = 0; (1ll << i) <= p; ++i) {
    if ((p >> i) & 1) add(ans, m);
    add(m, m);
  }
}
bool a[N];
long long cnt[2];
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long long n, k;
  cin >> n >> k;
  for (long long i = 0; i < n; ++i) {
    cin >> a[i];
    ++cnt[a[i]];
  }
  long long l = cnt[0];
  long long r = n - l;
  long long op = n * (n - 1) / 2;
  for (long long l1 = 0; l1 <= cnt[0] && l1 <= cnt[1]; ++l1) {
    long long l0 = l - l1;
    long long r0 = cnt[0] - l0;
    long long r1 = cnt[1] - l1;
    m[l1][l1] = op;
    if (l1) {
      m[l1][l1 - 1] = mod(l1 * r0);
      m[l1][l1] = mod(m[l1][l1] - m[l1][l1 - 1]);
    }
    m[l1][l1 + 1] = mod(l0 * r1);
    m[l1][l1] = mod(m[l1][l1] - m[l1][l1 + 1]);
  }
  pw(k);
  long long sum = 0;
  for (long long i = 0; i < l; ++i) sum += a[i];
  cout << dv(ans[sum][0], fp(op, k)) << '\n';
}
