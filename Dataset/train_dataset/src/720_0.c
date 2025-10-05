#include <bits/stdc++.h>
using namespace std;
int a[500010], n, k, suf[500010];
int l_bad, r_bad;
int mi[500010 << 2], mi_pos[500010 << 2];
vector<int> v[500010];
void push_up(int o) {
  mi[o] = min(mi[o << 1], mi[o << 1 | 1]);
  mi_pos[o] =
      (mi[o << 1] < mi[o << 1 | 1]) ? mi_pos[o << 1] : mi_pos[o << 1 | 1];
}
void build(int l, int r, int o) {
  if (l == r) {
    mi[o] = a[l], mi_pos[o] = l;
    return;
  }
  int m = (l + r) >> 1;
  build(l, m, o << 1), build(m + 1, r, o << 1 | 1);
  push_up(o);
}
void update(int l, int r, int o, int pos, int v) {
  if (l == r) {
    mi[o] = v;
    return;
  }
  int m = (l + r) >> 1;
  if (pos <= m)
    update(l, m, o << 1, pos, v);
  else
    update(m + 1, r, o << 1 | 1, pos, v);
  push_up(o);
}
pair<int, int> query(int l, int r, int o, int ql, int qr) {
  if (ql <= l && r <= qr) return pair<int, int>(mi[o], mi_pos[o]);
  int m = (l + r) >> 1;
  if (ql > m) return query(m + 1, r, o << 1 | 1, ql, qr);
  if (qr <= m) return query(l, m, o << 1, ql, qr);
  return min(query(l, m, o << 1, ql, m),
             query(m + 1, r, o << 1 | 1, m + 1, qr));
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  build(1, n, 1);
  for (int i = 1; i <= n - k; i++) {
    suf[i] = query(1, n, 1, i + 1, i + k).first;
    if (a[i] <= suf[i]) {
      if (!l_bad) l_bad = i;
      r_bad = i;
    }
  }
  if (!r_bad) return 0 * puts("YES");
  if (r_bad + 1 > l_bad + k) return 0 * puts("NO");
  if (r_bad + k + 1 > n) return 0 * puts("NO");
  for (int i = r_bad + 1; i <= n - k; i++) {
    pair<int, int> t = query(1, n, 1, i + 1, i + k);
    update(1, n, 1, t.second, 2000000000);
    if (a[i] <= query(1, n, 1, i + 1, i + k).first) v[t.second].push_back(i);
    update(1, n, 1, t.second, t.first);
  }
  for (int i = r_bad + k + 1; i <= n; i++)
    if (a[i] < a[l_bad]) {
      for (int j = r_bad + 1; j <= l_bad + k; j++) {
        if (a[i] > suf[j] && (!v[i].size() || v[i].back() < j))
          return 0 * puts("YES");
      }
    }
  puts("NO");
  return 0;
}
