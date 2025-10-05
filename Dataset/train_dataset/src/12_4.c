#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const long long LL_INF = 0x3f3f3f3f3f3f3f3f;
bool ok[maxn];
set<int> s;
set<int> vis[maxn];
void dfs(int rt) {
  set<int> s2;
  for (auto res : s) {
    if (ok[res]) continue;
    if (vis[rt].count(res)) continue;
    s2.insert(res);
  }
  for (auto res : s2) {
    ok[res] = true;
    s.erase(res);
  }
  for (auto res : s2) dfs(res);
}
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) s.insert(i);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    vis[u].insert(v);
    vis[v].insert(u);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (!ok[i]) {
      ans++;
      ok[i] = true;
      s.erase(i);
      dfs(i);
    }
  }
  printf("%d\n", ans - 1);
  return 0;
}
