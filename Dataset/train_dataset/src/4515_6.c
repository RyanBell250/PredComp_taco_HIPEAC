#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000009;
struct point {
  int x, y;
  point() {}
  point(int _x, int _y) : x(_x), y(_y) {}
} p[100011];
inline bool cmpx(const point &A, const point &B) { return A.x < B.x; }
inline bool operator<(const point &A, const point &B) { return A.y < B.y; }
struct status {
  int a, b;
  status() {}
  status(int _a, int _b) : a(_a), b(_b) {}
  int ans() { return max(a, b); }
} f[100011];
int n, k, a, b, c, d, m, root, xc[100011];
pair<point, int> q[100011];
int fa[100011], l[100011], r[100011], lc[100011], rc[100011];
int find(int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); }
void init() {
  ios::sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= k; ++i) cin >> p[i].x >> p[i].y;
  cin >> a >> b >> c >> d;
  for (int i = k; i < n; ++i)
    p[i + 1] = point(((long long)p[i].x * a + b) % MOD,
                     ((long long)p[i].y * c + d) % MOD);
  sort(p + 1, p + n + 1, cmpx);
  for (int i = 1; i <= n; ++i)
    q[i] = make_pair(p[i], i), fa[i] = i, xc[i] = p[i].x;
  sort(q + 1, q + n + 1);
  for (int i = 1, u; i <= n; ++i) {
    u = q[i].second;
    if (u - 1 >= 1 && p[u - 1].y < p[u].y)
      lc[u] = find(u - 1), l[u] = l[lc[u]], fa[lc[u]] = u;
    else
      l[u] = u;
    if (u + 1 <= n && p[u + 1].y < p[u].y)
      rc[u] = find(u + 1), r[u] = r[rc[u]], fa[rc[u]] = u;
    else
      r[u] = u;
    if (!lc[u] && !rc[u])
      f[u] = status(0, 0);
    else if (!rc[u])
      f[u] = status(max(f[lc[u]].a, f[lc[u]].b + 1), f[lc[u]].a);
    else if (!lc[u])
      f[u] = status(max(f[rc[u]].a, f[rc[u]].b + 1), f[rc[u]].a);
    else {
      f[u].b = f[lc[u]].a + f[rc[u]].a;
      f[u].a = max(f[u].b,
                   max(f[lc[u]].a + f[rc[u]].b, f[lc[u]].b + f[rc[u]].a) + 1);
    }
  }
  root = q[n].second;
}
status query(int L, int R, int k) {
  if (L > R || !k || l[k] > R || r[k] < L) return status(0, -1);
  if (L <= l[k] && R >= r[k]) return f[k];
  if (R < k) return query(L, R, lc[k]);
  if (L > k) return query(L, R, rc[k]);
  status fl, fr, fk;
  fl = query(L, R, lc[k]);
  fr = query(L, R, rc[k]);
  fk.b = fl.a + fr.a;
  fk.a = max(fk.b, max(fl.a + fr.b, fl.b + fr.a) + 1);
  return fk;
}
void work() {
  cin >> m;
  xc[0] = 0xffffffff, xc[n + 1] = 0x7fffffff;
  for (int i = 0, L, R; i < m; ++i) {
    cin >> L >> R;
    L = lower_bound(xc, xc + n + 3, L) - xc;
    R = upper_bound(xc, xc + n + 3, R) - xc - 1;
    cout << query(L, R, root).ans() << endl;
  }
}
int main() {
  init();
  work();
  return 0;
}
