#include <bits/stdc++.h>
using namespace std;
const int N = 200005, mod = 1000000000;
struct line {
  int left, right, mid;
  int a, b, lazy;
} seg[N * 4];
int f[N], fsum[N], mat[N][2][2], val[N], stk[N], top;
int mul(int a, int b) {
  if (a < 0) a += mod;
  if (b < 0) b += mod;
  long long ret = (long long)a * b;
  if (ret >= mod)
    return ret % mod;
  else
    return ret;
}
int add(int a, int b) {
  if (a < 0) a += mod;
  if (b < 0) b += mod;
  int ret = a + b;
  if (ret >= mod)
    return ret % mod;
  else
    return ret;
}
void init() {
  memset(mat, 0, sizeof(mat));
  mat[1][0][0] = mat[1][1][0] = mat[1][0][1] = 1;
  mat[1][1][1] = 0;
  for (int p = 2; p < N; p++) {
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          mat[p][i][j] = add(mat[p][i][j], mul(mat[p - 1][i][k], mat[1][k][j]));
        }
      }
    }
  }
  f[0] = 1;
  f[1] = 1;
  for (int i = 2; i < N; i++) {
    f[i] = add(f[i - 1], f[i - 2]);
  }
  fsum[0] = 1;
  for (int i = 1; i < N; i++) {
    fsum[i] = add(f[i], fsum[i - 1]);
  }
}
int fastmod(int a, int b, int c) {
  if (c == 0)
    return a;
  else if (c == 1)
    return b;
  else
    return add(mul(mat[c - 1][0][0], b), mul(mat[c - 1][0][1], a));
}
void pushdown(int now) {
  if (seg[now].lazy == 0) return;
  if (seg[now].left == seg[now].right) {
    seg[now].a = add(seg[now].a, seg[now].lazy);
    seg[now].b = add(seg[now].b, seg[now].lazy);
    seg[now].lazy = 0;
    return;
  }
  int si = seg[now].right - seg[now].left + 1, lazy = seg[now].lazy;
  seg[now].lazy = 0;
  seg[now].a = add(seg[now].a, mul(fsum[si - 1], lazy));
  seg[now].b = add(seg[now].b, mul(fsum[si] - fsum[0], lazy));
  int lc = now << 1, rc = lc | 1;
  seg[lc].lazy = add(seg[lc].lazy, lazy);
  seg[rc].lazy = add(seg[rc].lazy, lazy);
}
void update(int now) {
  int lc = now << 1, rc = lc | 1, ls = seg[now].mid - seg[now].left + 1;
  if (seg[now].left == seg[now].right) {
    return;
  }
  pushdown(lc);
  pushdown(rc);
  seg[now].a = add(seg[lc].a, fastmod(seg[rc].a, seg[rc].b, ls));
  seg[now].b = add(seg[lc].b, fastmod(seg[rc].a, seg[rc].b, ls + 1));
}
void build(int now, int left, int right) {
  seg[now].left = left;
  seg[now].right = right;
  seg[now].lazy = 0;
  int mid = seg[now].mid = (left + right) >> 1, lc = now << 1, rc = lc | 1,
      ls = mid - left + 1;
  if (left == right) {
    seg[now].a = val[left];
    seg[now].b = val[left];
    return;
  }
  build(lc, left, mid);
  build(rc, mid + 1, right);
  update(now);
}
void change(int now, int pos, int v) {
  int left = seg[now].left;
  int right = seg[now].right;
  int mid = seg[now].mid;
  if (left == pos && right == pos) {
    seg[now].a = v;
    seg[now].b = v;
    seg[now].lazy = 0;
    return;
  }
  pushdown(now);
  if (pos <= mid) {
    change(now << 1, pos, v);
  } else {
    change((now << 1) | 1, pos, v);
  }
  update(now);
}
void add(int now, int le, int ri, int v) {
  int left = seg[now].left;
  int right = seg[now].right;
  int mid = seg[now].mid;
  if (left == le && right == ri) {
    seg[now].lazy = add(seg[now].lazy, v);
    return;
  }
  pushdown(now);
  if (ri <= mid) {
    add(now << 1, le, ri, v);
  } else if (le > mid) {
    add((now << 1) | 1, le, ri, v);
  } else {
    add(now << 1, le, mid, v);
    add((now << 1) | 1, mid + 1, ri, v);
  }
  update(now);
}
void getsum(int now, int le, int ri) {
  int left = seg[now].left;
  int right = seg[now].right;
  int mid = seg[now].mid;
  pushdown(now);
  update(now);
  if (left == le && right == ri) {
    stk[top++] = now;
    return;
  }
  if (ri <= mid) {
    getsum(now << 1, le, ri);
  } else if (le > mid) {
    getsum((now << 1) | 1, le, ri);
  } else {
    getsum(now << 1, le, mid);
    getsum((now << 1) | 1, mid + 1, ri);
  }
}
int solve() {
  int ans = 0, si = 0;
  for (int tp, i = 0; i < top; i++) {
    tp = stk[i];
    ans = add(ans, fastmod(seg[tp].a, seg[tp].b, si));
    si += seg[stk[i]].right - seg[stk[i]].left + 1;
  }
  return ans;
}
int main() {
  init();
  int n, m;
  while (scanf("%d%d", &n, &m) != EOF) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", &val[i]);
    }
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
      int op, a, b, c, d;
      scanf("%d", &op);
      switch (op) {
        case 1:
          scanf("%d%d", &a, &b);
          change(1, a, b);
          break;
        case 2:
          scanf("%d%d", &a, &b);
          top = 0;
          getsum(1, a, b);
          printf("%d\n", solve());
          break;
        case 3:
          scanf("%d%d%d", &a, &b, &c);
          add(1, a, b, c);
          break;
      }
    }
  }
  return 0;
}
