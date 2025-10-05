#include <bits/stdc++.h>
using namespace std;
const int maxn = 300005;
int i, i0, n, m, k, dep[maxn], siz[maxn], fa[maxn], son[maxn], idx[maxn], cnt,
    top[maxn], pre[maxn];
bool vis[maxn];
vector<int> mp[maxn];
void dfs(int now, int root, int deep) {
  dep[now] = deep, fa[now] = root, siz[now] = 1, son[now] = -1, vis[now] = 1;
  for (auto i : mp[now]) {
    if (i == root || vis[i]) continue;
    dfs(i, now, deep + 1);
    siz[now] += siz[i];
    if (son[now] == -1 || siz[son[now]] < siz[i]) son[now] = i;
  }
}
void dfs0(int now, int topf) {
  idx[now] = ++cnt, top[now] = topf, vis[now] = 1;
  if (son[now] != -1 && !vis[son[now]]) dfs0(son[now], topf);
  for (auto i : mp[now]) {
    if (i == fa[now] || i == son[now] || vis[i]) continue;
    dfs0(i, i);
  }
}
int tree[maxn * 4], lazy[maxn * 4];
void p_tree(int l, int r, int p) {
  if (lazy[p] == -1) return;
  lazy[p * 2] = lazy[p], lazy[p * 2 + 1] = lazy[p];
  tree[p * 2] = ((l + r) / 2 - l + 1) * lazy[p],
           tree[p * 2 + 1] = (r - (l + r) / 2) * lazy[p];
  lazy[p] = -1;
}
void c_tree(int l, int r, int p, int a, int b, int v) {
  if (l == a && r == b)
    lazy[p] = v, tree[p] = (r - l + 1) * v;
  else {
    p_tree(l, r, p);
    if (b <= (l + r) / 2)
      c_tree(l, (l + r) / 2, p * 2, a, b, v);
    else if (a >= (l + r) / 2 + 1)
      c_tree((l + r) / 2 + 1, r, p * 2 + 1, a, b, v);
    else
      c_tree(l, (l + r) / 2, p * 2, a, (l + r) / 2, v),
          c_tree((l + r) / 2 + 1, r, p * 2 + 1, (l + r) / 2 + 1, b, v);
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
  }
}
int q_tree(int l, int r, int p, int a, int b) {
  if (l == a && r == b)
    return tree[p];
  else {
    p_tree(l, r, p);
    if (b <= (l + r) / 2)
      return q_tree(l, (l + r) / 2, p * 2, a, b);
    else if (a >= (l + r) / 2 + 1)
      return q_tree((l + r) / 2 + 1, r, p * 2 + 1, a, b);
    else
      return q_tree(l, (l + r) / 2, p * 2, a, (l + r) / 2) +
             q_tree((l + r) / 2 + 1, r, p * 2 + 1, (l + r) / 2 + 1, b);
  }
}
int q_range(int x, int y) {
  int ans = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    ans += q_tree(1, n, 1, idx[top[x]], idx[x]);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  ans += q_tree(1, n, 1, idx[x], idx[y]);
  return ans;
}
int lca(int x, int y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x, y);
    x = fa[top[x]];
  }
  if (dep[x] > dep[y]) swap(x, y);
  return x;
}
void c_son(int x, int k) { c_tree(1, n, 1, idx[x], idx[x] + siz[x] - 1, k); }
queue<int> q;
stack<int> s;
void out(int now, int x, int y) {
  int p = lca(now, x);
  while (now != p) q.push(now), now = fa[now];
  while (1) {
    s.push(x);
    if (x == p)
      break;
    else
      x = fa[x];
  }
  while (!s.empty()) q.push(s.top()), s.pop();
  printf("%d\n", q.size() + (y != 0));
  if (y) printf("%d ", y);
  while (!q.empty()) printf("%d ", q.front()), q.pop();
  printf("\n");
}
int main() {
  int r = 1;
  scanf("%d %d %d", &n, &m, &k);
  for (i = 1; i <= n; i++) pre[i] = i;
  while (m--) {
    int x, y;
    scanf("%d %d", &x, &y);
    mp[x].push_back(y), mp[y].push_back(x);
  }
  memset(lazy, -1, sizeof(lazy));
  dfs(r, -1, 1);
  cnt = 0;
  memset(vis, 0, sizeof(vis));
  dfs0(r, r);
  int maxi = 1;
  for (i = 2; i <= n; i++)
    if (dep[i] > dep[maxi]) maxi = i;
  if (dep[maxi] >= n / k) {
    printf("PATH\n");
    printf("%d\n", dep[maxi]);
    while (maxi != -1)
      printf("%d%c", maxi, (fa[maxi] != -1) ? ' ' : '\n'), maxi = fa[maxi];
  } else {
    printf("CYCLES\n");
    c_son(r, 1);
    int cnt = k, now = 1;
    while (k--) {
      while (son[now] != -1) now++;
      int x = -1, y = -1;
      for (auto i : mp[now])
        if (i != fa[now]) x = i;
      for (auto i : mp[now])
        if (i != fa[now] && i != x) y = i;
      if (q_range(now, x) % 3)
        out(now, x, 0);
      else if (q_range(now, y) % 3)
        out(now, y, 0);
      else
        out(x, y, now);
      now++;
    }
  }
  return 0;
}
