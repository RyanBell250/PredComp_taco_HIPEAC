#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
long long cl(long double a) {
  if (a > (long long)a) {
    return (long long)a + 1;
  } else {
    return (long long)a;
  }
}
long long flr(long double a) {
  if (a < 0.0) {
    return (long long)a - 1;
  }
  return (long long)a;
}
long long gcd(long long a, long long b) {
  if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}
long long pw(long long n, long long k) {
  if (k == 0) return 1;
  long long t = pw(n, k / 2);
  long long ans = (t * t) % mod;
  if (k % 2)
    return (ans * n) % mod;
  else
    return ans;
}
const long long M = 5e5 + 100;
long long pos[M], val[M];
vector<long long> p(M, 0);
vector<long long> r(M, 1);
long long getp(long long v) {
  if (v == p[v]) return v;
  return p[v] = getp(p[v]);
}
void unite(long long u, long long v) {
  u = getp(u), v = getp(v);
  if (u == v) return;
  if (r[u] < r[v]) swap(u, v);
  r[u] += r[v];
  p[v] = u;
}
void add(long long idx, long long num) {
  if (pos[num] == -1) {
    pos[num] = idx;
  } else {
    unite(pos[num], idx);
  }
}
void solve() {
  long long q;
  cin >> q;
  long long it = 0;
  for (long long i = 0; i < M; i++) {
    pos[i] = -1;
    p[i] = i;
  }
  while (q--) {
    long long t;
    cin >> t;
    if (t == 1) {
      long long x;
      cin >> x;
      add(it, x);
      it++;
    } else {
      long long x, y;
      cin >> x;
      cin >> y;
      if (x == y || pos[x] == -1) continue;
      add(pos[x], y);
      pos[x] = -1;
    }
  }
  for (long long i = 0; i < M; i++) {
    if (pos[i] == -1) continue;
    pos[i] = getp(pos[i]);
    val[pos[i]] = i;
  }
  vector<long long> res;
  for (long long i = 0; i < it; i++) {
    long long cur = val[getp(i)];
    res.push_back(cur);
  }
  for (auto x : res) cout << x << " ";
  cout << "\n";
}
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long t;
  t = 1;
  while (t--) solve();
}
