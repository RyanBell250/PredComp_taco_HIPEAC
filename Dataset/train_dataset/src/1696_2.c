#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;
using ll = long long;
using db = long double;
using ii = pair<int, int>;
const int N = 1e5 + 5, LG = 17, MOD = 998244353;
const int SQ = 225;
const long double EPS = 1e-7;
int n, q, f[N], lvl[N], par[N];
vector<ii> edges;
struct Nd {
  bool all;
  int prefix, suffix, sum;
  Nd(int x = 0) {
    all = prefix = suffix = x;
    sum = 0;
  }
  int calc() {
    if (all) return f[prefix];
    return sum + f[prefix] + f[suffix];
  }
} t[N << 2];
Nd flip(Nd x) {
  swap(x.prefix, x.suffix);
  return x;
}
Nd operator+(Nd a, Nd b) {
  Nd ret;
  ret.all = a.all & b.all;
  ret.prefix = a.prefix + a.all * b.prefix;
  ret.suffix = b.suffix + b.all * a.suffix;
  ret.sum = a.sum + b.sum + (!b.all) * (!a.all) * f[a.suffix + b.prefix];
  return ret;
}
void upd(int node, int s, int e, int idx) {
  if (s == e) {
    t[node] = Nd(1);
  } else {
    int md = (s + e) >> 1;
    if (idx <= md)
      upd(node << 1, s, md, idx);
    else
      upd(node << 1 | 1, md + 1, e, idx);
    t[node] = t[node << 1] + t[node << 1 | 1];
  }
}
Nd qry(int node, int s, int e, int l, int r) {
  if (r < s || e < l) {
    Nd ret;
    ret.all = true;
    return ret;
  }
  if (l <= s && e <= r) return t[node];
  int md = (s + e) >> 1;
  return qry(node << 1, s, md, l, r) + qry(node << 1 | 1, md + 1, e, l, r);
}
vector<ii> adj[N];
int sz[N], pos[N], head[N], ptr;
void pDFS(int node, int p) {
  sz[node] = 1;
  for (auto& x : adj[node]) {
    if (x.first == p) swap(x, adj[node].back());
    if (x.first == p) continue;
    edges.push_back({x.second, x.first});
    lvl[x.first] = lvl[node] + 1;
    par[x.first] = node;
    pDFS(x.first, node);
    sz[node] += sz[x.first];
    if (sz[x.first] > sz[adj[node][0].first]) swap(x, adj[node][0]);
  }
  if (node != 1) adj[node].pop_back();
}
void hDFS(int node) {
  pos[node] = ptr++;
  for (auto x : adj[node]) {
    if (x == adj[node][0])
      head[x.first] = head[node];
    else
      head[x.first] = x.first;
    hDFS(x.first);
  }
}
Nd query(int u, int v) {
  if (head[u] == head[v]) {
    if (lvl[u] < lvl[v]) return qry(1, 0, n - 1, pos[u] + 1, pos[v]);
    return flip(qry(1, 0, n - 1, pos[v] + 1, pos[u]));
  } else {
    if (lvl[head[u]] < lvl[head[v]])
      return query(u, par[head[v]]) + qry(1, 0, n - 1, pos[head[v]], pos[v]);
    return flip(query(v, par[head[u]]) +
                qry(1, 0, n - 1, pos[head[u]], pos[u]));
  }
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> q;
  for (int i = 1; i < n; i++) cin >> f[i];
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back(ii(v, w));
    adj[v].push_back(ii(u, w));
  }
  pDFS(1, 1);
  head[1] = 1;
  hDFS(1);
  vector<vector<int>> queries;
  for (int i = 0; i < q; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    queries.push_back({w, u, v, i});
  }
  sort(queries.rbegin(), queries.rend());
  sort(edges.rbegin(), edges.rend());
  vector<int> ans(q);
  for (int i = 0, j = 0; i < queries.size(); i++) {
    for (; j < edges.size() && edges[j].first >= queries[i][0]; j++) {
      upd(1, 0, n - 1, pos[edges[j].second]);
    }
    ans[queries[i].back()] = query(queries[i][1], queries[i][2]).calc();
  }
  for (int i = 0; i < q; i++) cout << ans[i] << '\n';
  return 0;
}
