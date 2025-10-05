#include <bits/stdc++.h>
const int N = 300200;
using namespace std;
int n;
int tim;
int tin[N];
int tout[N];
int dep[N];
int mod = 1e9 + 7;
pair<int, int> t[4 * N];
vector<int> v[N];
void dfs(int x, int g) {
  tin[x] = tout[x] = ++tim;
  dep[tin[x]] = g;
  for (auto y : v[x]) {
    dfs(y, g - 1);
    tout[x] = tout[y];
  }
}
void push(int x) {
  t[x * 2].first += t[x].first;
  t[x * 2].second += t[x].second;
  t[x * 2 + 1].first += t[x].first;
  t[x * 2 + 1].second += t[x].second;
  t[x * 2].first %= mod;
  t[x * 2].second %= mod;
  t[x * 2 + 1].first %= mod;
  t[x * 2 + 1].second %= mod;
  t[x].first = t[x].second = 0;
}
void upd(int x, int l, int r, int tl, int tr, int f1, int f2) {
  if (tl > tr) return;
  if (l == tl && r == tr) {
    t[x].first = (t[x].first + f1) % mod;
    t[x].second = (t[x].second + f2) % mod;
    return;
  }
  push(x);
  int m = (l + r) / 2;
  upd(x * 2, l, m, tl, min(m, tr), f1, f2);
  upd(x * 2 + 1, m + 1, r, max(m + 1, tl), tr, f1, f2);
}
int get(int x, int l, int r, int g) {
  if (l == r) {
    int ans = (1ll * t[x].second * dep[l]) % mod;
    ans = (t[x].first + ans) % mod;
    return ans;
  }
  push(x);
  int m = (l + r) / 2;
  if (g <= m)
    return get(x * 2, l, m, g);
  else
    return get(x * 2 + 1, m + 1, r, g);
}
int main() {
  ios_base::sync_with_stdio(0);
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    int x;
    scanf("%d", &x);
    v[x].push_back(i);
  }
  dfs(1, n);
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++) {
    int t, v, x, k;
    scanf("%d", &t);
    if (t == 1) {
      scanf("%d%d%d", &v, &x, &k);
      long long f = 1ll * x - 1ll * dep[tin[v]] * k;
      f = f % mod + mod;
      upd(1, 1, n, tin[v], tout[v], f % mod, k);
    } else {
      scanf("%d", &v);
      printf("%d\n", get(1, 1, n, tin[v]));
    }
  }
}
