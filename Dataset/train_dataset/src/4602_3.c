#include <bits/stdc++.h>
using namespace std;
set<int> se[200100];
int u[200100];
int v[200100];
int vis[200100];
int n, m, k, ans;
int num[200100];
void dfs(int st) {
  if (se[st].size() >= k || vis[st]) return;
  vis[st] = 1;
  --ans;
  for (auto &t : se[st]) {
    se[t].erase(st);
    dfs(t);
  }
  se[st].clear();
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    se[a].insert(b);
    se[b].insert(a);
    u[i] = a;
    v[i] = b;
  }
  ans = n;
  for (int i = 1; i <= n; i++) dfs(i);
  num[m] = ans;
  for (int i = m; i >= 1; i--) {
    se[u[i]].erase(v[i]);
    se[v[i]].erase(u[i]);
    dfs(u[i]);
    dfs(v[i]);
    num[i - 1] = ans;
  }
  for (int i = 1; i <= m; i++) printf("%d\n", num[i]);
}
