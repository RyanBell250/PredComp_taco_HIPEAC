#include <bits/stdc++.h>
using namespace std;
template <class T>
bool chmax(T &a, const T &b) {
  return (a < b) ? (a = b, 1) : 0;
}
template <class T>
bool chmin(T &a, const T &b) {
  return (b < a) ? (a = b, 1) : 0;
}
using ll = long long;
using R = long double;
const R EPS = 1e-9L;
inline int sgn(const R &r) { return (r > EPS) - (r < -EPS); }
inline R sq(R x) { return sqrt(max(x, 0.0L)); }
const int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
const int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
const ll mod = 1000000007LL;
const int limit = 1000;
ll dp[limit + 10][2 * limit + 10];
ll power(ll a, ll n) {
  ll b = 1LL;
  while (n) {
    if (n & 1) b = b * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return b;
}
int main(void) {
  ll k, pa, pb;
  cin >> k >> pa >> pb;
  const ll ips = power(pa + pb, mod - 2);
  dp[1][0] = 1LL;
  for (int i = int(1); i < int(k); ++i)
    for (int j = int(0); j < int(k); ++j) {
      {
        ll add = dp[i][j] * pa % mod * ips % mod;
        dp[i + 1][j] = (dp[i + 1][j] + add) % mod;
      }
      {
        ll add = dp[i][j] * pb % mod * ips % mod;
        dp[i][j + i] = (dp[i][j + i] + add) % mod;
      }
    }
  ll ans = 0LL;
  for (int i = int(0); i < int(k); ++i) {
    for (int j = int(k); j < int(2 * k + 1); ++j) {
      ll add = 1LL * j * dp[i][j] % mod;
      ans = (ans + add) % mod;
    }
  }
  const ll val = 1LL * pa * power(pb, mod - 2) % mod;
  for (int j = int(0); j < int(k); ++j) {
    ll add = 1LL * (j + k + val) * dp[k][j] % mod;
    ans = (ans + add) % mod;
  }
  cout << ans << endl;
  return 0;
}
