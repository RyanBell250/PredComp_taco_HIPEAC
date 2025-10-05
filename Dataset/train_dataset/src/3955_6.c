#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;
long long powmod(long long a, long long b) {
  long long res = 1;
  a %= mod;
  for (; b; b >>= 1) {
    if (b & 1) res = res * a % mod;
    a = a * a % mod;
  }
  return res;
}
const int N = 201000;
vector<int> e[N], sp[N];
long long dp[N], ans;
int dep[N], ce[N], sz[N], n, u, v, rt;
void getlr(int u, int op, int &l, int &r) {
  assert(((int)(e[u]).size()) == 3);
  if (e[u][0] == op)
    l = e[u][1], r = e[u][2];
  else if (e[u][1] == op)
    l = e[u][0], r = e[u][2];
  else
    l = e[u][0], r = e[u][1];
}
int getop(int u, int op) {
  assert(((int)(e[u]).size()) == 2);
  if (e[u][0] == op)
    return e[u][1];
  else
    return e[u][0];
}
long long del(int u, int v) {
  bool f1 = ((int)(e[ce[u]]).size()) == 1, f2 = ((int)(e[ce[v]]).size()) == 1;
  int d1 = dep[ce[u]] - dep[u] + 1, d2 = dep[ce[v]] - dep[v] + 1;
  if (!f1 && !f2)
    return 0;
  else if (f1 && !f2) {
    if (d1 >= d2)
      return 0;
    else
      return dp[sp[ce[v]][d2 - d1 - 1]];
  } else if (!f1 && f2) {
    if (d1 <= d2)
      return 0;
    else
      return dp[sp[ce[u]][d1 - d2 - 1]];
  } else {
    if ((d1 + d2) % 2 == 0)
      return max(1, abs(d1 - d2) / 2);
    else
      return 0;
  }
}
void gg(int u, int v, int r, int l) {
  if (((int)(e[l]).size()) == 1)
    dp[u] = (dp[u] + dp[r]) % mod;
  else if (((int)(e[l]).size()) == 3) {
    int opl = 0, opr = 0;
    getlr(l, v, opl, opr);
    if (((int)(e[ce[opr]]).size()) == 1 &&
        dep[ce[opr]] - dep[opr] <= dep[v] - dep[u])
      dp[u] = (dp[u] + del(opl, r)) % mod;
    if (((int)(e[ce[opl]]).size()) == 1 &&
        dep[ce[opl]] - dep[opl] <= dep[v] - dep[u])
      dp[u] = (dp[u] + del(opr, r)) % mod;
  } else {
    int opl = getop(l, v);
    if (((int)(e[ce[opl]]).size()) == 1 &&
        dep[ce[opl]] - dep[opl] <= dep[v] - dep[u])
      dp[u] = (dp[u] + dp[r]) % mod;
    dp[u] = (dp[u] + del(opl, r)) % mod;
  }
  if (((int)(e[ce[l]]).size()) == 1 &&
      dep[ce[l]] - dep[v] <= dep[v] - dep[u] - 1)
    dp[u] = (dp[u] + dp[r]) % mod;
}
void dfs(int u, int f) {
  sz[u] = 1;
  dep[u] = dep[f] + 1;
  for (int i = 0; i < ((int)(e[u]).size()); i++) {
    int v = e[u][i];
    if (v == f) continue;
    dfs(v, u);
    sz[u] += sz[v];
  }
  if (((int)(e[u]).size()) != 2)
    ce[u] = u;
  else
    ce[u] = ce[getop(u, f)];
  sp[ce[u]].push_back(u);
  if (sz[u] % 2 == 0) {
    if (((int)(e[u]).size()) == 3) {
      int l = 0, r = 0;
      getlr(u, f, l, r);
      if (((int)(e[l]).size()) == 2)
        dp[u] = (dp[u] + del(getop(l, u), r)) % mod;
      else if (((int)(e[l]).size()) == 1)
        dp[u] = (dp[u] + dp[r]) % mod;
      if (((int)(e[r]).size()) == 2)
        dp[u] = (dp[u] + del(getop(r, u), l)) % mod;
      else if (((int)(e[r]).size()) == 1)
        dp[u] = (dp[u] + dp[l]) % mod;
    } else if (((int)(e[u]).size()) == 2) {
      int v = ce[u];
      if (((int)(e[v]).size()) == 1)
        dp[u] = sz[u] / 2;
      else {
        int ff = 0, l = 0, r = 0;
        for (int i = 0; i < 3; i++)
          if (dep[e[v][i]] < dep[v]) ff = e[v][i];
        getlr(v, ff, l, r);
        gg(u, v, l, r);
        gg(u, v, r, l);
      }
    }
  }
}
void gao(int rt, int op, int l, int r) {
  if (((int)(e[op]).size()) == 1)
    ans = (ans + dp[l] * dp[r]) % mod;
  else if (((int)(e[op]).size()) == 3) {
    int opl = 0, opr = 0;
    getlr(op, rt, opl, opr);
    ans = (ans + del(l, opl) * del(r, opr) + del(l, opr) * del(r, opl)) % mod;
  } else {
    int opl = getop(op, rt);
    ans = (ans + dp[l] * del(r, opl) + dp[r] * del(l, opl)) % mod;
  }
}
int main() {
  scanf("%d", &n);
  n *= 2;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (int i = 1; i < n + 1; i++)
    if (((int)(e[i]).size()) > 3) return puts("0"), 0;
  for (int i = 1; i < n + 1; i++)
    if (((int)(e[i]).size()) == 3) {
      rt = i;
      break;
    }
  if (rt == 0) {
    if (n == 2)
      puts("2");
    else
      printf("%I64d\n", (n * (n / 2 - 1ll) + 4) % mod);
    return 0;
  }
  for (int i = 0; i < 3; i++) dfs(e[rt][i], rt);
  gao(rt, e[rt][0], e[rt][1], e[rt][2]);
  gao(rt, e[rt][1], e[rt][0], e[rt][2]);
  gao(rt, e[rt][2], e[rt][0], e[rt][1]);
  ans = ans * 4 % mod;
  printf("%I64d\n", ans);
}
