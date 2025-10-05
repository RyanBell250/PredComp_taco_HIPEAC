#include <bits/stdc++.h>
using namespace std;
int c[6][32][32][32][32];
bool inside(int s, int e, int t) { return s <= t && t <= e; }
int back(int k, int l1, int r1, int l2, int r2) {
  l1 = (((1) > (l1)) ? (1) : (l1));
  r1 = ((((1 << k) - 1) < (r1)) ? ((1 << k) - 1) : (r1));
  l2 = (((1) > (l2)) ? (1) : (l2));
  r2 = ((((1 << k) - 1) < (r2)) ? ((1 << k) - 1) : (r2));
  if (l1 > r1 || l2 > r2) return 0;
  if (l1 <= l2 && r2 <= r1) return r2 - l2 + 1;
  if (l2 <= l1 && r1 <= r2) return r1 - l1 + 1;
  if (k <= 5) {
    if (c[k][l1][r1][l2][r2] != -1) return c[k][l1][r1][l2][r2];
  }
  int v = 0, mid = 1 << (k - 1);
  int l, r, re;
  if (inside(l1, r1, mid) && inside(l2, r2, mid)) {
    v = (((r1) < (r2)) ? (r1) : (r2)) - (((l1) > (l2)) ? (l1) : (l2)) + 1;
    re = back(k - 1, (((l1) < (l2)) ? (l1) : (l2)), mid - 1, 1,
              (((r1) > (r2)) ? (r1) : (r2)) - mid);
    if (v < re) v = re;
  } else if (inside(l1, r1, mid)) {
    if (mid < l2) {
      l2 -= mid;
      r2 -= mid;
    }
    re = back(k - 1, l1, mid - 1, l2, r2);
    if (v < re) v = re;
    re = back(k - 1, 1, r1 - mid, l2, r2);
    if (v < re) v = re;
  } else if (inside(l2, r2, mid)) {
    if (mid < l1) {
      l1 -= mid;
      r1 -= mid;
    }
    re = back(k - 1, l2, mid - 1, l1, r1);
    if (v < re) v = re;
    re = back(k - 1, 1, r2 - mid, l1, r1);
    if (v < re) v = re;
  } else {
    if (mid < l1) {
      l1 -= mid;
      r1 -= mid;
    }
    if (mid < l2) {
      l2 -= mid;
      r2 -= mid;
    }
    re = back(k - 1, l1, r1, l2, r2);
    if (v < re) v = re;
  }
  if (k <= 5)
    return c[k][l1][r1][l2][r2] = v;
  else
    return v;
}
int main() {
  int l1, r1, l2, r2;
  scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
  memset(c, -1, sizeof(c));
  printf("%d", back(30, l1, r1, l2, r2));
  return 0;
}
