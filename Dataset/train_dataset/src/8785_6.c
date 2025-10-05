#include <bits/stdc++.h>
using namespace std;
int par[505];
int r[505];
int res, u[10005], v[10005];
inline void init(int n) {
  res = n;
  for (int i = 0; i < n; i++) {
    par[i] = i;
    r[i] = 0;
  }
}
inline int f(int x) {
  if (par[x] == x)
    return x;
  else
    return par[x] = f(par[x]);
}
inline void unite(int x, int y) {
  x = f(x);
  y = f(y);
  if (x == y) return;
  res--;
  if (r[x] < r[y])
    par[x] = y;
  else {
    par[y] = x;
    if (r[x] == r[y]) r[x]++;
  }
}
int main() {
  ios::sync_with_stdio(false);
  int n, m, k, l, r;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> u[i] >> v[i];
    u[i]--;
    v[i]--;
  }
  cin >> k;
  for (int t = 1; t <= k; t++) {
    cin >> l >> r;
    l--;
    r--;
    init(n);
    for (int i = 0; i < l; i++) unite(u[i], v[i]);
    for (int i = r + 1; i < m; i++) unite(u[i], v[i]);
    cout << res << endl;
  }
}
