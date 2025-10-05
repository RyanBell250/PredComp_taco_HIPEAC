#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector")
using namespace std;
template <typename _Tp>
inline void IN(_Tp& dig) {
  char c;
  bool flag = 0;
  dig = 0;
  while (c = getchar(), !isdigit(c))
    if (c == '-') flag = 1;
  while (isdigit(c)) dig = dig * 10 + c - '0', c = getchar();
  if (flag) dig = -dig;
}
int n, m;
struct LCT {
  struct N {
    int f, s[2], dx, mx, dn;
    bool tag, rev;
    N() { dx = mx = INT_MIN, dn = INT_MAX; }
  } e[(200005) << 1];
  int root;
  stack<int> st;
  bool isroot(int a) { return e[e[a].f].s[0] != a && e[e[a].f].s[1] != a; }
  int pos(int a) { return e[e[a].f].s[1] == a; }
  void pup(int a) {
    int &l = e[a].s[0], &r = e[a].s[1];
    e[a].mx = max(e[a].dx, max(e[l].mx, e[r].mx));
  }
  void pdown(int a) {
    int &l = e[a].s[0], &r = e[a].s[1];
    if (e[a].tag) {
      e[l].dn = e[r].dn = e[a].dn;
      e[l].tag = e[r].tag = 1, e[a].tag = 0;
    }
    if (e[a].rev) {
      e[l].rev ^= 1, e[r].rev ^= 1, e[a].rev = 0;
      swap(e[l].s[0], e[l].s[1]), swap(e[r].s[0], e[r].s[1]);
    }
  }
  void rot(int a) {
    int f = e[a].f, g = e[f].f, p = pos(a), q = pos(f);
    if (!isroot(f)) e[g].s[q] = a;
    e[a].f = g, e[f].s[p] = e[a].s[!p], e[a].s[!p] = f, e[f].f = a;
    if (e[f].s[p]) e[e[f].s[p]].f = f;
    pup(f), pup(a);
  }
  void splay(int a) {
    st.push(a);
    for (int i = a; !isroot(i); i = e[i].f) st.push(e[i].f);
    while (!st.empty()) pdown(st.top()), st.pop();
    for (; !isroot(a); rot(a))
      if (!isroot(e[a].f)) {
        if (pos(a) ^ pos(e[a].f))
          rot(a);
        else
          rot(e[a].f);
      }
  }
  void acc(int a) {
    for (int i = 0; a; i = a, a = e[a].f) splay(a), e[a].s[1] = i, pup(a);
  }
  void evert(int a) {
    acc(a), splay(a);
    e[a].rev ^= 1, swap(e[a].s[0], e[a].s[1]);
  }
  void link(int a, int b) { evert(b), e[b].f = a; }
} t;
struct Edge {
  int u, v, w, i;
  bool f;
  bool operator<(const Edge oth) const { return w < oth.w; }
} E[(200005)];
int fa[(200005)], ans[(200005)];
int findf(int a) { return fa[a] == a ? a : fa[a] = findf(fa[a]); }
int main(int argc, char const* argv[]) {
  IN(n), IN(m);
  for (int i = 1; i <= n; i += 1) fa[i] = i;
  for (int i = 1; i <= m; i += 1)
    IN(E[i].u), IN(E[i].v), IN(E[i].w), E[i].i = i;
  sort(E + 1, E + 1 + m);
  for (int i = 1; i <= m; i += 1)
    if (findf(E[i].u) != findf(E[i].v)) {
      fa[findf(E[i].u)] = findf(E[i].v), E[i].f = 1;
      t.e[n + i].dx = t.e[n + i].mx = E[i].w;
      t.link(E[i].u, n + i), t.link(E[i].v, n + i);
    }
  for (int i = m; i >= 1; i -= 1)
    if (!E[i].f) {
      t.evert(E[i].u), t.acc(E[i].v), t.splay(E[i].u);
      t.e[E[i].u].dn = E[i].w, t.e[E[i].u].tag = 1;
    }
  for (int i = 1; i <= m; i += 1)
    if (E[i].f)
      t.splay(n + i), ans[E[i].i] = t.e[n + i].dn - 1;
    else {
      t.evert(E[i].u), t.acc(E[i].v), t.splay(E[i].u);
      ans[E[i].i] = t.e[E[i].u].mx - 1;
    }
  for (int i = 1; i <= m; i += 1)
    if (ans[i] > 2e9)
      printf("-1 ");
    else
      printf("%d ", ans[i]);
  putchar(10);
  return 0;
}
