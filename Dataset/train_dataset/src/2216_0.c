#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int MX = 200010;
const int N = MX + 10;
const long long oo = 2e18;
long long seg[4 * N], lazy[4 * N], dp[N];
int n, m, a, b, p, cost[N];
vector<pair<int, int> > ed[N];
void push(int n, int s, int e) {
  seg[n] += lazy[n];
  if (s != e) {
    lazy[2 * n] += lazy[n];
    lazy[2 * n + 1] += lazy[n];
  }
  lazy[n] = 0;
}
void update(int n, int s, int e, int l, int r, long long val) {
  push(n, s, e);
  if (s > r || e < l) return;
  if (s >= l && e <= r) {
    lazy[n] += val;
    push(n, s, e);
    return;
  }
  update(2 * n, s, (s + e) / 2, l, r, val);
  update(2 * n + 1, (s + e) / 2 + 1, e, l, r, val);
  seg[n] = max(seg[2 * n], seg[2 * n + 1]);
}
long long get(int n, int s, int e, int l, int r) {
  push(n, s, e);
  if (s > r || e < l) return -1e18;
  if (s >= l && e <= r) {
    return seg[n];
  }
  return max(get(2 * n, s, (s + e) / 2, l, r),
             get(2 * n + 1, (s + e) / 2 + 1, e, l, r));
}
long long res = 0;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", &cost[i]);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d%d", &a, &b, &p);
    ed[b].push_back(make_pair(a, p));
  }
  for (int idx = 1; idx <= n; idx++) {
    update(1, 1, MX, 1, idx, -cost[idx]);
    for (int i = 0; i < ed[idx].size(); i++) {
      pair<int, int> cur = ed[idx][i];
      update(1, 1, MX, 1, cur.first, cur.second);
    }
    dp[idx] = max(dp[idx - 1], get(1, 1, MX, 1, idx));
    update(1, 1, MX, idx + 1, idx + 1, dp[idx]);
  }
  printf("%lld\n", dp[n]);
  return 0;
}
