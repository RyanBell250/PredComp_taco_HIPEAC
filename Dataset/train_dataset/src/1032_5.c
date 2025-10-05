#include <bits/stdc++.h>
using namespace std;
int const INF = numeric_limits<int>::max();
long long const LLINF = numeric_limits<long long>::max();
const long double EPS = 1e-9;
long long const N = 3e5 + 5;
long long level[N];
vector<pair<long long, long long>> q[N];
vector<long long> g[N];
long long t[4 * N];
long long p[4 * N];
long long ans[N];
long long n;
void push(long long v) {
  if (p[v]) {
    p[v << 1] += p[v];
    p[v << 1 | 1] += p[v];
    t[v << 1] += p[v];
    t[v << 1 | 1] += p[v];
    p[v] = 0;
  }
}
void update(long long v, long long tl, long long tr, long long l, long long r,
            long long x) {
  if (tl == l && tr == r) {
    t[v] += x;
    p[v] += x;
    return;
  }
  push(v);
  long long mid = tl + tr >> 1;
  if (l <= mid) update(v << 1, tl, mid, l, min(r, mid), x);
  if (r > mid) update(v << 1 | 1, mid + 1, tr, max(l, mid + 1), r, x);
}
long long get(long long v, long long tl, long long tr, long long pos) {
  if (tl == tr) return t[v];
  long long mid = tl + tr >> 1;
  push(v);
  if (pos <= mid)
    return get(v << 1, tl, mid, pos);
  else
    return get(v << 1 | 1, mid + 1, tr, pos);
}
void dfs(long long v, long long par, long long level) {
  for (auto to : q[v]) {
    update(1, 0, n - 1, level, min(level + to.first, n - 1), to.second);
  }
  ans[v] = get(1, 0, n - 1, level);
  for (auto to : g[v]) {
    if (to != par) dfs(to, v, level + 1);
  }
  for (auto to : q[v]) {
    update(1, 0, n - 1, level, min(level + to.first, n - 1), -to.second);
  }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  ;
  cin >> n;
  for (long long i = 0; i < n - 1; i++) {
    long long a, b;
    cin >> a >> b;
    a--, b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  long long m;
  cin >> m;
  for (long long i = 0; i < m; i++) {
    long long v, d, x;
    cin >> v >> d >> x;
    v--;
    q[v].push_back({d, x});
  }
  dfs(0, 0, 0);
  for (long long i = 0; i < n; i++) cout << ans[i] << " ";
}
