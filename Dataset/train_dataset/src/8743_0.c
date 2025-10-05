#include <bits/stdc++.h>
using namespace std;
struct node {
  int p, x;
  node() { ; }
  node(int a, int b) { p = a, x = b; }
};
stack<node> s[100005];
int mx[100005 << 2], n, m, k;
struct QaQ {
  int l, r, f, h;
  bool operator<(const QaQ &a) const { return h < a.h; }
} a[100005];
int cmp(int a, int b) {
  if (s[a].empty()) return b;
  if (s[b].empty()) return a;
  return (s[a].top().p > s[b].top().p) ? a : b;
}
void PushUp(int rt) { mx[rt] = cmp(mx[rt << 1], mx[rt << 1 | 1]); }
void build(int l, int r, int rt) {
  if (l == r) {
    s[l].push(node(0, 1));
    mx[rt] = l;
    return;
  }
  int m = (l + r) >> 1;
  build(l, m, rt << 1);
  build(m + 1, r, rt << 1 | 1);
  PushUp(rt);
}
void insert(int x, node p, int l, int r, int rt) {
  if (l == r) {
    s[l].push(p);
    return;
  }
  int m = (l + r) >> 1;
  if (x <= m)
    insert(x, p, l, m, rt << 1);
  else
    insert(x, p, m + 1, r, rt << 1 | 1);
  PushUp(rt);
}
void del(int x, int l, int r, int rt) {
  if (l == r) {
    s[l].pop();
    return;
  }
  int m = (l + r) >> 1;
  if (x <= m)
    del(x, l, m, rt << 1);
  else
    del(x, m + 1, r, rt << 1 | 1);
  PushUp(rt);
}
int query(int L, int R, int l, int r, int rt) {
  if (L <= l && r <= R) return mx[rt];
  int m = (l + r) >> 1, ret = 0;
  if (L <= m) ret = query(L, R, l, m, rt << 1);
  if (m < R) ret = cmp(ret, query(L, R, m + 1, r, rt << 1 | 1));
  return ret;
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= k; i++)
    scanf("%d%d%d%d", &a[i].h, &a[i].l, &a[i].r, &a[i].f),
        a[i].h = n + 1 - a[i].h;
  build(1, m, 1);
  sort(a + 1, a + k + 1);
  for (int i = 1; i <= k; i++) {
    node p(a[i].h, 0);
    while (1) {
      int x = query(a[i].l, a[i].r, 1, m, 1);
      if (s[x].empty()) break;
      node tmp = s[x].top();
      if (tmp.p < a[i].h - a[i].f) break;
      p.x = (p.x + tmp.x) % 1000000007;
      del(x, 1, m, 1);
    }
    if (a[i].l == 1) {
      p.x = (p.x + p.x) % 1000000007;
      insert(a[i].r + 1, p, 1, m, 1);
    } else if (a[i].r == m) {
      p.x = (p.x + p.x) % 1000000007;
      insert(a[i].l - 1, p, 1, m, 1);
    } else {
      insert(a[i].l - 1, p, 1, m, 1);
      insert(a[i].r + 1, p, 1, m, 1);
    }
  }
  int ans = 0;
  for (int i = 1; i <= m; i++) {
    while (!s[i].empty()) ans = (ans + s[i].top().x) % 1000000007, s[i].pop();
  }
  printf("%d\n", ans);
}
