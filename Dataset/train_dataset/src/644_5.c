#include <bits/stdc++.h>
using namespace std;
void SR(int &x) { scanf("%d", &x); }
void SR(long long &x) { scanf("%lld", &x); }
void SR(double &x) { scanf("%lf", &x); }
void SR(char *s) { scanf("%s", s); }
void RI() {}
template <typename I, typename... T>
void RI(I &x, T &...tail) {
  SR(x);
  RI(tail...);
}
void SP(const int x) { printf("%d", x); }
void SP(const long long x) { printf("%lld", x); }
void SP(const double x) { printf("%.16lf", x); }
void SP(const char *s) { printf(s); }
void PS() { puts(""); }
template <typename I, typename... T>
void PS(I &x, T &...tail) {
  putchar(' ');
  SP(x);
  PS(tail...);
}
void PL() { puts(""); }
template <typename I, typename... T>
void PL(const I x, const T... tail) {
  SP(x);
  PS(tail...);
}
const int TN = 8.06e6;
struct Node {
  static Node mem[TN], *pmem;
  Node() : hi(0), l(0), r(0) {}
  Node(const Node &o) : hi(o.hi), l(o.l), r(o.r) {}
  unsigned long long hi : 18, l : 23, r : 23;
} Node::mem[TN], *Node::pmem = Node::mem;
struct Seg {
  Node *dat = Node::mem;
  Node *&siz = Node::pmem;
  inline int hi(int o, int low, int high) {
    if (low == high) return o;
    return dat[o].hi;
  }
  inline int l(int o) { return dat[o].l; }
  inline int r(int o) { return dat[o].r; }
  int getNode(int x) {
    siz++;
    *siz = Node(dat[x]);
    return siz - dat;
  }
  int tag(int x, int low, int high) {
    int mid = (low + high) / 2;
    return hi(x, low, high) - max(hi(l(x), low, mid), hi(r(x), mid + 1, high));
  }
  void pull(int x, int low, int high, int d) {
    int mid = (low + high) / 2;
    dat[x].hi = max(hi(l(x), low, mid), hi(r(x), mid + 1, high)) + d;
  }
  int add(int x, int low, int high, int a, int b, int k) {
    if (low == high) {
      return x + k;
    }
    int t = getNode(x);
    if (low == a && b == high) {
      dat[t].hi += k;
      return t;
    }
    int mid = (low + high) / 2;
    int d = tag(t, low, high);
    if (b <= mid)
      dat[t].l = add(l(t), low, mid, a, b, k);
    else if (mid + 1 <= a)
      dat[t].r = add(r(t), mid + 1, high, a, b, k);
    else
      dat[t].l = add(l(t), low, mid, a, mid, k),
      dat[t].r = add(r(t), mid + 1, high, mid + 1, b, k);
    pull(t, low, high, d);
    return t;
  }
  int ask(int x, int low, int high, int a, int b) {
    if (low == a && b == high) return hi(x, low, high);
    int t = x;
    int mid = (low + high) / 2;
    int ret = 0;
    if (b <= mid)
      ret = ask(l(t), low, mid, a, b);
    else if (mid + 1 <= a)
      ret = ask(r(t), mid + 1, high, a, b);
    else
      ret = max(ask(l(t), low, mid, a, mid),
                ask(r(t), mid + 1, high, mid + 1, b));
    return ret + tag(t, low, high);
  }
} seg;
const int maxn = 2e5 + 5;
int n, m, a[maxn];
void read() {
  RI(n, m);
  for (int i = (1); i <= int(n); i++) RI(a[i]);
}
int rnk[maxn];
int *t = a;
bool cmp(int x, int y) { return a[x] < a[y]; }
void build() {
  memcpy(rnk, a + 1, sizeof(int) * n);
  sort(rnk, rnk + n);
  for (int i = (1); i <= int(n); i++)
    a[i] = lower_bound(rnk, rnk + n, a[i]) - rnk;
  static int tmp[maxn];
  for (int i = 0; i < int(n); i++) tmp[i] = i + 1;
  sort(tmp, tmp + n, cmp);
  t[n] = 0;
  for (int i = n - 1; i >= 0; i--)
    t[i] = seg.add(t[i + 1], 1, n - m + 1, max(tmp[i] - m + 1, 1),
                   min(tmp[i], n - m + 1), 1);
}
void sol() {
  int s;
  RI(s);
  int ans = 0;
  while (s--) {
    int l, r, x;
    RI(l, r, x);
    int q = x ^ ans;
    int v = lower_bound(rnk, rnk + n, q) - rnk;
    ans = m - seg.ask(t[v], 1, n - m + 1, l, r);
    PL(ans);
  }
}
int main() {
  read();
  build();
  sol();
  return 0;
}
