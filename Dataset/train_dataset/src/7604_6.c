#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18 + 9;
const long double EPS = 1e-6;
long long qread() {
  char c = getchar();
  long long neg = 1;
  long long val = 0;
  while (c != '-' && !isdigit(c)) c = getchar();
  if (c == '-') {
    c = getchar();
    neg = -1;
  }
  while (isdigit(c)) {
    val = (val << 3) + (val << 1) + c - '0';
    c = getchar();
  }
  return neg * val;
}
long long n, m, p;
const long long N = 1000020;
struct W {
  long long a, c;
  W(long long a = 0, long long c = 0) : a(a), c(c) {}
} X[N], x[N];
struct D {
  long long d, c;
  D(long long d = 0, long long c = 0) : d(d), c(c) {}
} Y[N], y[N];
struct M {
  long long a, d, p;
  M(long long a = 0, long long d = 0, long long p = 0) : a(a), d(d), p(p) {}
} z[N];
class SegmentTree {
 private:
  long long lc[N], rc[N], lazy[N];
  void pushup(long long p) { t[p] = max(t[(p << 1)], t[(p << 1 | 1)]); }
  void pushdown(long long p) {
    if (lazy[p]) {
      lazy[(p << 1)] += lazy[p];
      lazy[(p << 1 | 1)] += lazy[p];
      t[(p << 1)] += lazy[p];
      t[(p << 1 | 1)] += lazy[p];
      lazy[p] = 0;
    }
  }
 public:
  long long t[N];
  void build(long long l, long long r, long long p = 1) {
    lc[p] = l;
    rc[p] = r;
    if (l == r) {
      t[p] = -x[l].c;
      return;
    }
    long long mid = (l + r) >> 1;
    build(l, mid, (p << 1));
    build(mid + 1, r, (p << 1 | 1));
    pushup(p);
  }
  long long query() { return t[1]; }
  void modify(long long l, long long r, long long v, long long p = 1) {
    if (l <= lc[p] && rc[p] <= r) {
      t[p] += v;
      lazy[p] += v;
      return;
    } else if (l > rc[p] || r < lc[p])
      return;
    pushdown(p);
    modify(l, r, v, (p << 1));
    modify(l, r, v, (p << 1 | 1));
    pushup(p);
  }
} seg;
long long a[N];
void solve() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> p;
  for (long long i = 1; i <= (long long)n; i++) cin >> X[i].a >> X[i].c;
  for (long long i = 1; i <= (long long)m; i++) cin >> Y[i].d >> Y[i].c;
  for (long long i = 1; i <= (long long)p; i++)
    cin >> z[i].d >> z[i].a >> z[i].p;
  sort(X + 1, X + n + 1,
       [](W a, W b) { return a.a != b.a ? a.a < b.a : a.c < b.c; });
  sort(Y + 1, Y + m + 1,
       [](D a, D b) { return a.d != b.d ? a.d < b.d : a.c < b.c; });
  sort(z + 1, z + p + 1, [](M a, M b) { return a.a < b.a; });
  long long cnt = 0;
  for (long long i = 1; i <= (long long)n; i++)
    if (X[i].a != x[cnt].a) x[++cnt] = X[i];
  n = cnt;
  cnt = 0;
  for (long long i = 1; i <= (long long)m; i++)
    if (Y[i].d != y[cnt].d) y[++cnt] = Y[i];
  m = cnt;
  cnt = 1;
  fill(seg.t + 1, seg.t + n * 4 + 1, -INF);
  seg.build(1, n);
  for (long long i = 1; i <= (long long)n; i++) a[i] = x[i].a;
  long long ans = -INF;
  for (long long i = 1; i <= (long long)m; i++) {
    for (; cnt <= p && z[cnt].a < y[i].d; ++cnt) {
      long long w = upper_bound(a + 1, a + 1 + n, z[cnt].d) - a;
      if (a[w] > z[cnt].d) seg.modify(w, n, z[cnt].p);
    }
    ans = max(ans, seg.query() - y[i].c);
  }
  cout << ans << endl;
}
signed main() {
  long long T = 1;
  while (T--) solve();
  return 0;
}
