#include <bits/stdc++.h>
using namespace std;
int l[222222], r[222222];
int ll[222222], rr[222222];
int good[222222];
int tree[222222 * 4];
void build(int v, int l, int r) {
  if (l == r) {
    tree[v] = good[l];
  } else {
    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m + 1, r);
    tree[v] = tree[v * 2] + tree[v * 2 + 1];
  }
}
int sum(int v, int l, int r, int tl, int tr) {
  if (tl > tr) {
    return 0;
  }
  if (l == tl && r == tr) {
    return tree[v];
  }
  int m = (l + r) / 2;
  return sum(v * 2, l, m, tl, min(tr, m)) +
         sum(v * 2 + 1, m + 1, r, max(tl, m + 1), tr);
}
int main() {
  int n, k, q;
  scanf("%i%i%i", &n, &k, &q);
  memset(l, 0, sizeof(l));
  memset(r, 0, sizeof(r));
  for (int i = 0; i < n; i++) {
    int lx, rx;
    scanf("%i%i", &lx, &rx);
    l[lx]++;
    r[rx]++;
  }
  for (int i = 0; i < q; i++) {
    scanf("%i%i", &ll[i], &rr[i]);
  }
  memset(good, 0, sizeof(good));
  int cnt = 0;
  for (int i = 0; i < 222222; i++) {
    cnt += l[i];
    if (cnt >= k) {
      good[i] = 1;
    }
    cnt -= r[i];
  }
  build(1, 0, 222222);
  for (int i = 0; i < q; i++) {
    printf("%i\n", sum(1, 0, 222222, ll[i], rr[i]));
  }
}
