#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005 * 2;
const long long modulo = 1000000007;
int n;
vector<int> g[MAXN];
bool cycle_used[MAXN];
bool used[MAXN];
vector<int> path;
set<int> st_path;
vector<int> circle_sizes;
int parent[MAXN];
int sizes[MAXN];
void dsu_init() {
  for (int i = 0; i < MAXN; ++i) {
    parent[i] = i;
    sizes[i] = 1;
  }
}
int dsu_get(int v) {
  if (parent[v] == v) return v;
  return parent[v] = dsu_get(parent[v]);
}
void dsu_union(int a, int b) {
  a = dsu_get(a);
  b = dsu_get(b);
  if (a != b) {
    bool cycled = cycle_used[a] || cycle_used[b];
    if (sizes[a] > sizes[b]) swap(a, b);
    sizes[b] += sizes[a];
    parent[a] = b;
    cycle_used[a] = cycle_used[b] = cycled;
  }
}
void find_and_delete_circles(int v) {
  used[v] = true;
  path.push_back(v);
  st_path.insert(v);
  for (int to : g[v]) {
    if (!used[to]) {
      find_and_delete_circles(to);
    } else {
      if (st_path.find(to) == st_path.end()) continue;
      int circle_size = 0;
      for (size_t i = path.size() - 1; path[i] != to; --i) {
        cycle_used[path[i]] = true;
        ++circle_size;
      }
      ++circle_size;
      cycle_used[to] = true;
      circle_sizes.push_back(circle_size == 1 ? 1 : 2);
    }
  }
  st_path.erase(v);
  path.pop_back();
}
int main() {
  ios::sync_with_stdio(0);
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    g[x].push_back(y);
  }
  for (int i = 1; i < MAXN; ++i) {
    if (!used[i]) find_and_delete_circles(i);
  }
  memset(used, 0, sizeof(used));
  dsu_init();
  for (int i = 1; i < MAXN; ++i) {
    for (int to : g[i]) {
      dsu_union(i, to);
    }
  }
  long long ans = 1;
  for (int i = 1; i < MAXN; ++i) {
    int x = dsu_get(i);
    if (!cycle_used[x]) {
      circle_sizes.push_back(sizes[x]);
      cycle_used[x] = true;
    }
  }
  for (int x : circle_sizes) {
    ans = ans * x % modulo;
  }
  cout << ans;
  return 0;
}
