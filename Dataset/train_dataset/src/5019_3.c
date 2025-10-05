#include <bits/stdc++.h>
using namespace std;
int N;
long long W[300001];
long long dp[300001];
vector<int> adj[300001];
long long ans = -2001001001001;
int cnt = 0;
void dfs2(int node, int parent) {
  for (int v : adj[node])
    if (v != parent) dfs2(v, node);
  dp[node] = W[node];
  for (int v : adj[node])
    if (v != parent) dp[node] += max(0LL, dp[v]);
  if (dp[node] == ans) {
    dp[node] = 0;
    cnt++;
  }
}
void dfs(int node, int parent) {
  for (int v : adj[node]) {
    if (v != parent) dfs(v, node);
  }
  dp[node] = W[node];
  for (int v : adj[node])
    if (v != parent) dp[node] += max(0LL, dp[v]);
  ans = max(ans, dp[node]);
}
int main() {
  scanf("%d", &N);
  for (int i = 1; i <= N; i++) scanf("%I64d", &W[i]);
  for (int i = 1; i < N; i++) {
    int X, Y;
    scanf("%d%d", &X, &Y);
    adj[X].push_back(Y);
    adj[Y].push_back(X);
  }
  dfs(1, 1);
  dfs2(1, 1);
  cout << ans * cnt << ' ' << cnt << '\n';
  return 0;
}
