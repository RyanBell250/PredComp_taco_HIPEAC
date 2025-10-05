#include <bits/stdc++.h>
using namespace std;
const int N = 300010;
bool line[N];
long long d[N];
vector<pair<long long, long long> > v[N], w;
int n, m, x, y, z;
vector<int> vis;
void dfs(int x, int p, long long val) {
  d[x] = val;
  if (x == n) {
    vis.push_back(n);
    line[n] = 1;
  }
  for (pair<long long, long long> y : v[x]) {
    if (y.first == p) continue;
    dfs(y.first, x, y.second + val);
    if (line[y.first]) {
      vis.push_back(x);
      line[x] = line[y.first];
    }
  }
}
int flag = 0;
long long mx = -1, res = 0;
;
void dfs2(int x, int p, int l) {
  for (pair<long long, long long> y : v[x]) {
    if (line[y.first]) continue;
    flag = 1;
    return;
  }
  if (mx >= 0 && l > 0)
    res = max(res, max(mx + d[n] + d[x] - 2 * d[p],
                       d[n] + d[x] - 2 * d[p] + d[vis[l - 1]]));
  else if (l > 0)
    res = max(res, d[n] + d[x] - 2 * d[p] + d[vis[l - 1]]);
  mx = max(mx, d[x]);
}
int main() {
  cin >> n >> m;
  for (int i = 1; i < n; i++) {
    scanf("%d %d %d", &x, &y, &z);
    v[x].push_back({y, z});
    v[y].push_back({x, z});
  }
  dfs(1, 0, 0);
  res = 0;
  reverse(vis.begin(), vis.end());
  for (int i = 2; i < vis.size(); i++) {
    res = max(res, d[vis[i - 2]] + d[n] - d[vis[i]]);
  }
  int pr;
  for (int i = 0; flag == 0 && i < vis.size(); i++) {
    if (mx >= 0) res = max(res, d[n] - d[vis[i]] + mx);
    x = vis[i];
    pr = 0;
    for (pair<long long, long long> p : v[x]) {
      if (line[p.first]) continue;
      if (pr > 0 || flag) {
        flag = 1;
        break;
      }
      pr++;
      dfs2(p.first, x, i);
    }
  }
  while (m--) {
    long long x;
    scanf("%lld", &x);
    if (flag)
      printf("%lld\n", d[n]);
    else
      printf("%lld\n", min(d[n], res + x));
  }
  return 0;
}
