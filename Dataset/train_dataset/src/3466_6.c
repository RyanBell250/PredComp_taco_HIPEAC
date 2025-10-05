#include <bits/stdc++.h>
using namespace std;
const int MX = 5e2 + 10;
int cnt[MX];
vector<int> adj[MX];
int center;
int match[MX];
bool mrk[MX], fmatch[MX];
bool dfs(int v) {
  if (mrk[v] || v == center) return 0;
  mrk[v] = 1;
  for (int u : adj[v]) {
    if (u == center) continue;
    if (match[u] == 0 || dfs(match[u])) {
      match[u] = v;
      return 1;
    }
  }
  return 0;
}
int main() {
  ios::sync_with_stdio();
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int v, u;
    cin >> v >> u;
    cnt[v]++;
    if (v != u) cnt[u]++;
    adj[v].push_back(u);
  }
  int ans = n * n;
  for (center = 1; center <= n; center++) {
    int siz = 0, fnd = 1;
    fill(fmatch, fmatch + n + 1, 0);
    fill(match, match + n + 1, 0);
    while (fnd) {
      fnd = 0;
      fill(mrk, mrk + n + 1, 0);
      for (int i = 1; i <= n; i++) {
        if (i != center && !mrk[i] && !fmatch[i] && dfs(i)) {
          fmatch[i] = 1;
          fnd = 1;
          siz++;
        }
      }
    }
    ans = min(ans, (2 * n - 1 - cnt[center]) + (m - cnt[center] - siz) +
                       (n - 1 - siz));
  }
  cout << ans << endl;
  return 0;
}
