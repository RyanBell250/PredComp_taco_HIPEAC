#include <bits/stdc++.h>
using namespace std;
int n, m, s, t;
int head[200005], nxt[400005], to[400005], cnt;
int w[200005];
unsigned long long base[200005], base1[200005];
int read();
void add(int f, int t, int wei) {
  nxt[++cnt] = head[f], head[f] = cnt, to[cnt] = t;
  w[cnt] = wei;
  return;
}
int root[400005];
struct Seg {
  int idcnt;
  int ls[4000006], rs[4000006], tsum[4000006];
  unsigned long long ths[4000006], ths1[4000006];
  void update(int k) {
    tsum[k] = tsum[ls[k]] + tsum[rs[k]];
    ths[k] = (ths[ls[k]] + ths[rs[k]]) % 1000000007;
    ths1[k] = ths1[ls[k]] + ths1[rs[k]];
    return;
  }
  int build(int l, int r, int v) {
    int ret = ++idcnt;
    if (l == r) {
      tsum[ret] = v;
      ths[ret] = base[l] * v, ths1[ret] = base1[l] * v;
      return ret;
    }
    int mid = l + r >> 1;
    ls[ret] = build(l, mid, v);
    rs[ret] = build(mid + 1, r, v);
    update(ret);
    return ret;
  }
  int query(int l, int r, int k, int st, int en) {
    if (st > r || en < l) return 0;
    if (st <= l && en >= r) return tsum[k];
    int mid = l + r >> 1;
    return query(l, mid, ls[k], st, en) + query(mid + 1, r, rs[k], st, en);
  }
  int find(int l, int r, int k, int pos) {
    if (l == r) return l;
    int mid = l + r >> 1;
    if (pos > mid) return find(mid + 1, r, rs[k], pos);
    if (query(l, mid, ls[k], pos, mid) == mid - pos + 1)
      return find(mid + 1, r, rs[k], mid + 1);
    return find(l, mid, ls[k], pos);
  }
  int isrt(int l, int r, int k, int pos) {
    int ret = ++idcnt;
    ls[ret] = ls[k], rs[ret] = rs[k];
    if (l == r) {
      tsum[ret] = 1;
      ths[ret] = base[l], ths1[ret] = base1[l];
      return ret;
    }
    int mid = l + r >> 1;
    if (pos <= mid)
      ls[ret] = isrt(l, mid, ls[k], pos);
    else
      rs[ret] = isrt(mid + 1, r, rs[k], pos);
    update(ret);
    return ret;
  }
  int move(int l, int r, int k, int k1, int st, int en) {
    if (st > r || en < l) return k;
    if (st <= l && en >= r) return k1;
    int ret = ++idcnt;
    int mid = l + r >> 1;
    ls[ret] = move(l, mid, ls[k], ls[k1], st, en);
    rs[ret] = move(mid + 1, r, rs[k], rs[k1], st, en);
    update(ret);
    return ret;
  }
  int add(int rt, int w) {
    int pos = find(0, 100040, rt, w);
    int tmp = isrt(0, 100040, rt, pos);
    if (pos == w) return tmp;
    tmp = move(0, 100040, tmp, root[0], w, pos - 1);
    return tmp;
  }
  bool sm(int k1, int k2) {
    return tsum[k1] == tsum[k2] && ths[k1] == ths[k2] && ths1[k1] == ths1[k2];
  }
  bool cmp(int l, int r, int k1, int k2) {
    if (l == r) return tsum[k1] <= tsum[k2];
    int mid = l + r >> 1;
    if (sm(rs[k1], rs[k2])) return cmp(l, mid, ls[k1], ls[k2]);
    return cmp(mid + 1, r, rs[k1], rs[k2]);
  }
} seg;
struct heap {
  int pu[400005], prt[400005];
  int ch[400005][2], h[400005];
  int idcnt, root, sz;
  int merge(int x, int y) {
    if (!x || !y) return x + y;
    if (seg.cmp(0, 100040, prt[y], prt[x])) swap(x, y);
    ch[x][1] = merge(ch[x][1], y);
    if (h[ch[x][1]] > h[ch[x][0]]) swap(ch[x][0], ch[x][1]);
    h[x] = h[ch[x][0]] + 1;
    return x;
  }
  void push(int u, int rt) {
    sz++;
    pu[++idcnt] = u, prt[idcnt] = rt;
    root = merge(idcnt, root);
  }
  void pop() { sz--, root = merge(ch[root][0], ch[root][1]); }
  int top() { return pu[root]; }
  bool empty() { return sz == 0; }
} q;
bool vis[200005];
int pv[200005];
int st[200005], top;
void Dijkstra() {
  int tmp = seg.build(0, 100040, 1);
  for (int i = 1; i <= n; ++i) root[i] = tmp;
  root[0] = root[s] = seg.build(0, 100040, 0);
  q.push(s, root[s]);
  while (!q.empty()) {
    while (!q.empty() && vis[q.top()]) q.pop();
    if (q.empty()) break;
    int u = q.top();
    vis[u] = 1;
    q.pop();
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i];
      if (vis[v]) continue;
      int trt = seg.add(root[u], w[i]);
      if (seg.cmp(0, 100040, root[v], trt)) continue;
      root[v] = trt, pv[v] = u;
      q.push(v, root[v]);
    }
  }
  if (root[t] == tmp) {
    puts("-1");
  } else {
    printf("%d\n", (int)seg.ths[root[t]]);
    for (int u = t; u != s; u = pv[u]) {
      st[++top] = u;
    }
    st[++top] = s;
    printf("%d\n", top);
    for (int i = top; i >= 1; --i) {
      printf("%d ", st[i]);
    }
    puts("");
  }
  return;
}
int main() {
  n = read(), m = read();
  base[0] = 1, base1[0] = 1;
  for (int i = 1; i <= 100040; ++i)
    base[i] = base[i - 1] * 2 % 1000000007, base1[i] = base1[i - 1] * 17;
  for (int i = 1; i <= m; ++i) {
    int u = read(), v = read(), x = read();
    add(u, v, x), add(v, u, x);
  }
  s = read(), t = read();
  Dijkstra();
  return 0;
}
int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (!isdigit(c)) f = (c == '-') ? -1 : f, c = getchar();
  while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
  return x * f;
}
