#include <bits/stdc++.h>
using namespace std;
int read() {
  int x = 0;
  bool flg = false;
  char ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') flg = true;
  for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ 48);
  return flg ? -x : x;
}
int n, m, q;
long long T;
int L[100010], R[100010];
int b[100010];
long long lim[100010];
struct Pt {
  int x;
  long long y;
} pt[100010];
Pt operator+(const Pt &x, const Pt &y) { return (Pt){x.x + y.x, x.y + y.y}; }
Pt operator-(const Pt &x, const Pt &y) { return (Pt){x.x - y.x, x.y - y.y}; }
long long cross(const Pt &x, const Pt &y) { return x.x * y.y - x.y * y.x; }
bool operator<(const Pt &x, const Pt &y) {
  if (x.x ^ y.x) return x.x < y.x;
  return x.y < y.y;
}
bool operator==(const Pt &x, const Pt &y) { return x.x == y.x && x.y == y.y; }
vector<long long> solve(vector<long long> w, const long long &T) {
  vector<long long> z(m + 2);
  sort((w).begin(), (w).end());
  for (int i(1); i <= int(n); i++) w[i] += w[i - 1];
  static int stk[100010];
  int top = 0;
  for (int i(0); i <= int(n); i++) {
    pt[i] = (Pt){i, T - w[i] + n - i};
  }
  sort(pt, pt + n + 1);
  for (int i(0); i <= int(n); i++) {
    while (top > 1 &&
           cross(pt[stk[top]] - pt[stk[top - 1]], pt[i] - pt[stk[top]]) >= 0)
      --top;
    stk[++top] = i;
  }
  for (int i = 1, j = 1; i <= m + 1; ++i) {
    while (j < top) {
      const Pt &u = pt[stk[j]], &v = pt[stk[j + 1]];
      if (u.x * 1LL * i + u.y < v.x * 1LL * i + v.y)
        ++j;
      else
        break;
    }
    const Pt &u = pt[stk[j]];
    z[i] = u.x * 1LL * i + u.y - 1LL * n * i;
  }
  return z;
}
int check1(int o) {
  static int a[100010];
  long long sum = 0, W = 0;
  int L = 0;
  for (int i(m); i >= int(o + 1); i--) {
    if (~b[i]) {
      a[i] = b[i];
      sum += a[i];
      if (a[i] < a[i + 1]) return -1;
      W += 1LL * L * (a[i] - a[i + 1]);
      L = 0;
      if (sum >= lim[i]) continue;
      W -= lim[i] - sum;
      sum = lim[i];
      if (W < 0) return -1;
      continue;
    }
    a[i] = a[i + 1];
    sum += a[i];
    L = i == m || ~b[i + 1] ? 1 : L + 1;
    if (sum >= lim[i]) continue;
    if (W >= lim[i] - sum) {
      W -= lim[i] - sum, sum = lim[i];
      continue;
    }
    sum += W;
    W = 0;
    const long long d = (lim[i] - sum + L - 1) / L;
    if (a[i] + d > n) return -1;
    a[i] += d;
    W += d * L - (lim[i] - sum);
    sum = lim[i];
    if (sum > T) return -1;
  }
  const auto check2 = [&](int w, long long sum, long long W, int L) {
    if (w < a[o + 1]) return 1;
    W += 1LL * L * (w - a[o + 1]);
    for (int i(1); i <= int(o); i++) {
      const long long e = sum + 1LL * (o - i + 1) * w;
      if (e < lim[i]) {
        if (W < lim[i] - e) return 1;
        W -= lim[i] - e, sum += lim[i] - e;
      }
    }
    sum += 1LL * o * w;
    if (sum > T) return -1;
    if (W < T - sum) return 1;
    return 0;
  };
  int fixed = -1;
  for (int i(1); i <= int(o); i++)
    if (~b[i]) {
      fixed = b[i];
      break;
    }
  if (~fixed) {
    return check2(fixed, sum, W, L) ? -1 : fixed;
  }
  int l = 0, r = n, mid, z = -1;
  while (l <= r) {
    mid = l + r >> 1;
    const int w = check2(mid, sum, W, L);
    if (!w) z = mid;
    if (w >= 0)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return z;
}
void solve() {
  n = read(), m = read();
  for (int i(1); i <= int(n); i++) L[i] = read(), R[i] = read();
  q = read();
  memset(b, -1, sizeof b);
  while (q--) {
    int p = read(), w = read();
    b[p] = w;
  }
  scanf("%lld", &T);
  long long W = 0;
  for (int i(1); i <= int(n); i++) W += L[i];
  const auto F = solve(vector<long long>(L, L + n + 1), W);
  const auto G = solve(vector<long long>(R, R + n + 1), T);
  for (int i(1); i <= int(m + 1); i++) lim[i] = max(F[i], G[i]);
  if (lim[m + 1] > 0) puts("-1 -1"), exit(0);
  int fixed = -1, ok;
  for (int i(1); i <= int(m); i++) {
    if (~b[i]) {
      if (~fixed && fixed != b[i]) break;
      fixed = b[i];
    }
    ok = i;
  }
  int l = 1, r = ok, mid;
  while (l < r) {
    mid = l + r + 1 >> 1;
    if (check1(mid) >= 0)
      l = mid;
    else
      r = mid - 1;
  }
  const int w = check1(l);
  if (w < 0) puts("-1 -1"), exit(0);
  printf("%d %d\n", l, w);
}
int main() {
  for (int T = 1; T--;) solve();
  return 0;
}
