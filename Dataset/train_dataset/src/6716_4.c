#include <bits/stdc++.h>
using namespace std;
namespace __SarcasticMonk {
template <typename Arg1>
void __f(const char *name, Arg1 &&arg1) {
  cerr << name << " : " << arg1 << "\n";
}
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&...args) {
  const char *comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << " : " << arg1 << " | ";
  __f(comma + 1, args...);
}
long long mod = 1e9 + 7;
long long mod2 = 998244353;
const long long N = 1e6 + 204;
const long long M = 5009;
long long dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
long long ddx[8] = {1, 1, 0, -1, -1, -1, 0, 1},
          ddy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
template <typename T>
void amin(T &a, const T &b) {
  a = min(a, b);
}
template <typename T>
void amax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T1, typename T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
  in >> a.fr >> a.sc;
  return in;
}
template <typename T1, typename T2>
ostream &operator<<(ostream &out, pair<T1, T2> a) {
  out << a.fr << " " << a.sc;
  return out;
}
template <typename T>
struct is_outputtable {
  template <typename C>
  static constexpr decltype(declval<ostream &>() << declval<const C &>(),
                            bool())
  test(int32_t) {
    return true;
  }
  template <typename C>
  static constexpr bool test(...) {
    return false;
  }
  static constexpr bool value = test<T>(int32_t());
};
template <
    class T, typename V = decltype(declval<const T &>().begin()),
    typename S = typename enable_if<!is_outputtable<T>::value, bool>::type>
void pr(const T &x);
template <class T,
          typename V = decltype(declval<ostream &>() << declval<const T &>())>
