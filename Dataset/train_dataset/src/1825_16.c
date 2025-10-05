#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007;
const double PI = acos(-1.);
const int N = 200000 + 5;
int n, a[N], w[N];
int din[N], dot[N], fot[N];
vector<int> G[N];
void dfsd(int u, int f) {
  int i, v;
  for (i = 0; i < G[u].size(); i++) {
    v = G[u][i];
    if (v == f) continue;
    dfsd(v, u);
  }
  if (w[u]) {
    din[u] = 1;
    for (i = 0; i < G[u].size(); i++) {
      v = G[u][i];
      if (v == f) continue;
      if (din[v])
        din[u] += din[v];
      else {
        din[u] = 0;
        break;
      }
    }
    dot[u] = 1;
    int mx = 0;
    for (i = 0; i < G[u].size(); i++) {
      v = G[u][i];
      if (v == f) continue;
      if (din[v])
        dot[u] += din[v];
      else
        mx = max(mx, dot[v]);
    }
    dot[u] += mx;
  } else
    din[u] = dot[u] = 0;
}
void Max2(int &a, int &b, int c) {
  if (c >= a) {
    b = a;
    a = c;
  } else
    b = max(b, c);
}
void dfsf(int u, int f) {
  int i, v;
  if (w[u]) {
    int b[2];
    b[0] = fot[u];
    b[1] = 0;
    int sum = 0;
    for (i = 0; i < G[u].size(); i++) {
      v = G[u][i];
      if (v == f) continue;
      if (din[v])
        sum += din[v];
      else
        Max2(b[0], b[1], dot[v]);
    }
    for (i = 0; i < G[u].size(); i++) {
      v = G[u][i];
      if (v == f) continue;
      if (din[v]) {
        fot[v] = sum - din[v] + 1 + b[0];
      } else {
        if (dot[v] == b[0])
          fot[v] = sum + 1 + b[1];
        else
          fot[v] = sum + 1 + b[0];
      }
      if (!w[v]) fot[v] = 0;
    }
  } else {
    for (i = 0; i < G[u].size(); i++) {
      v = G[u][i];
      if (v == f) continue;
      fot[v] = 0;
    }
  }
  for (i = 0; i < G[u].size(); i++) {
    v = G[u][i];
    if (v == f) continue;
    dfsf(v, u);
  }
}
int dfsdp(int u, int f) {
  int ret = 0;
  int i, v;
  if (w[u]) {
    ret = 1;
    int mx = 0;
    if (~f) mx = fot[u];
    for (i = 0; i < G[u].size(); i++) {
      v = G[u][i];
      if (v == f) continue;
      if (din[v])
        ret += din[v];
      else
        mx = max(mx, dot[v]);
    }
    ret += mx;
  }
  for (i = 0; i < G[u].size(); i++) {
    v = G[u][i];
    if (v == f) continue;
    int tmp = dfsdp(v, u);
    ret = max(ret, tmp);
  }
  return ret;
}
int cnt(int A) {
  int i;
  for (i = 1; i <= n; i++) w[i] = a[i] >= A;
  int rt = -1;
  for (i = 1; i <= n; i++)
    if (!w[i]) rt = i;
  if (rt == -1) return n;
  dfsd(rt, -1);
  fot[rt] = 0;
  dfsf(rt, -1);
  int ans = dfsdp(rt, -1);
  return ans;
}
int main() {
  if (0)
    freopen(
        "535F"
        ".out",
        "r", stdin);
  if (0)
    freopen(
        "535F"
        "wa.txt",
        "w", stdout);
  int i, j, _T;
  int k;
  while (~scanf("%d%d", &n, &k)) {
    for (i = 1; i <= n; i++) scanf("%d", &a[i]), G[i].clear();
    for (i = 1; i < n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[u].push_back(v), G[v].push_back(u);
    }
    vector<int> L;
    for (i = 1; i <= n; i++) L.push_back(a[i]);
    sort(L.begin(), L.end());
    L.erase(unique(L.begin(), L.end()), L.end());
    int le = 0, re = L.size() - 1, ge = -1;
    while (re >= le) {
      if (re - le <= 1) {
        if (cnt(L[re]) >= k)
          ge = re;
        else
          ge = le;
        break;
      }
      int mid = (le + re) / 2;
      if (cnt(L[mid]) >= k)
        le = mid;
      else
        re = mid;
    }
    printf("%d\n", L[ge]);
  }
  return 0;
}
