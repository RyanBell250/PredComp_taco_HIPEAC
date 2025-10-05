#include <bits/stdc++.h>
using namespace std;
const int M = 1e9 + 7;
int n, m, ans;
map<int, vector<int>> g;
map<int, int> sz;
vector<int> add;
map<int, bool> vis;
void add1(int a) {
  while (a) {
    sz[a];
    a >>= 1;
  }
}
void add2(int& a, int b) {
  a += b;
  if (a >= M) a -= M;
}
int calc(int at) {
  int l = at, r = at, ret = 0;
  while (l <= n) {
    ret += min(n, r) - l + 1;
    l <<= 1;
    r <<= 1;
    r++;
  }
  return ret;
}
void dfs(int u, int path) {
  vis[u] = 1;
  add2(ans, path * 1LL * sz[u] % M);
  for (auto i : g[u])
    if (!vis[i]) dfs(i, path);
  vis[u] = 0;
}
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0, a, b; i < m; i++) {
    scanf("%d%d", &a, &b);
    g[a].push_back(b);
    g[b].push_back(a);
    add1(a);
    add1(b);
  }
  for (auto i = g.rbegin(); i != g.rend(); i++) {
    int temp = calc(i->first);
    sz[i->first] += temp;
    if ((i->first) / 2) {
      sz[(i->first) / 2] -= temp;
      g[i->first / 2].push_back(i->first);
      g[i->first].push_back(i->first / 2);
    }
  }
  for (auto i : sz) dfs(i.first, i.second);
  if (sz.empty()) ans = n * 1LL * n % M;
  printf("%d\n", ans);
}
