#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
const int p = 998244353;
int get() {
  char c = getchar();
  while (c < '0' || '9' < c) c = getchar();
  return c - '0';
}
int read() {
  int s = 0;
  char c = getchar(), lc = '+';
  while (c < '0' || '9' < c) lc = c, c = getchar();
  while ('0' <= c && c <= '9') s = s * 10 + c - '0', c = getchar();
  return lc == '-' ? -s : s;
}
void write(int x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x < 10)
    putchar(x + '0');
  else {
    write(x / 10);
    putchar(x % 10 + '0');
  }
}
void print(int x = -1, char c = '\n') {
  write(x);
  putchar(c);
}
inline void add(int &x, int y) {
  x += y;
  if (x >= p) x -= p;
}
struct node {
  int a[2][2];
  node() { memset(a, 0, sizeof(a)); }
  node operator*(const node &x) const {
    node ret;
    for (int i = 0; i < 2; i++)
      for (int k = 0; k < 2; k++)
        for (int j = 0; j < 2; j++)
          add(ret.a[i][j], 1LL * a[i][k] * x.a[k][j] % p);
    return ret;
  }
} t[N * 4], ed;
int a[N];
node make_node(int x) {
  node ret;
  ret.a[0][0] = a[x] + 1;
  ret.a[0][1] = (a[x - 1] == 1) * (9 - a[x]);
  ret.a[1][0] = 1;
  ret.a[1][1] = 0;
  return ret;
}
void build(int w, int l, int r) {
  if (l == r) return void(t[w] = make_node(l));
  build((w * 2), l, ((l + r) / 2));
  build((w * 2 + 1), ((l + r) / 2) + 1, r);
  t[w] = t[(w * 2 + 1)] * t[(w * 2)];
}
void change(int w, int l, int r, int x, int y) {
  if (l == r) return a[x] = y, t[w] = make_node(x), void();
  if (x <= ((l + r) / 2))
    change((w * 2), l, ((l + r) / 2), x, y);
  else
    change((w * 2 + 1), ((l + r) / 2) + 1, r, x, y);
  t[w] = t[(w * 2 + 1)] * t[(w * 2)];
}
void out(int w, int l, int r) {
  print(l, ' ');
  print(r, ':');
  puts("");
  print(t[w].a[0][0], ' ');
  print(t[w].a[0][1]);
  print(t[w].a[1][0], ' ');
  print(t[w].a[1][1]);
  if (l == r) return;
  out((w * 2), l, ((l + r) / 2));
  out((w * 2 + 1), ((l + r) / 2) + 1, r);
}
signed main(signed Recall, char *_902_[]) {
  ed.a[0][0] = ed.a[1][0] = 1;
  (void)Recall, (void)_902_;
  int n = read(), m = read();
  for (int i = 1; i <= n; i++) a[i] = get();
  build(1, 1, n);
  for (int i = 1; i <= m; i++) {
    int x = read(), y = read();
    change(1, 1, n, x, y);
    if (x < n) change(1, 1, n, x + 1, a[x + 1]);
    print((t[1] * ed).a[0][0]);
  }
  return 0;
}
