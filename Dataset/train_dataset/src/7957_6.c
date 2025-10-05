#include <bits/stdc++.h>
using namespace std;
long long a[200005], b[200005];
long long n, m;
vector<long long> g[200005][2];
long long used[200005];
bool vs[200005][2] = {0};
bool dfs(long long u) {
  used[u] = 0;
  for (long long i = 0; i < g[u][0].size(); i++) {
    long long v = g[u][0][i];
    if (used[v] == 0)
      return true;
    else if (used[v] == -1 && dfs(v))
      return true;
  }
  used[u] = 1;
  return false;
}
bool round() {
  for (long long i = 1; i <= n; i++) used[i] = -1;
  for (long long i = 1; i <= n; i++) {
    if (used[i] == -1 && dfs(i)) return true;
  }
  return false;
}
void dfs2(long long u, long long tt) {
  vs[u][tt] = 1;
  for (long long i = 0; i < g[u][tt].size(); i++) {
    long long v = g[u][tt][i];
    if (!vs[v][tt]) dfs2(v, tt);
  }
}
int main() {
  scanf("%lld%lld", &n, &m);
  for (long long i = 0; i < m; i++) {
    long long u, v;
    scanf("%lld%lld", &u, &v);
    g[u][0].push_back(v);
    g[v][1].push_back(u);
  }
  if (round()) {
    printf("-1");
    return 0;
  }
  long long cnt = 0;
  string ans;
  for (long long i = 1; i <= n; i++) {
    if (!vs[i][0] && !vs[i][1])
      cnt++, ans += 'A';
    else
      ans += 'E';
    dfs2(i, 0);
    dfs2(i, 1);
  }
  cout << cnt << endl << ans << endl;
}
