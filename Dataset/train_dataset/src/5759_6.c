#include <bits/stdc++.h>
using namespace std;
int max(int a, int b, int c) { return max(a, max(b, c)); }
int n, K;
const int MAXN = 100005;
vector<int> tree[MAXN];
int lvl[MAXN];
long long dp[MAXN][20];
long long parent[MAXN];
bool visited[MAXN];
int counter[MAXN];
int ans[MAXN];
map<pair<int, int>, int> edges;
void dfs(int vrtx) {
  visited[vrtx] = true;
  for (auto u : tree[vrtx]) {
    if (!visited[u]) {
      dp[u][0] = vrtx;
      lvl[u] = lvl[vrtx] + 1;
      parent[u] = vrtx;
      dfs(u);
    }
  }
}
void build() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; (1 << j) < n; j++) {
      dp[i][j] = -1;
      visited[i] = false;
    }
  }
  lvl[0] = 1;
  dfs(0);
  for (int j = 1; (1 << j) < n; j++) {
    for (int i = 0; i < n; i++) {
      int mid = dp[i][j - 1];
      if (mid != -1) {
        dp[i][j] = dp[mid][j - 1];
      }
    }
  }
}
int jump(int i, int k) {
  for (int d = 0; d <= K && i != -1; d++) {
    if (((1 << d) & k) > 0) {
      i = dp[i][d];
    }
  }
  return i;
}
int lca(int a, int b) {
  if (lvl[a] < lvl[b]) swap(a, b);
  int i;
  for (i = K; i >= 0; i--) {
    if (lvl[a] - (1 << i) >= lvl[b]) {
      a = dp[a][i];
    }
  }
  if (a == b) return a;
  for (i = K; i >= 0; i--) {
    if (dp[a][i] != -1 && dp[a][i] != dp[b][i]) {
      a = dp[a][i];
      b = dp[b][i];
    }
  }
  return dp[a][0];
}
void dfs1(int vrtx) {
  visited[vrtx] = true;
  for (auto u : tree[vrtx]) {
    if (!visited[u]) {
      dfs1(u);
      counter[vrtx] += counter[u];
    }
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    tree[x - 1].push_back(y - 1);
    tree[y - 1].push_back(x - 1);
    if (x > y) swap(x, y);
    edges[{x - 1, y - 1}] = i;
    edges[{y - 1, x - 1}] = i;
  }
  K = (int)ceil(log2(n));
  build();
  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    counter[x - 1]++;
    counter[y - 1]++;
    counter[lca(x - 1, y - 1)] -= 2;
  }
  memset(visited, false, sizeof(visited));
  dfs1(0);
  for (int i = 1; i < n; i++) {
    ans[edges[{i, parent[i]}]] = counter[i];
  }
  for (int i = 0; i < n - 1; i++) cout << ans[i] << " ";
}
