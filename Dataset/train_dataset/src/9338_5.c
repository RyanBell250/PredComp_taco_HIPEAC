#include <bits/stdc++.h>
using namespace std;
const long long N = 1e5 + 5;
vector<vector<long long> > adj(N);
long long h[N];
struct centroidDecomp {
  vector<vector<long long> > cd;
  vector<long long> d;
  vector<bool> vis;
  vector<long long> sz;
  vector<long long> par;
  long long n;
  centroidDecomp(long long root = 1) {
    n = adj.size();
    d.resize(n, 1000000000);
    par.resize(n, -1);
    cd.resize(n);
    vis.resize(n, false);
    sz.resize(n, 0);
    init_centroid(root);
    constructTree();
  }
  void constructTree() {
    for (long long i = 0; i < n; i++) {
      if (par[i] == -1) continue;
      cd[i].push_back(par[i]);
      cd[par[i]].push_back(i);
    }
  }
  long long fillSize(long long v, long long p = -1) {
    if (vis[v]) return 0;
    sz[v] = 1;
    for (auto i : adj[v]) {
      if (!vis[i] && i != p) sz[v] += fillSize(i, v);
    }
    return sz[v];
  }
  long long find_centroid(long long u, long long p, long long n) {
    for (long long x : adj[u]) {
      if (!vis[x] && x != p && sz[x] > n / 2) return find_centroid(x, u, n);
    }
    return u;
  }
  void init_centroid(long long u, long long p = -1) {
    fillSize(u, p);
    long long c = find_centroid(u, p, sz[u]);
    par[c] = p;
    vis[c] = true;
    for (auto x : adj[c]) {
      if (!vis[x]) init_centroid(x, c);
    }
  }
  void printTree() {
    for (long long i = 0; i < n; i++) {
      if (cd[i].size()) {
        cout << i << ": ";
        for (auto j : cd[i]) cout << j << " ";
        cout << "\n";
      }
    }
  }
};
void dfs(vector<vector<long long> > &adj, long long u, long long p = -1) {
  for (auto x : adj[u]) {
    if (x != p) {
      h[x] = h[u] + 1;
      dfs(adj, x, u);
    }
  }
}
int32_t main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  long long i, j;
  long long n;
  cin >> n;
  for (i = 0; i < n - 1; i++) {
    long long a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  centroidDecomp cdecomp;
  long long rt;
  for (i = 1; i < n + 1; i++)
    if (cdecomp.par[i] == -1) rt = i;
  dfs(cdecomp.cd, rt);
  for (i = 1; i < n + 1; i++) cout << (char)(h[i] + 'A') << " ";
  return 0;
}
