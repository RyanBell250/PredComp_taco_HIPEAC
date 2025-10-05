#include <bits/stdc++.h>
const int MAXN = 200000;
const int MAXL = 30;
using namespace std;
inline void enableFileIO() {
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
}
inline int read() {
  int x = 0, w = 1;
  char c = ' ';
  while (c < '0' || c > '9') {
    c = getchar();
    if (c == '-') w = -1;
  }
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c ^ 48);
    c = getchar();
  }
  return x * w;
}
struct LinearBasis {
  int b[MAXL + 5], v;
  void init() {
    memset(b, 0, sizeof(b));
    v = 0;
  }
  void insert(int x) {
    for (int i = MAXL; i >= 0; --i) {
      if (x & (1 << i)) {
        if (!b[i]) {
          b[i] = x;
          return;
        } else {
          x ^= b[i];
        }
      }
    }
  }
  int count() {
    int ret = 1;
    for (int i = 0; i <= MAXL; ++i) {
      if (b[i]) ret <<= 1;
    }
    return ret;
  }
} ans;
LinearBasis merge(const LinearBasis &A, const LinearBasis &B) {
  LinearBasis ret;
  ret.init();
  for (int i = 0; i <= MAXL; ++i) {
    ret.insert(A.b[i]);
    ret.insert(B.b[i]);
  }
  ret.insert(A.v ^ B.v);
  ret.v = B.v;
  return ret;
}
int a[MAXN + 5];
struct SegmentTree {
  struct Node {
    int delta;
    LinearBasis b;
  } s[MAXN * 4 + 5];
  SegmentTree() {}
  void upd(int p) { s[p].b = merge(s[p << 1].b, s[p << 1 | 1].b); }
  void pd(int p) {
    if (s[p].delta) {
      s[p << 1].delta ^= s[p].delta;
      s[p << 1 | 1].delta ^= s[p].delta;
      s[p << 1].b.v ^= s[p].delta;
      s[p << 1 | 1].b.v ^= s[p].delta;
      s[p].delta = 0;
    }
  }
  void build(int p, int l, int r) {
    if (l == r) {
      s[p].b.v = a[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    upd(p);
  }
  void update(int p, int l, int r, int x, int y, int v) {
    if (x <= l && y >= r) {
      s[p].delta ^= v;
      s[p].b.v ^= v;
      return;
    }
    pd(p);
    int mid = (l + r) >> 1;
    if (x <= mid) update(p << 1, l, mid, x, y, v);
    if (y > mid) update(p << 1 | 1, mid + 1, r, x, y, v);
    upd(p);
  }
  void query(int p, int l, int r, int x, int y) {
    if (x <= l && y >= r) {
      ans = merge(ans, s[p].b);
      return;
    }
    pd(p);
    int mid = (l + r) >> 1;
    if (x <= mid) query(p << 1, l, mid, x, y);
    if (y > mid) query(p << 1 | 1, mid + 1, r, x, y);
  }
} S;
int n, m;
void init() {
  n = read();
  m = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
}
int main() {
  init();
  S.build(1, 1, n);
  while (m--) {
    int opt = read(), l = read(), r = read();
    switch (opt) {
      case 1: {
        int v = read();
        S.update(1, 1, n, l, r, v);
        break;
      }
      case 2: {
        ans.init();
        S.query(1, 1, n, l, r);
        printf("%d\n", ans.count());
        break;
      }
    }
  }
  return 0;
}
