#include <bits/stdc++.h>
using namespace std;
long long n, q, anw;
vector<long long> g[300005];
long long dfs(long long a, long long p) {
  long long ret = g[a].size() - 1;
  vector<long long> ar;
  for (int i = 0; i < g[a].size(); i++)
    if (g[a][i] != p) ar.push_back(dfs(g[a][i], a));
  if (p != -1 && g[a].size() == 1) return 1;
  sort(ar.rbegin(), ar.rend());
  if (ar.size() >= 2) anw = max(anw, ret + ar[0] + ar[1]);
  anw = max(anw, ret + ar[0] + 1);
  return ret + ar[0];
}
void solve() {
  cin >> n;
  anw = 0;
  for (int i = 0; i <= n; i++) g[i].clear();
  for (int i = 1; i < n; i++) {
    long long a, b;
    cin >> a >> b;
    g[a].push_back(b), g[b].push_back(a);
  }
  dfs(1, -1);
  cout << anw << "\n";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> q;
  while (q--) solve();
  return 0;
}
