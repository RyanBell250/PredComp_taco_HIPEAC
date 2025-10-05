#include <bits/stdc++.h>
using namespace std;
const long long N = 2e5 + 5;
vector<long long> g[N];
long long sz[N], dp[N], ans[N];
void for_root(long long v, long long p) {
  sz[v] = 1;
  for (long long to : g[v]) {
    if (to != p) {
      for_root(to, v);
      sz[v] += sz[to];
      dp[v] += dp[to];
    }
  }
  dp[v] += sz[v];
}
long long n;
void dfs(long long v, long long p) {
  ans[v] = dp[v];
  long long fixed_v = dp[v];
  for (long long to : g[v]) {
    if (to != p) {
      long long fixed_to = dp[to];
      dp[v] -= dp[to] + sz[to];
      dp[to] += dp[v] + (n - sz[to]);
      dfs(to, v);
      dp[to] = fixed_to;
      dp[v] = fixed_v;
    }
  }
}
int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (long long i = 1; i < n; i++) {
    long long a, b;
    cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  for_root(1, 1);
  dfs(1, 1);
  cout << (*max_element(ans, ans + N));
  return 0;
}
