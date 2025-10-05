#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
int n, m, A[400010], len[400010], sign[400010], Rt[400010], q;
int pos[400010][2], DEL[400010 << 2], TAG[400010 << 2];
int flower[400010 << 2], c[400010 << 2][2], tot, cnt;
char comd[10];
vector<int> V[400010];
struct node {
  int len, sum;
};
node tree[400010 << 2][2];
inline bool operator<(const node a, const node b) {
  return a.sum == b.sum ? a.len < b.len : a.sum < b.sum;
}
inline bool operator>(const node a, const node b) {
  return a.sum == b.sum ? a.len > b.len : a.sum > b.sum;
}
inline node operator+(const node a, const node b) {
  return (node){a.len + b.len, a.sum + b.sum};
}
inline void deal_(int rt) {
  if (!rt) return;
  flower[rt] = 0;
  TAG[rt] = 1;
}
inline void deal(int rt) {
  tree[rt][0].sum = 0;
  DEL[rt] = 1;
  if (tree[rt][0].len != 1 && sign[rt]) deal_(Rt[sign[rt]]);
  if (tree[rt][1] < tree[rt][0]) swap(tree[rt][1], tree[rt][0]);
}
inline void pushdown_(int rt) {
  if (TAG[rt]) {
    deal_(c[rt][0]);
    deal_(c[rt][1]);
    TAG[rt] = 0;
  }
}
inline void pushdown(int rt) {
  if (DEL[rt]) {
    deal(rt << 1);
    deal(rt << 1 | 1);
    DEL[rt] = 0;
  }
}
inline void pushup_(int rt) {
  flower[rt] = flower[c[rt][0]] + flower[c[rt][1]];
}
inline void pushup(int rt) {
  tree[rt][0] = tree[rt << 1][0] + tree[rt << 1 | 1][0];
  tree[rt][1] = tree[rt << 1][1] + tree[rt << 1 | 1][1];
}
inline void built(int l, int r, int rt) {
  if (l == r) {
    tree[rt][0].len = 1;
    sign[rt] = l;
    tree[rt][1].len = len[l] - 1;
    tree[rt][0].sum = tree[rt][1].sum = 0;
    return;
  }
  int mid = (l + r) >> 1;
  built(l, mid, rt << 1);
  built(mid + 1, r, rt << 1 | 1);
  pushup(rt);
}
inline void updata_(int x, int y, int l, int r, int &rt) {
  if (!rt) rt = ++tot;
  if (l == r) {
    flower[rt] += y;
    return;
  }
  int mid = (l + r) >> 1;
  pushdown_(rt);
  if (mid >= x) updata_(x, y, l, mid, c[rt][0]);
  if (mid < x) updata_(x, y, mid + 1, r, c[rt][1]);
  pushup_(rt);
}
inline void updata(int x, int z, int y, int l, int r, int rt) {
  if (l == r) {
    if (z == tree[rt][0].len)
      tree[rt][0].sum += y;
    else
      tree[rt][1].sum += y;
    if (tree[rt][0] > tree[rt][1]) swap(tree[rt][1], tree[rt][0]);
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(rt);
  if (mid >= x) updata(x, z, y, l, mid, rt << 1);
  if (mid < x) updata(x, z, y, mid + 1, r, rt << 1 | 1);
  pushup(rt);
}
inline node query_(int L, int R, int l, int r, int &rt) {
  if (L > R) return (node){0, 0};
  if (!rt) rt = ++tot;
  if (L <= l && r <= R) return (node){r - l + 1, flower[rt]};
  int mid = (l + r) >> 1;
  pushdown_(rt);
  if (mid < L) return query_(L, R, mid + 1, r, c[rt][1]);
  if (mid >= R) return query_(L, R, l, mid, c[rt][0]);
  return query_(L, R, l, mid, c[rt][0]) + query_(L, R, mid + 1, r, c[rt][1]);
}
inline node query(int L, int R, int l, int r, int rt) {
  if (L > R) return (node){0, 0};
  if (L <= l && r <= R) return tree[rt][0];
  int mid = (l + r) >> 1;
  pushdown(rt);
  if (mid < L) return query(L, R, mid + 1, r, rt << 1 | 1);
  if (mid >= R) return query(L, R, l, mid, rt << 1);
  return query(L, R, l, mid, rt << 1) + query(L, R, mid + 1, r, rt << 1 | 1);
}
inline void delet(int L, int R, int l, int r, int rt) {
  if (L > R) return;
  if (L <= l && r <= R) {
    deal(rt);
    return;
  }
  int mid = (l + r) >> 1;
  pushdown(rt);
  if (mid >= L) delet(L, R, l, mid, rt << 1);
  if (mid < R) delet(L, R, mid + 1, r, rt << 1 | 1);
  pushup(rt);
}
inline void delet_(int L, int R, int l, int r, int rt, int tp) {
  if (L > R) return;
  if (!rt) return;
  if (L <= l && r <= R) {
    updata(tp, len[tp] - 1, -flower[rt], 1, n, 1);
    deal_(rt);
    return;
  }
  int mid = (l + r) >> 1;
  pushdown_(rt);
  if (mid >= L) delet_(L, R, l, mid, c[rt][0], tp);
  if (mid < R) delet_(L, R, mid + 1, r, c[rt][1], tp);
  pushup_(rt);
}
int p1, p2, p3, rev, u, v, px, py, bx, by;
node Ans;
inline int step3(int nw1, int p, int pp) {
  if (pp == 0) {
    if (p == 0) return V[pos[nw1][0]][1];
    if (p == 1) return V[pos[nw1][0]][len[pos[nw1][0]] - 1];
  }
  if (pp == 1) {
    int pre = pos[nw1][0] == 1 ? n : pos[nw1][0] - 1;
    if (p == 0) return V[pre][0];
    if (p == 1) return V[pre][len[pre] - 2];
  }
  return 0;
}
inline int step2(int nw1, int p, int pp) {
  if (p == 0) {
    int pre = pos[nw1][0];
    node x = query(pre, pre, 1, n, 1);
    if (x.len == 1)
      nw1 = V[pre][len[pre] - 1];
    else
      nw1 = V[pre][1];
  }
  if (p == 1) {
    int pre = pos[nw1][0] == 1 ? n : pos[nw1][0] - 1;
    node x = query(pre, pre, 1, n, 1);
    if (x.len == 1)
      nw1 = V[pre][0];
    else
      nw1 = V[pre][len[pre] - 2];
  }
  return nw1;
}
inline int step1(int nw1, int p, int pp) {
  if (p == 0) {
    if (pos[nw1][1] == 1 && pp == 1) {
      int pre = pos[nw1][0] == 1 ? n : pos[nw1][0] - 1;
      node x = query(pre, pre, 1, n, 1);
      if (x.len == 1)
        nw1 = V[pre][0];
      else
        nw1 = V[pre][len[pre] - 2];
      return nw1;
    }
    if (pos[nw1][1] == 1 && pp == 0) {
      int pre = pos[nw1][0] == n ? 1 : pos[nw1][0] + 1;
      return A[pre];
    } else
      nw1 = V[pos[nw1][0]][pos[nw1][1] - 2];
  } else
    nw1 = V[pos[nw1][0]][pos[nw1][1]];
  return nw1;
}
inline void upgrade(node xx, int t1, int t2, int t3) {
  if (xx < Ans) {
    Ans = xx;
    p1 = t1;
    p2 = t2;
    p3 = t3;
    return;
  }
  if (xx > Ans) return;
  int nw1 = u, nw2 = u, s1 = p1, s2 = p2, s3 = p3;
  if (rev) s2 ^= 1, t2 ^= 1, swap(t1, t3), swap(s1, s3);
  if (t1 != s1) {
    nw1 = step1(nw1, s1, s2);
    nw2 = step1(nw2, t1, t2);
    if (nw1 > nw2) {
      Ans = xx;
      if (rev)
        p1 = t3, p3 = t1;
      else
        p1 = t1, p3 = t3;
      p2 = t2 ^ rev;
    }
    return;
  }
  nw1 = nw2 =
      t1 == 1 ? V[pos[nw1][0]][len[pos[nw1][0]] - 1] : V[pos[nw1][0]][0];
  if (t2 != s2) {
    nw1 = step2(nw1, s2, s1);
    nw2 = step2(nw2, t2, t1);
    if (nw1 > nw2) {
      Ans = xx;
      if (rev)
        p1 = t3, p3 = t1;
      else
        p1 = t1, p3 = t3;
      p2 = t2 ^ rev;
    }
    return;
  }
  nw1 = nw2 = (t2 == 0 ? V[pos[v][0]][0] : V[pos[v][0]][len[pos[v][0]] - 1]);
  nw1 = step3(nw1, s3, s2);
  nw2 = step3(nw2, t3, t2);
  if (nw1 > nw2) {
    Ans = xx;
    if (rev)
      p1 = t3, p3 = t1;
    else
      p1 = t1, p3 = t3;
    p2 = t2 ^ rev;
  }
  return;
}
inline int Ask(int x, int y) {
  ++cnt;
  u = x;
  v = y;
  rev = 0;
  if (pos[x][0] > pos[y][0]) swap(x, y), rev = 1;
  if (pos[x][0] == pos[y][0])
    if (pos[x][1] > pos[y][1]) swap(x, y), rev = 1;
  px = pos[x][1], py = pos[y][1];
  bx = pos[x][0], by = pos[y][0];
  if (x == y) return 0;
  node lx, rx, ly, ry, la, lb;
  la = query(bx, bx, 1, n, 1);
  lb = query(by, by, 1, n, 1);
  lx = query_(1, px - 1, 1, len[bx] - 1, Rt[bx]);
  rx = query_(px, len[bx], 1, len[bx] - 1, Rt[bx]);
  ly = query_(1, py - 1, 1, len[by] - 1, Rt[by]);
  ry = query_(py, len[by], 1, len[by] - 1, Rt[by]);
  Ans = lx + query(bx, by - 1, 1, n, 1) + ly;
  p1 = 0;
  p2 = 0;
  p3 = 0;
  upgrade(lx + query(1, bx - 1, 1, n, 1) + query(by, n, 1, n, 1) + ly, 0, 1, 0);
  upgrade(lx + query(bx, by, 1, n, 1) + ry, 0, 0, 1);
  upgrade(lx + query(1, bx - 1, 1, n, 1) + query(by + 1, n, 1, n, 1) + ry, 0, 1,
          1);
  upgrade(rx + query(bx + 1, by - 1, 1, n, 1) + ly, 1, 0, 0);
  upgrade(rx + query(1, bx, 1, n, 1) + query(by, n, 1, n, 1) + ly, 1, 1, 0);
  upgrade(rx + query(bx + 1, by, 1, n, 1) + ry, 1, 0, 1);
  upgrade(rx + query(1, bx, 1, n, 1) + query(by + 1, n, 1, n, 1) + ry, 1, 1, 1);
  if (bx == by) upgrade(query_(px, py - 1, 1, len[bx] - 1, Rt[bx]), 1, 2, 2);
  if (p1 == 0 && p2 == 0 && p3 == 0)
    delet_(1, px - 1, 1, len[bx] - 1, Rt[bx], bx), delet(bx, by - 1, 1, n, 1),
        delet_(1, py - 1, 1, len[by] - 1, Rt[by], by);
  if (p1 == 0 && p2 == 1 && p3 == 0)
    delet_(1, px - 1, 1, len[bx] - 1, Rt[bx], bx), delet(1, bx - 1, 1, n, 1),
        delet(by, n, 1, n, 1), delet_(1, py - 1, 1, len[by] - 1, Rt[by], by);
  if (p1 == 0 && p2 == 0 && p3 == 1)
    delet_(1, px - 1, 1, len[bx] - 1, Rt[bx], bx), delet(bx, by, 1, n, 1),
        delet_(py, len[by], 1, len[by] - 1, Rt[by], by);
  if (p1 == 0 && p2 == 1 && p3 == 1)
    delet_(1, px - 1, 1, len[bx] - 1, Rt[bx], bx), delet(1, bx - 1, 1, n, 1),
        delet(by + 1, n, 1, n, 1),
        delet_(py, len[by], 1, len[by] - 1, Rt[by], by);
  if (p1 == 1 && p2 == 0 && p3 == 0)
    delet_(px, len[bx], 1, len[bx] - 1, Rt[bx], bx),
        delet(bx + 1, by - 1, 1, n, 1),
        delet_(1, py - 1, 1, len[by] - 1, Rt[by], by);
  if (p1 == 1 && p2 == 1 && p3 == 0)
    delet_(px, len[bx], 1, len[bx] - 1, Rt[bx], bx), delet(1, bx, 1, n, 1),
        delet(by, n, 1, n, 1), delet_(1, py - 1, 1, len[by] - 1, Rt[by], by);
  if (p1 == 1 && p2 == 0 && p3 == 1)
    delet_(px, len[bx], 1, len[bx] - 1, Rt[bx], bx), delet(bx + 1, by, 1, n, 1),
        delet_(py, len[by], 1, len[by] - 1, Rt[by], by);
  if (p1 == 1 && p2 == 1 && p3 == 1)
    delet_(px, len[bx], 1, len[bx] - 1, Rt[bx], bx), delet(1, bx, 1, n, 1),
        delet(by + 1, n, 1, n, 1),
        delet_(py, len[by], 1, len[by] - 1, Rt[by], by);
  if (p1 == 1 && p2 == 2 && p3 == 2)
    delet_(px, py - 1, 1, len[bx] - 1, Rt[bx], bx);
  if (p1 == 2 && p2 == 2 && p3 == 1)
    delet_(px, py - 1, 1, len[bx] - 1, Rt[bx], bx);
  return Ans.sum;
}
int main() {
  m = read();
  n = read();
  for (int i = 1; i <= n; i++)
    A[i] = read(), pos[A[i]][0] = i, pos[A[i]][1] = 0;
  for (int i = 1; i <= n; i++) {
    len[i] = read();
    for (int j = 1; j <= len[i]; j++) {
      int k = read();
      V[i].push_back(k);
      if (j == len[i]) continue;
      pos[k][0] = i;
      pos[k][1] = j;
    }
  }
  built(1, n, 1);
  q = read();
  for (int i = 1; i <= q; i++) {
    scanf("%s", comd);
    int u = read(), v = read();
    if (comd[0] == '+') {
      if (pos[u][0] != pos[v][0]) {
        if (pos[u][0] > pos[v][0]) swap(u, v);
        if (pos[u][0] == 1 && pos[v][0] == n) swap(u, v);
        if (pos[u][1] == len[pos[u][0]] - 1) {
          updata(pos[u][0], len[pos[u][0]] - 1, 1, 1, n, 1);
          updata_(pos[u][1], 1, 1, len[pos[u][0]] - 1, Rt[pos[u][0]]);
          continue;
        }
        updata(pos[u][0], 1, 1, 1, n, 1);
      } else {
        if (pos[u][1] > pos[v][1]) swap(u, v);
        updata(pos[u][0], len[pos[u][0]] - 1, 1, 1, n, 1);
        updata_(pos[u][1], 1, 1, len[pos[u][0]] - 1, Rt[pos[u][0]]);
      }
    }
    if (comd[0] == '?') printf("%d\n", Ask(u, v));
  }
  return 0;
}
