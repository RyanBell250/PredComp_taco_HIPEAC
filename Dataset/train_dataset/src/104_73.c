#include <bits/stdc++.h>
using namespace std;
template <class c>
struct rge {
  c b, e;
};
template <class c>
rge<c> range(c i, c j) {
  return rge<c>{i, j};
}
template <class c>
auto dud(c *x) -> decltype(cout << *x, 0);
template <class c>
char dud(...);
struct debug {
  ~debug() { cout << endl; }
  template <class c>
  typename enable_if<sizeof dud<c>(0) != 1, debug &>::type operator<<(c i) {
    cout << boolalpha << i;
    return *this;
  }
  template <class c>
  typename enable_if<sizeof dud<c>(0) == 1, debug &>::type operator<<(c i) {
    return *this << range(begin(i), end(i));
  }
  template <class c, class b>
  debug &operator<<(pair<b, c> d) {
    return *this << "(" << d.first << ", " << d.second << ")";
  }
  template <class c>
  debug &operator<<(rge<c> d) {
    *this << "[";
    for (auto it = d.b; it != d.e; ++it) *this << ", " + 2 * (it == d.b) << *it;
    return *this << "]";
  }
};
long double eps = (long double)1 / 1e6;
const long double pi = 3.14159265359;
long long inf = 1e18, mod1 = 1e9 + 7;
long long sqr(long long a) { return a * a; }
long long qb(long long a) { return a * a * a; }
long long gcd(long long a, long long b) { return !a ? b : gcd(b % a, a); }
void binary(long long val, int to) {
  for (int i = 0; i < to; i++) cerr << ((1ll << i) & val ? 1 : 0);
  cerr << "\n";
}
long long binpow(long long a, long long b, long long mod) {
  return b ? (b % 2 ? (a * (sqr(binpow(a, b / 2, mod)) % mod)) % mod
                    : sqr(binpow(a, b / 2, mod)) % mod)
           : 1;
}
long long binmult(long long a, long long b, long long mod) {
  return b ? (b % 2 ? (2 * binmult(a, b / 2, mod) + a) % mod
                    : (2 * binmult(a, b / 2, mod)) % mod)
           : 0;
}
const long long R = 1e4;
const long long tx[4] = {1, 0, -1, 0};
const long long ty[4] = {0, 1, 0, -1};
const char rev_to[4] = {'E', 'W', 'N', 'S'};
const int N = 1e5 + 1;
const int M = 1e9 + 7;
void bad() {
  cout << -1;
  exit(0);
}
int n, m;
int sz[N], h[N], cnt[N], ans[N], pr[N];
vector<int> *vec[N];
vector<int> g[N];
vector<pair<int, int> > zapr[N];
void prec(int v, int p, int he) {
  h[v] = he;
  sz[v] = 1;
  for (auto &z : g[v]) {
    if (z == p) continue;
    prec(z, v, he + 1);
    sz[v] += sz[z];
  }
}
void dfs(int v, int p, bool keep) {
  int big = -1;
  for (auto &u : g[v]) {
    if (u == p) continue;
    if (big == -1 || sz[u] > sz[big]) big = u;
  }
  for (auto &u : g[v]) {
    if (u == p || u == big) continue;
    dfs(u, v, 0);
  }
  if (big == -1) {
    vec[v] = new vector<int>();
  } else
    dfs(big, v, 1), vec[v] = vec[big];
  vec[v]->push_back(v);
  cnt[h[v]]++;
  for (auto &u : g[v]) {
    if (u == p || u == big) continue;
    for (auto &z : *vec[u]) {
      vec[v]->push_back(z);
      cnt[h[z]]++;
    }
  }
  for (auto &z : zapr[v]) {
    ans[z.second] = cnt[z.first] - 1;
  }
  if (!keep) {
    for (auto &z : *vec[v]) cnt[h[z]]--;
  }
}
int lol[N][18];
signed main() {
  cin.tie(0);
  cout.tie(0);
  ios_base::sync_with_stdio(0);
  ;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> pr[i];
    if (pr[i]) g[pr[i] - 1].push_back(i);
    lol[i][0] = pr[i] - 1;
  }
  for (int i = 1; i < 18; i++) {
    for (int j = 0; j < n; j++) {
      if (lol[j][i - 1] != -1) {
        lol[j][i] = lol[lol[j][i - 1]][i - 1];
      } else
        lol[j][i] = -1;
    }
  }
  for (int i = 0; i < n; i++) {
    if (pr[i] == 0) {
      prec(i, i, 0);
    }
  }
  cin >> m;
  int v, u;
  for (int i = 0; i < m; i++) {
    cin >> v >> u;
    --v;
    int need = v;
    for (int j = 0; j < 17; j++) {
      if (need == -1) break;
      if ((1ll << j) & u) need = lol[need][j];
    }
    if (need != -1)
      zapr[need].push_back({h[v], i});
    else
      ans[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    if (pr[i] == 0) {
      dfs(i, i, 0);
    }
  }
  for (int i = 0; i < m; i++) cout << ans[i] << ' ';
  return 0;
}
