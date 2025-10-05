#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6 + 10;
void chmax(int& a, int b) {
  if (b > a) a = b;
}
struct disjoint {
  int p[MX];
  void init() {
    for (int i = 0; i < MX; i++) p[i] = -1;
  }
  int f(int x) { return p[x] < 0 ? x : p[x] = f(p[x]); }
  void Join(int x, int y) {
    int fx = f(x), fy = f(y);
    if (fx == fy) return;
    p[fx] += p[fy];
    p[fy] = fx;
  }
  int fsize(int x) { return -p[f(x)]; }
} dsu;
int N, M, vs[MX];
pair<int, int> a[MX], q[MX];
long double ans[MX];
struct segtree {
  pair<long long, long long> seg[MX << 1];
  void chad(pair<long long, long long>& a, pair<long long, long long> b) {
    a.first += b.first;
    a.second += b.second;
  }
  void upd(int l, int r, pair<long long, long long> val) {
    if (r < l) return;
    for (l += MX, r += MX + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) chad(seg[l++], val);
      if (r & 1) chad(seg[--r], val);
    }
  }
  void push() {
    for (int i = 1; i < MX; i++) {
      chad(seg[i << 1], seg[i]);
      chad(seg[i << 1 | 1], seg[i]);
    }
    for (int i = MX; i < (MX << 1); i++)
      seg[i].first += 1ll * q[i - MX].first * seg[i].second;
  }
} st;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  dsu.init();
  for (int i = 0; i < N; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }
  sort(a, a + N, greater<pair<int, int> >());
  cin >> M;
  for (int i = 0; i < M; i++) {
    cin >> q[i].first;
    q[i].second = i;
  }
  sort(q, q + M);
  for (int i = 0; i < N; i++) {
    int h = a[i].first, idx = a[i].second;
    int mn = (idx > 0 && vs[idx - 1]) ? dsu.fsize(idx - 1) : 0;
    int mx = (idx + 1 < N && vs[idx + 1]) ? dsu.fsize(idx + 1) : 0;
    if (mn > mx) swap(mn, mx);
    int lf = -1, rg = M, boundr = 0;
    {
      int l = 0, r = M - 1;
      while (l <= r) {
        int mid = l + r >> 1;
        if (q[mid].first <= mn) {
          lf = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
    }
    {
      int l = 0, r = M - 1;
      while (l <= r) {
        int mid = l + r >> 1;
        if (q[mid].first > mx) {
          rg = mid;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
    }
    {
      int l = 0, r = M - 1;
      while (l <= r) {
        int mid = l + r >> 1;
        if (q[mid].first <= mn + mx + 1) {
          boundr = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
    }
    st.upd(0, lf, make_pair(0ll, (long long)h));
    st.upd(lf + 1, rg - 1, make_pair(1ll * h * (mn + 1), 0ll));
    st.upd(rg, boundr, make_pair(1ll * h * (mn + mx + 2), (long long)-h));
    if (i > 0 && vs[idx - 1]) dsu.Join(idx - 1, idx);
    if (i + 1 < N && vs[idx + 1]) dsu.Join(idx + 1, idx);
    vs[idx] = 1;
  }
  st.push();
  for (int i = 0; i < M; i++) {
    int sum = N - q[i].first + 1;
    ans[q[i].second] = (long double)st.seg[i + MX].first / (long double)sum;
  }
  for (int i = 0; i < M; i++) {
    cout << fixed << setprecision(10) << ans[i] << '\n';
  }
}
