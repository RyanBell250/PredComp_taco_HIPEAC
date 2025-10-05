#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
inline long long mod_it(long long it) {
  it %= MOD;
  while (it < 0) it += MOD;
  it %= MOD;
  return it;
}
struct Result {
  long long x;
  long long k;
  Result operator+(const Result& r) {
    Result temp = {x + r.x, k + r.k};
    return temp;
  }
  void operator+=(const Result& r) {
    x += r.x;
    k += r.k;
  }
};
struct SegmentTree {
  struct Node {
    int l;
    int r;
    long long x;
    long long k;
  };
  int r_most;
  vector<Node> node;
  void init(int rm) {
    r_most = rm;
    node.resize((r_most + 1) * 4);
    Node& root = node[1];
    root.l = 0;
    root.r = r_most;
    root.x = 0;
    root.k = 0;
    for (int i = 2; i < node.size(); i++) {
      Node& cur = node[i];
      cur.x = 0;
      cur.k = 0;
      const Node& par = node[i / 2];
      if (par.l == par.r) continue;
      int m = (par.l + par.r) / 2;
      if (i & 1) {
        cur.l = m + 1;
        cur.r = par.r;
      } else {
        cur.l = par.l;
        cur.r = m;
      }
    }
    { ; }
    show();
  }
  void show() {
    for (int i = 1; i < node.size(); i++) {
      Node& cur = node[i];
      { ; }
    }
  }
  void update(int l, int r, long long x, long long k, int i = 1) {
    if (i >= node.size())
      printf("ERROR i{%d} >= node.size{%d}, l = %d, r = %d\n", i, node.size(),
             l, r);
    if (i < 0) printf("ERROR i < 0\n");
    Node& cur = node[i];
    if (cur.l == cur.r) {
      { ; }
      cur.x += x;
      cur.x = mod_it(cur.x);
      cur.k += k;
      cur.k = mod_it(cur.k);
      return;
    }
    int curm = (cur.l + cur.r) / 2;
    int il = i * 2;
    int ir = il + 1;
    { ; }
    if (l <= cur.l && cur.r <= r) {
      cur.x += x;
      cur.x = mod_it(cur.x);
      cur.k += k;
      cur.k = mod_it(cur.k);
      return;
    }
    long long mmx = mod_it(x - mod_it(curm + 1 - l) * mod_it(k));
    if (l > curm && l <= cur.r) {
      { ; }
      update(l, r, x, k, ir);
    }
    if (l <= curm && curm < r) {
      { ; }
      update(curm + 1, r, mmx, k, ir);
    }
    if (l <= curm && r >= cur.l) {
      { ; }
      update(l, r, x, k, il);
    }
  }
  Result query(int l, int i = 1) {
    Node& cur = node[i];
    if (cur.l == cur.r) {
      Result ans = {cur.x, cur.k};
      { ; }
      return ans;
    }
    long long sub = mod_it(mod_it(l - cur.l) * mod_it(cur.k));
    Result ans = {mod_it(cur.x - sub), cur.k};
    { ; }
    int m = (cur.l + cur.r) / 2;
    int il = i * 2;
    int ir = il + 1;
    if (l <= m)
      ans += query(l, il);
    else
      ans += query(l, ir);
    { ; }
    ans.x = mod_it(ans.x);
    ans.k = mod_it(ans.k);
    return ans;
  }
};
struct Graph {
  struct Edge {
    int x;
  };
  const static int MAXNODE = 300002;
  vector<int> g[MAXNODE];
  vector<Edge> edge;
  int n;
  void init(int nn) {
    n = nn;
    for (int i = 0; i <= n; i++) g[i].clear();
    edge.clear();
  }
  void add_e(int x, int y) {
    Edge e = {y};
    g[x].push_back(edge.size());
    edge.push_back(e);
  }
  int parent[MAXNODE];
  int size[MAXNODE];
  int size_parent(int cur) {
    int& s = size[cur] = 1;
    for (int ie : g[cur]) {
      const Edge& e = edge[ie];
      int nx = e.x;
      parent[nx] = cur;
      s += size_parent(nx);
    }
    return s;
  }
  void show_size_parent() {
    for (int i = 0; i <= n; i++)
      printf("node %d: size %d, parent %d\n", i, size[i], parent[i]);
  }
  struct Chain {
    int head;
    int len;
  };
  vector<Chain> chain;
  int chain_total;
  int chain_no[MAXNODE];
  int chain_pos[MAXNODE];
  void hld(int cur) {
    if (chain_total == chain.size()) {
      Chain c = {cur, 0};
      chain.push_back(c);
    }
    chain_no[cur] = chain_total;
    chain_pos[cur] = chain[chain_total].len;
    chain[chain_total].len++;
    if (g[cur].size() == 0) return;
    int heavy = edge[g[cur][0]].x;
    for (int ie : g[cur]) {
      const Edge& e = edge[ie];
      int nx = e.x;
      if (size[nx] > size[heavy]) heavy = nx;
    }
    hld(heavy);
    for (int ie : g[cur]) {
      const Edge& e = edge[ie];
      int nx = e.x;
      if (nx == heavy) continue;
      chain_total++;
      hld(nx);
    }
  }
  void heavy_light_decomposition() {
    parent[1] = -1;
    assert(n == size_parent(1));
    chain_total = 0;
    chain.clear();
    hld(1);
    chain_total++;
  }
  void show_hld() {
    for (int i = 0; i <= chain_total; i++)
      printf("chain %d: len %d, head %d\n", i, chain[i].len, chain[i].head);
    for (int i = 0; i <= n; i++)
      printf("node %d: chain %d, pos %d\n", i, chain_no[i], chain_pos[i]);
  }
  vector<SegmentTree> st;
  void init_sol() {
    st.resize(chain_total);
    for (int i = 0; i < st.size(); i++) st[i].init(chain[i].len - 1);
  }
  void update(int v, int x, int k) {
    int cn = chain_no[v];
    int cp = chain_pos[v];
    int cl = chain[cn].len;
    { ; }
    st[cn].update(cp, cl - 1, x, k);
    st[cn].show();
  }
  long long query(int v) {
    long long ans = 0;
    int d = 0;
    do {
      int cn = chain_no[v];
      int cp = chain_pos[v];
      Result temp = st[cn].query(cp);
      { ; }
      long long temp_ans = temp.x - mod_it(mod_it(temp.k) * mod_it(d));
      temp_ans = mod_it(temp_ans);
      ans += temp_ans;
      ans = mod_it(ans);
      d += chain_pos[v] + 1;
      v = chain[cn].head;
      v = parent[v];
    } while (v != -1);
    return ans;
  }
};
int n;
int m;
Graph g;
int main() {
  scanf("%d", &n);
  g.init(n);
  for (int i = 2; i <= n; i++) {
    int x;
    scanf("%d", &x);
    g.add_e(x, i);
  }
  g.heavy_light_decomposition();
  g.init_sol();
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int v, x, k;
      scanf("%d %d %d", &v, &x, &k);
      { ; }
      g.update(v, x, k);
    } else {
      int v;
      scanf("%d", &v);
      { ; };
      long long ans = g.query(v);
      printf("%d\n", ans);
    }
  }
}
