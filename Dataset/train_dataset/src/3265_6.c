#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using TP = tuple<ll, ll, ll>;
void init_io() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  cout << fixed << setprecision(18);
}
const ll MAX = 210;
const ll MINF = -1e15;
ll dp[MAX][MAX] = {};
template <typename Monoid>
struct SegmentTree {
  using F = function<Monoid(Monoid, Monoid)>;
  int sz;
  vector<Monoid> seg;
  const F f;
  const Monoid M;
  SegmentTree(int n, const F f, const Monoid &M) : f(f), M(M) {
    sz = 1;
    while (sz < n) sz <<= 1;
    seg.assign(sz * 2, M);
  }
  void set(int k, const Monoid &v) { seg[k + sz] = v; }
  void build() {
    for (int k = sz - 1; k > 0; k--) {
      seg[k] = f(seg[2 * k], seg[2 * k + 1]);
    }
  }
  void update(int k, const Monoid &v) {
    k += sz;
    seg[k] = v;
    while (k >>= 1) {
      seg[k] = f(seg[2 * k], seg[2 * k + 1]);
    }
  }
  Monoid que(int a, int b) {
    Monoid L = M, R = M;
    for (a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
      if (a & 1) L = f(L, seg[a++]);
      if (b & 1) R = f(seg[--b], R);
    }
    return f(L, R);
  }
  Monoid operator[](const int &k) const { return seg[k + sz]; }
};
signed main() {
  init_io();
  ll n, k, x;
  cin >> n >> k >> x;
  vector<ll> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      dp[i][j] = MINF;
    }
  }
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= x; j++) {
      for (int l = 1; l <= k; l++) {
        if (i - l < 0) break;
        if (dp[i - l][j - 1] == MINF) continue;
        dp[i][j] = max(dp[i][j], dp[i - l][j - 1] + a[i - 1]);
      }
    }
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= x; j++) {
      if (dp[i][j] == MINF) dp[i][j] = -1;
    }
  }
  ll ans = MINF;
  for (int i = n - k + 1; i <= n; i++) {
    for (int j = 0; j <= x; j++) {
      ans = max(ans, dp[i][j]);
    }
  }
  if (ans == MINF) ans = -1;
  cout << ans << endl;
}
