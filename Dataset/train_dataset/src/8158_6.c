#include <bits/stdc++.h>
using namespace std;
struct DSU {
  vector<int> p, sz;
  DSU(int n = 0) : p(n + 1), sz(n + 1, 1) {
    for (int i = 1; i <= n; i++) p[i] = i;
  }
  int find(int x) { return (p[x] ^ x) ? (p[x] = find(p[x])) : p[x]; }
  int operator[](int x) { return find(x); }
  int merge(int x, int y) {
    if ((x = find(x)) ^ (y = find(y))) p[x] = y, sz[y] += sz[x];
    return x ^ y;
  }
};
const int N = 1e6 + 10;
vector<int> adj[N];
int par[N], val[N], x[N];
void dfs(int v, int p = 0, int mn = 1e9) {
  mn = min(mn, v);
  x[v] = mn;
  par[v] = p;
  for (int u : adj[v])
    if (p ^ u) {
      dfs(u, v, mn);
    }
}
int32_t main() {
  ios_base ::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n, q;
  cin >> n >> q;
  DSU dsu(n);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int t, root, last = 0;
  cin >> t >> root;
  root = root % n + 1;
  int ans = root;
  dfs(root);
  for (int i = 1; i < q; i++) {
    int v;
    cin >> t >> v;
    v = (v + last) % n + 1;
    if (t == 1) {
      while (dsu[v] != root) {
        ans = min(ans, v);
        dsu.merge(v, par[v]);
        v = dsu[v];
      }
    } else {
      cout << (last = min(ans, x[v])) << "\n";
    }
  }
}
