#include <bits/stdc++.h>
inline long long rd() {
  long long _x = 0;
  int _ch = getchar(), _f = 1;
  for (; !isdigit(_ch) && (_ch != '-') && (_ch != EOF); _ch = getchar())
    ;
  if (_ch == '-') {
    _f = 0;
    _ch = getchar();
  }
  for (; isdigit(_ch); _ch = getchar()) _x = _x * 10 + _ch - '0';
  return _f ? _x : -_x;
}
void write(long long _x) {
  if (_x >= 10)
    write(_x / 10), putchar(_x % 10 + '0');
  else
    putchar(_x + '0');
}
inline void wrt(long long _x, char _p) {
  if (_x < 0) putchar('-'), _x = -_x;
  write(_x);
  if (_p) putchar(_p);
}
int dfn[150005], sz[150005], id, dep[150005];
int f[20][150005];
std::vector<int> G[150005];
void dfs(int u, int fa) {
  f[0][u] = fa;
  dep[u] = dep[fa] + 1;
  for (int i = 1; i <= 19; i++) f[i][u] = f[i - 1][f[i - 1][u]];
  dfn[u] = ++id;
  sz[u] = 1;
  for (auto i : G[u])
    if (i != fa) {
      dfs(i, u);
      sz[u] += sz[i];
    }
}
inline int __lca(int a, int b) {
  if (dep[a] < dep[b]) std::swap(a, b);
  for (int i = 19; i >= 0; i--)
    if (dep[f[i][a]] >= dep[b]) {
      a = f[i][a];
    }
  if (a == b) return a;
  for (int i = 19; i >= 0; i--)
    if (f[i][a] != f[i][b]) {
      a = f[i][a];
      b = f[i][b];
    }
  return f[0][a];
}
inline int jump(int u, int x) {
  for (int i = 19; i >= 0; i--)
    if (x >= (1 << i)) u = f[i][u], x -= (1 << i);
  return u;
}
struct node {
  int ls, rs, sum;
} tr[150005 * 40];
int cnt, root;
void upd(int &pos, int l, int r, int w, int v) {
  if (!pos) pos = ++cnt;
  tr[pos].sum += v;
  if (l == r) return;
  int mid = (l + r) >> 1;
  if (w <= mid)
    upd(tr[pos].ls, l, mid, w, v);
  else
    upd(tr[pos].rs, mid + 1, r, w, v);
}
int query(int pos, int l, int r, int ql, int qr) {
  if (!pos || r < ql || l > qr) return 0;
  if (ql <= l && r <= qr) return tr[pos].sum;
  int mid = (l + r) >> 1;
  return query(tr[pos].ls, l, mid, ql, qr) +
         query(tr[pos].rs, mid + 1, r, ql, qr);
}
void clear(int pos) {
  if (!pos) return;
  clear(tr[pos].ls), clear(tr[pos].rs);
  tr[pos] = {0, 0, 0};
}
int n, m, k;
std::vector<std::pair<int, int>> vt[150005];
void insert(int A, int u) {
  if (dep[A] - dep[u] >= k) {
    int x = jump(A, dep[A] - dep[u] - k);
    upd(root, 1, n, dfn[x], 1);
    if (dfn[x] + sz[x] <= n) upd(root, 1, n, dfn[x] + sz[x], -1);
  }
}
long long ans = 0;
void DFS1(int u, int fa) {
  for (auto i : G[u])
    if (i != fa) DFS1(i, u);
  for (auto i : vt[u])
    ans += query(root, 1, n, 1, dfn[i.first]) +
           query(root, 1, n, 1, dfn[i.second]);
  for (auto i : vt[u]) {
    insert(i.first, u), insert(i.second, u);
  }
}
std::vector<int> to[150005];
int sta[150005], top, LCA;
inline bool cmp(int A, int B) { return dfn[A] < dfn[B]; }
std::vector<int> g[150005];
int findto(int A, int B) {
  if (dep[A] - dep[LCA] >= k) {
    return LCA;
  } else {
    int t = k - (dep[A] - dep[LCA]);
    if (dep[B] - dep[LCA] < t) return 0;
    t = dep[B] - dep[LCA] - t;
    return jump(B, t);
  }
}
std::pair<std::vector<int>, int> solve(int x) {
  std::pair<std::vector<int>, int> res;
  res.second = 0;
  for (auto i : g[x]) {
    std::pair<std::vector<int>, int> v = solve(i);
    if (res.first.size() < v.first.size()) {
      std::swap(res, v);
    }
    for (auto j : v.first) {
      int v = findto(x, j);
      ans += query(res.second, 1, n, dfn[v], dfn[v] + sz[v] - 1);
    }
    for (auto j : v.first) {
      upd(res.second, 1, n, dfn[j], 1);
      res.first.push_back(j);
    }
    clear(v.second);
  }
  for (auto i : to[x]) {
    int v = findto(x, i);
    ans += query(res.second, 1, n, dfn[v], dfn[v] + sz[v] - 1);
    upd(res.second, 1, n, dfn[i], 1);
    res.first.push_back(i);
  }
  g[x].clear();
  return res;
}
int main() {
  n = rd(), m = rd(), k = rd();
  for (int i = 2; i <= n; i++) {
    int x = rd(), y = rd();
    G[x].push_back(y);
    G[y].push_back(x);
  }
  dfs(1, 0);
  for (int i = 1; i <= m; i++) {
    int x = rd(), y = rd();
    if (dfn[x] > dfn[y]) std::swap(x, y);
    int A = __lca(x, y);
    vt[A].push_back(std::make_pair(x, y));
  }
  DFS1(1, 0);
  clear(root);
  root = 0;
  cnt = 0;
  for (int u = 1; u <= n; u++) {
    std::sort(vt[u].begin(), vt[u].end());
    for (auto j : vt[u]) {
      insert(j.second, u);
    }
    for (auto j : vt[u]) {
      ans += query(root, 1, n, 1, dfn[j.first]);
    }
    clear(root), root = 0, cnt = 0;
  }
  for (int u = 1; u <= n; u++) {
    std::vector<int> h;
    LCA = u;
    for (auto i : vt[u]) {
      if (to[i.first].empty()) h.push_back(i.first);
      to[i.first].push_back(i.second);
    }
    std::sort(h.begin(), h.end(), cmp);
    sta[top = 1] = u;
    for (int i = 0, l; i < h.size(); i++)
      if (h[i] != u) {
        l = __lca(h[i], sta[top]);
        if (l != sta[top]) {
          while (dfn[l] < dfn[sta[top - 1]])
            g[sta[top - 1]].push_back(sta[top]), top--;
          if (dfn[l] > dfn[sta[top - 1]])
            g[l].push_back(sta[top]), sta[top] = l;
          else
            g[l].push_back(sta[top--]);
        }
        sta[++top] = h[i];
      }
    for (int i = 1; i < top; i += 1) g[sta[i]].push_back(sta[i + 1]);
    int x = solve(sta[1]).second;
    for (auto i : h) to[i].clear();
    clear(x);
    cnt = 0;
  }
  wrt(ans, '\n');
}
