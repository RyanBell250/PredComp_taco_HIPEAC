#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
vector<int> g[maxn], rg[maxn], v[maxn], lis;
map<int, int> mp;
int n, m, c[maxn], ind, mark[maxn], ans;
bool key, pol[maxn];
void DFS(int s) {
  mark[s] = 1;
  mp[c[s]]++;
  for (int p : v[s])
    if (!mark[p]) c[p] = c[s], DFS(p);
}
void DFS2(int x) {
  if (key) return;
  mark[x] = 1;
  for (int p : g[x])
    if (mark[p] == 0)
      DFS2(p);
    else if (mark[p] == 1)
      key = 1;
  mark[x] = 2;
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    g[a].push_back(b), v[a].push_back(b), v[b].push_back(a);
  }
  for (int i = 0; i < n; i++)
    if (!mark[i]) c[i] = ind++, DFS(i);
  fill(mark, mark + maxn, 0);
  for (int i = 0; i < n; i++)
    if (!mark[i]) {
      DFS2(i);
      if (key) key = 0, pol[c[i]] = 1;
    }
  for (int i = 0; i < ind; i++)
    if (pol[i])
      ans += mp[i];
    else
      ans += mp[i] - 1;
  cout << ans;
}
