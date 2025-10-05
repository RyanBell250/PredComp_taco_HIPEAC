#include <bits/stdc++.h>
using namespace std;
const int MAXN = 15e4 + 5, SQ = 400;
const long long MOD = 998244353;
int n, q, tim;
vector<int> adj[MAXN];
vector<pair<int, int> > adj2[MAXN];
int par[MAXN];
int st[MAXN], fn[MAXN], bc[MAXN], sub[MAXN], up[MAXN];
long long seg[MAXN * 4], an[MAXN];
long long pw(long long a, long long b) {
  if (b == 0) return 1LL;
  return pw(a * a % MOD, b / 2) * (b % 2 ? a : 1LL) % MOD;
}
void dfs(int u) {
  sub[u] = 1, st[u] = tim++, bc[u] = -1;
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v == par[u]) continue;
    par[v] = u, dfs(v), sub[u] += sub[v];
    if (bc[u] == -1 || sub[bc[u]] < sub[v]) bc[u] = v;
  }
  fn[u] = tim;
}
void dfs1(int u) {
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v == par[u]) continue;
    if (v == bc[u]) up[bc[u]] = up[u];
    dfs1(v);
  }
}
void add(int l, int r, long long val, int b = 0, int e = n, int id = 1) {
  if (r <= b || l >= e) return;
  if (l <= b && e <= r) {
    seg[id] += val;
    return;
  }
  int mid = (b + e) / 2;
  add(l, r, val, b, mid, id * 2), add(l, r, val, mid, e, id * 2 + 1);
}
long long get(int ind, int b = 0, int e = n, int id = 1) {
  if (b + 1 == e) return seg[id];
  int mid = (b + e) / 2;
  if (ind < mid)
    return (seg[id] + get(ind, b, mid, id * 2));
  else
    return (seg[id] + get(ind, mid, e, id * 2 + 1));
}
int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--, v--;
    adj[u].push_back(v), adj[v].push_back(u);
  }
  dfs(0);
  for (int i = 0; i < n; i++) up[i] = i;
  dfs1(0);
  int inv = pw(n, MOD - 2);
  while (q) {
    q--;
    int ty, v;
    long long d;
    scanf("%d%d", &ty, &v);
    v--;
    if (ty == 1) {
      scanf("%lld", &d);
      an[v] += d;
      seg[1] += d * sub[v];
      add(st[v], fn[v], d * (n - sub[v]));
      if (bc[v] != -1) add(st[bc[v]], fn[bc[v]], -d * sub[bc[v]]);
    } else {
      long long ans = get(st[v]);
      while (up[v]) {
        int u = up[v];
        v = par[u];
        ans -= sub[u] * an[v];
      }
      ans = ans % MOD, ans = (ans + MOD) % MOD;
      printf("%lld\n", ans * inv % MOD);
    }
  }
  return 0;
}
