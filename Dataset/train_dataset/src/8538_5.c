#include <bits/stdc++.h>
using namespace std;
vector<int> e[200005], dp[200005];
int n;
const int B = 234;
inline int query(int x, int y) {
  y = min(y, (int)dp[x].size() - 1);
  return dp[x][y];
}
inline void dfs(int u, int f) {
  int cnt = 0;
  vector<int> v;
  for (auto x : e[u])
    if (x != f) dfs(x, u), ++cnt, v.push_back(x);
  int sum = 0;
  for (int i = 0; i <= n; i++) {
    int now = 0;
    for (auto x : v) now += max(1, query(x, i) - i);
    dp[u].push_back(now + sum);
    if (i == B) {
      vector<int> V;
      for (auto x : v) {
        if (query(x, i) - i <= 1)
          sum++;
        else
          V.push_back(x);
      }
      swap(v, V);
    }
    if (now + sum == cnt) break;
  }
}
signed main(int argc, char** argv) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs(1, 0);
  int q;
  cin >> q;
  while (q--) {
    int x, y;
    cin >> x >> y;
    cout << query(x, y) << "\n";
  }
  return 0;
}
