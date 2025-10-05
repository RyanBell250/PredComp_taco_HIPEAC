#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5 + 200;
int n, ai[MAX_N], bi[MAX_N], seq[MAX_N], pos[MAX_N];
vector<pair<int, int> > vec[MAX_N];
pair<int, int> nodes[MAX_N << 2];
pair<int, int> pushup(pair<int, int> ls, pair<int, int> rs) {
  if (ls.first == -1) return rs;
  if (rs.first == -1) return ls;
  return min(ls, rs);
}
void build(int l, int r, int p) {
  if (l == r) return (void)(nodes[p] = make_pair(ai[pos[l]], l));
  build(l, ((l + r) >> 1), (p << 1)),
      build(((l + r) >> 1) + 1, r, ((p << 1) | 1));
  nodes[p] = pushup(nodes[(p << 1)], nodes[((p << 1) | 1)]);
}
pair<int, int> query(int ql, int qr, int l, int r, int p) {
  if (ql <= l && r <= qr) return nodes[p];
  pair<int, int> ls = make_pair(-1, -1), rs = make_pair(-1, -1);
  if (ql <= ((l + r) >> 1)) ls = query(ql, qr, l, ((l + r) >> 1), (p << 1));
  if (((l + r) >> 1) < qr)
    rs = query(ql, qr, ((l + r) >> 1) + 1, r, ((p << 1) | 1));
  return pushup(ls, rs);
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d%d", &ai[i], &bi[i]), vec[ai[i]].push_back(make_pair(bi[i], i));
  set<pair<int, int> > st;
  for (int i = 1; i <= n; i++) {
    st.insert(vec[i].begin(), vec[i].end());
    seq[st.begin()->second] = i;
    pos[i] = st.begin()->second;
    st.erase(st.begin());
  }
  build(1, n, 1);
  for (int i = 1; i <= n; i++) {
    if (i + 1 > bi[pos[i]]) continue;
    pair<int, int> res = query(i + 1, bi[pos[i]], 1, n, 1);
    if (res.first <= i) {
      puts("NO");
      for (int i = 1; i <= n; i++) printf("%d ", seq[i]);
      puts("");
      swap(seq[pos[res.second]], seq[pos[i]]);
      for (int i = 1; i <= n; i++) printf("%d ", seq[i]);
      puts("");
      exit(0);
    }
  }
  puts("YES");
  for (int i = 1; i <= n; i++) printf("%d ", seq[i]);
  puts("");
  return 0;
}
