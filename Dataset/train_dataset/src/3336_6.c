#include <bits/stdc++.h>
using namespace std;
const int N = 10005;
int l[N], r[N], x[N];
int n;
struct node {
  int l, r;
  vector<int> v;
  bitset<N> b;
} T[4 * N];
void build(int id, int l, int r) {
  T[id].l = l, T[id].r = r, T[id].b.set(0);
  if (l == r) return;
  int mid = (l + r) / 2;
  build(2 * id, l, mid);
  build(2 * id + 1, mid + 1, r);
}
void update(int id, int l, int r, int k) {
  if (T[id].l >= l && T[id].r <= r) {
    T[id].v.push_back(k);
    return;
  }
  int mid = (T[id].l + T[id].r) / 2;
  if (l <= mid) update(2 * id, l, r, k);
  if (r > mid) update(2 * id + 1, l, r, k);
}
void getans(int id) {
  if (T[id].l == T[id].r) {
    for (int i = 0; i < T[id].v.size(); i++) {
      int t = T[id].v[i];
      T[id].b |= (T[id].b << x[t]);
    }
    return;
  }
  getans(2 * id);
  getans(2 * id + 1);
  T[id].b |= T[2 * id].b;
  T[id].b |= T[2 * id + 1].b;
  for (int i = 0; i < T[id].v.size(); i++) {
    int t = T[id].v[i];
    T[id].b |= (T[id].b << x[t]);
  }
}
vector<int> ans;
int main() {
  int q;
  scanf("%d%d", &n, &q);
  build(1, 1, n);
  for (int i = 1; i <= q; i++) {
    scanf("%d%d%d", &l[i], &r[i], &x[i]);
    update(1, l[i], r[i], i);
  }
  getans(1);
  for (int i = 1; i <= n; i++) {
    if (T[1].b.test(i)) ans.push_back(i);
  }
  printf("%d\n", ans.size());
  for (int i = 0; i < ans.size(); i++) printf("%d ", ans[i]);
  return 0;
}