void pr(const T &x) {
  cout << x;
}
template <class T1, class T2>
void pr(const pair<T1, T2> &x);
template <class Arg, class... Args>
void pr(const Arg &first, const Args &...rest) {
  pr(first);
  pr(rest...);
}
template <class T, bool pretty = false>
void prContain(const T &x) {
  if (pretty) pr("{");
  bool fst = 1;
  for (const auto &a : x) pr(!fst ? pretty ? " " : " " : "", a), fst = 0;
  if (pretty) pr("}");
}
template <class T>
void pc(const T &x) {
  prContain<T, false>(x);
  pr("\n");
}
template <class T1, class T2>
void pr(const pair<T1, T2> &x) {
  pr(x.first, " ", x.second, "\n");
}
template <class T, typename V, typename S>
void pr(const T &x) {
  prContain(x);
}
void ps() { pr("\n"); }
template <class Arg>
void ps(const Arg &first) {
  pr(first);
  ps();
}
template <class Arg, class... Args>
void ps(const Arg &first, const Args &...rest) {
  pr(first, " ");
  ps(rest...);
}
template <class T1, class T2>
void re(pair<T1, T2> &p);
template <class T>
void re(vector<T> &a);
template <class T, size_t SZ>
void re(array<T, SZ> &a);
template <class T>
void re(T &x) {
  cin >> x;
}
void re(double &x) {
  string t;
  re(t);
  x = stod(t);
}
template <class Arg, class... Args>
void re(Arg &first, Args &...rest) {
  re(first);
  re(rest...);
}
template <class T1, class T2>
void re(pair<T1, T2> &p) {
  re(p.first, p.second);
}
template <class T>
void re(vector<T> &a) {
  for (int32_t i = 0; i < (long long)a.size(); i++) re(a[i]);
}
template <class T, size_t SZ>
void re(array<T, SZ> &a) {
  for (int32_t i = 0; i < SZ; i++) re(a[i]);
}
}  // namespace __SarcasticMonk
using namespace __SarcasticMonk;
namespace __dsu {
vector<long long> parent(1e6 + 2047, -1);
vector<long long> cont(1e6 + 2047, 0);
long long find_set(long long v) {
  if (v == parent[v]) return v;
  return parent[v] = find_set(parent[v]);
}
void make_set(long long v) {
  parent[v] = v;
  cont[v] = 1;
}
void make_set_n(long long n) {
  for (long long i = 0; i <= n; i++) {
    make_set(i);
  }
}
void union_sets(long long a, long long b) {
  a = find_set(a);
  b = find_set(b);
  if (a != b) {
    if (cont[a] < cont[b]) swap(a, b);
    parent[b] = a;
    cont[a] += cont[b];
  }
}
}  // namespace __dsu
using namespace __dsu;
namespace __graph {
struct Graph {
  vector<vector<long long>> graph, g_rev;
  vector<long long> vis, cost, dp, up, parent, order, component;
  long long n;
  Graph(long long x) {
    n = x - 1;
    graph.resize(x);
    g_rev.resize(x);
    vis.resize(x);
    cost.resize(x);
    parent.resize(x);
    dp.resize(x);
    up.resize(x);
  }
  void UaddEdge(long long u, long long v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  void DaddEdge(long long u, long long v) {
    graph[u].push_back(v);
    g_rev[v].push_back(u);
  }
  Graph GenerateReverseGraph() const {
    Graph g_rev(graph.size());
    for (long long v = 0; v < graph.size(); v++) {
      for (const auto &e : graph[v]) {
        g_rev.DaddEdge(e, v);
      }
    }
    return g_rev;
  }
  void dfs(long long u, long long p = 0) {
    vis[u] = 1;
    parent[u] = p;
    order.push_back(u);
    for (auto it : graph[u]) {
      if (vis[it] == 0) {
        dfs(it, u);
      }
    }
  }
  vector<long long> topological_sort() {
    vis.assign(n, false);
    order.clear();
    for (long long i = 0; i < n; ++i) {
      if (!vis[i]) dfs(i);
    }
    reverse(order.begin(), order.end());
    return order;
  }
  void dfs2(long long u) {
    vis[u] = 1;
    component.push_back(u);
    for (auto it : g_rev[u]) {
      if (vis[it] == 0) {
        dfs2(it);
      }
    }
  }
  void scc() {
    for (long long i = 1; i <= n; i++) {
      if (!vis[i]) {
        dfs(i);
      }
    }
    reverse(order.begin(), order.end());
    vis.assign((long long)vis.size(), 0);
    for (auto v : order) {
      if (!vis[v]) {
        dfs2(v);
        component.clear();
      }
    }
  }
  void dfs3(long long u, long long p) {
    vis[u] = 1;
    for (auto it : graph[u]) {
      if (it != p) {
        if (vis[it] == 1) {
          cout << -1;
          exit(0);
        } else if (vis[it] == 0) {
          dfs3(it, u);
        }
      }
    }
    vis[u] = 2;
  }
  void check_cycle() {
    for (long long i = 1; i <= n; i++) {
      if (vis[i] == 0) {
        dfs3(i, 0);
      }
    }
    vis.assign(n + 1, 0);
  }
};
}  // namespace __graph
using namespace __graph;
Graph G((long long)(1e5 + 10)), F((long long)(1e5 + 10));
void dfs1(long long u) {
  if (G.dp[u]) {
    return;
  }
  G.dp[u] = 1;
  if (G.cost[u] == 1) {
    return;
  }
  for (auto it : G.graph[u]) {
    dfs1(it);
  }
}
void dfs2(long long u) {
  if (G.up[u]) {
    return;
  }
  G.up[u] = 1;
  for (auto it : F.graph[u]) {
    dfs2(it);
  }
}
void test_case(long long tc) {
  long long n, m;
  cin >> n >> m;
  for (long long i = 1; i <= n; i++) {
    cin >> G.cost[i];
  }
  for (long long i = 1; i <= m; i++) {
    long long u, v;
    cin >> u >> v;
    G.DaddEdge(v, u);
    F.DaddEdge(u, v);
  }
  for (long long i = 1; i <= n; i++) {
    if (G.cost[i] == 2) {
      dfs1(i);
    }
  }
  for (long long i = 1; i <= n; i++) {
    if (G.cost[i] == 1) dfs2(i);
  }
  for (long long i = 1; i <= n; i++) {
    if (G.dp[i] == 1 && G.up[i] == 1) {
      cout << 1 << "\n";
    } else {
      cout << 0 << "\n";
    }
  }
}
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout << fixed << setprecision(10);
  long long t = 1;
  for (long long i = 1; i <= t; i++) {
    test_case(i);
  }
}
