#include <bits/stdc++.h>
const int maxn = 2e5 + 222;
const int mod = 1e9 + 7;
using ll = long long;
const int lim = 1e6;
int n, k, p[maxn], len, ans, mul = 1, one, max, vis[maxn], s[maxn], cnt[maxn],
                             f[maxn], fac[maxn], in[maxn], g[maxn],
                             iv[lim + 100];
std::vector<int> chain, cycle;
std::vector<int> F[maxn];
int cw[maxn];
int inv(int x) {
  return x <= lim ? iv[x] : (ll)(mod - mod / x) * inv(mod % x) % mod;
}
void extend(int x, int f = 1) {
  if (f) mul = (ll)mul * inv(F[x].back()) % mod;
  cw[x]++;
  F[x].push_back((ll)x *
                 (F[x][cw[x] - 1] +
                  (cw[x] > 1 ? (ll)(cw[x] - 1) * F[x][cw[x] - 2] % mod : 0)) %
                 mod);
  if (f) mul = (ll)mul * F[x].back() % mod;
}
void erase(int x, int f = 1) {
  if (f) mul = (ll)mul * inv(F[x].back()) % mod;
  cw[x]--;
  F[x].pop_back();
  if (f) mul = (ll)mul * F[x].back() % mod;
}
void dfs(int u, int lim) {
  if (u == len) {
    int x = max;
    int way = 1;
    for (int i = 1; i <= lim; ++i) {
      assert(1 <= cnt[i] && cnt[i] <= n);
      way = (ll)way * fac[cnt[i] - 1] % mod;
      x = std::max(x, s[i]);
    }
    if (x == 1) {
      ans = (ans + way) % mod;
    } else if (x == 2) {
      ans = (ans + way) % mod;
    } else {
      ans = (ans + (ll)mul * way % mod) % mod;
    }
    return;
  }
  for (int i = 1; i <= lim + 1; ++i) {
    int prev = mul;
    if (s[i]) erase(s[i]);
    s[i] += chain[u];
    extend(s[i]);
    cnt[i]++;
    dfs(u + 1, std::max(lim, i));
    cnt[i]--;
    if (s[i]) erase(s[i], 0);
    s[i] -= chain[u];
    if (s[i]) extend(s[i], 0);
    mul = prev;
  }
}
int main() {
  scanf("%d%d", &n, &k);
  f[0] = f[1] = fac[0] = g[0] = 1;
  iv[1] = 1;
  for (int i = 2; i <= lim; ++i)
    iv[i] = (ll)(mod - mod / i) * iv[mod % i] % mod;
  for (int i = 1; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % mod;
  for (int i = 2; i <= n; ++i)
    f[i] = (f[i - 1] + (ll)(i - 1) * f[i - 2] % mod) % mod;
  for (int i = 2; i <= n; i += 2) g[i] = (ll)g[i - 2] * (i - 1) % mod;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &p[i]);
    in[p[i]]++;
  }
  for (int i = 1; i <= n; ++i) {
    if (!in[i]) {
      int u = i, c = 0;
      while (u) {
        vis[u] = 1;
        c++;
        u = p[u];
      }
      chain.push_back(c);
    }
  }
  for (int i = 1; i <= n; ++i) {
    F[i].push_back(1);
    if (!vis[i]) {
      int u = i, c = 0;
      while (!vis[u]) {
        vis[u] = 1;
        c++;
        u = p[u];
      }
      cycle.push_back(c);
    }
  }
  for (int c : cycle) {
    max = std::max(max, c);
    extend(c);
  }
  len = chain.size();
  dfs(0, 0);
  printf("%d", ans);
  return 0;
}
