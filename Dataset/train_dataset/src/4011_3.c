#include <bits/stdc++.h>
using namespace std;
const int mod = 1000 * 1000 * 1000 + 7;
const int maxn = 10000 + 10;
const int inf = 100000000;
const int base = 139;
int n, k, l, b[maxn], first[11], c[maxn], r, t, d[maxn], dist[22][22],
    dp[(1 << 20) + 3];
vector<int> v[maxn], a;
bool mark[maxn];
void bfs(int e) {
  queue<int> q;
  memset(mark, 0, sizeof mark);
  for (int i = 0; i < maxn; i++) d[i] = inf;
  q.push(e);
  d[e] = 0;
  mark[e] = 1;
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = 0; i < v[x].size(); i++)
      if (!mark[v[x][i]]) {
        q.push(v[x][i]);
        d[v[x][i]] = d[x] + 1;
        mark[v[x][i]] = 1;
      }
  }
  for (int i = 0; i <= n; i++)
    if (b[i]) dist[b[e]][b[i]] = d[i];
}
int f(int x) {
  if (!x) return 0;
  if (dp[x] != -1) return dp[x];
  int o = -1, res = inf;
  for (int i = 0; i < r; i++) {
    if ((1 << i) & x) {
      if (o == -1)
        o = i;
      else
        res = min(res, f(x - (1 << o) - (1 << i)) + dist[o + 1][i + 1]);
    }
  }
  return dp[x] = res;
}
int main() {
  memset(dp, -1, sizeof dp);
  for (int i = 0; i < 22; i++)
    for (int j = 0; j < 22; j++) dist[i][j] = inf;
  cin >> n >> k >> l;
  for (int i = 1; i <= k; i++) {
    cin >> first[i];
    c[first[i]] = 1;
  }
  for (int i = 1; i <= l; i++) {
    int x;
    cin >> x;
    a.push_back(x);
  }
  sort(a.begin(), a.end());
  a.resize(unique(a.begin(), a.end()) - a.begin());
  for (int i = 0; i <= n; i++)
    if (c[i] != c[i + 1]) b[i] = ++t;
  for (int i = 0; i < l; i++)
    for (int j = 0; j + a[i] <= n; j++) {
      v[j].push_back(j + a[i]);
      v[j + a[i]].push_back(j);
    }
  for (int i = 0; i <= n; i++)
    if (b[i]) {
      r++;
      bfs(i);
    }
  int k = f((1 << r) - 1);
  if (k >= inf)
    cout << -1 << endl;
  else
    cout << k << endl;
  return 0;
}
