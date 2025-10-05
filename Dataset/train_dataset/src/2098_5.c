#include <bits/stdc++.h>
#pragma GCC optimize("O2")
#pragma GCC optimize("unroll-loops")
using namespace std;
const long double eps = 1e-7;
const int inf = 1000000010;
const long long INF = 10000000000000010LL;
const int mod = 1000000007;
const int MAXN = 200010, LOG = 20;
struct node {
  int mn = 0, cnt = 0;
  node(int a = 0, int b = 0) : mn(a), cnt(b) {}
} seg[MAXN << 2];
node combine(node x, node y) {
  if (x.mn == y.mn) return node(x.mn, x.cnt + y.cnt);
  if (x.mn < y.mn) return x;
  return y;
}
int n, m, k, u, v, x, y, t, a, b, ans;
int stt[MAXN], fnt[MAXN], timer = 1;
int lazy[MAXN << 2];
vector<int> G[MAXN];
vector<pair<int, int> > child[MAXN];
set<pair<int, int> > edge;
void dfs(int node, int p) {
  stt[node] = timer++;
  for (int v : G[node])
    if (v != p) {
      dfs(v, node);
      child[node].push_back({fnt[v], v});
    }
  fnt[node] = timer;
}
node build(int id, int tl, int tr) {
  if (tr - tl == 1) return seg[id] = node(0, 1);
  int mid = (tl + tr) >> 1;
  return seg[id] =
             combine(build(id << 1, tl, mid), build(id << 1 | 1, mid, tr));
}
void add_lazy(int id, int lz) {
  lazy[id] += lz;
  seg[id].mn += lz;
}
void shift(int id) {
  if (!lazy[id]) return;
  add_lazy(id << 1, lazy[id]);
  add_lazy(id << 1 | 1, lazy[id]);
  lazy[id] = 0;
}
void update(int id, int tl, int tr, int l, int r, int val) {
  if (tr <= l || r <= tl) return;
  if (l <= tl && tr <= r) {
    add_lazy(id, val);
    return;
  }
  shift(id);
  int mid = (tl + tr) >> 1;
  update(id << 1, tl, mid, l, r, val);
  update(id << 1 | 1, mid, tr, l, r, val);
  seg[id] = combine(seg[id << 1], seg[id << 1 | 1]);
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i < n; i++) {
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  dfs(1, 1);
  build(1, 1, n + 1);
  while (m--) {
    cin >> u >> v;
    int tmp = 1;
    if (stt[u] > stt[v]) swap(u, v);
    if (edge.count({u, v})) {
      tmp = -1;
      edge.erase({u, v});
    } else
      edge.insert({u, v});
    if (fnt[v] <= fnt[u]) {
      int x = lower_bound(child[u].begin(), child[u].end(),
                          pair<int, int>(fnt[v], 0))
                  ->second;
      update(1, 1, n + 1, stt[x], fnt[x], tmp);
      update(1, 1, n + 1, stt[v], fnt[v], -tmp);
    } else {
      update(1, 1, n + 1, 1, n + 1, tmp);
      update(1, 1, n + 1, stt[u], fnt[u], -tmp);
      update(1, 1, n + 1, stt[v], fnt[v], -tmp);
    }
    cout << (seg[1].mn == 0) * seg[1].cnt << '\n';
  }
  return 0;
}
