#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10;
vector<int> G[maxn], rp[maxn];
int dfn[maxn], coc, bel[maxn], blo, crash[maxn][2], id[maxn], maxr[maxn];
bool ins[maxn];
long long ans[maxn];
stack<int> s;
set<int> lp;
pair<int, int> query[maxn];
inline int tarjan(int k, int fa) {
  int lowu = dfn[k] = ++coc;
  ins[k] = true;
  s.push(k);
  for (int i = 0; i < G[k].size(); i++) {
    int v = G[k][i];
    if (v == fa) continue;
    if (!dfn[v]) {
      int lowv = tarjan(v, k);
      lowu = min(lowu, lowv);
    } else if (ins[v])
      lowu = min(lowu, dfn[v]);
  }
  if (lowu == dfn[k]) {
    crash[blo][0] = crash[blo][1] = k;
    int size = 0;
    while (ins[k]) {
      int v = s.top();
      s.pop();
      size++;
      ins[v] = false;
      bel[v] = blo;
      crash[blo][0] = min(crash[blo][0], v);
      crash[blo][1] = max(crash[blo][1], v);
    }
    if (size != 1) blo++;
  }
  return lowu;
}
inline bool cmp(int x, int y) { return query[x] > query[y]; }
struct node {
  long long sum[maxn << 3], all[maxn << 3];
  inline void update(int p, int lp, int rp, int l, int r, long long v) {
    if (l == lp && r == rp) return void(all[p] += v);
    sum[p] += (r - l + 1) * v;
    int mid = lp + rp >> 1;
    if (r <= mid)
      update(p << 1, lp, mid, l, r, v);
    else if (l > mid)
      update(p << 1 | 1, mid + 1, rp, l, r, v);
    else
      update(p << 1, lp, mid, l, mid, v),
          update(p << 1 | 1, mid + 1, rp, mid + 1, r, v);
  }
  inline long long query(int p, int lp, int rp, int l, int r) {
    long long rtn = all[p] * (r - l + 1);
    if (l == lp && r == rp) return rtn + sum[p];
    int mid = lp + rp >> 1;
    if (r <= mid)
      return query(p << 1, lp, mid, l, r) + rtn;
    else if (l > mid)
      return query(p << 1 | 1, mid + 1, rp, l, r) + rtn;
    else
      return query(p << 1, lp, mid, l, mid) +
             query(p << 1 | 1, mid + 1, rp, mid + 1, r) + rtn;
  }
} S;
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) tarjan(i, 0);
  for (int i = 0; i < blo; i++) {
    rp[crash[i][0]].push_back(crash[i][1]);
    lp.insert(crash[i][1]);
  }
  for (int i = 1; i <= n; i++) {
    maxr[i] = lp.size() ? *lp.begin() - 1 : n;
    for (int j = 0; j < rp[i].size(); j++) lp.erase(rp[i][j]);
  }
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; i++)
    scanf("%d%d", &query[i].first, &query[i].second), id[i] = i;
  sort(id + 1, id + 1 + q, cmp);
  int minl = n + 1;
  for (int i = 1; i <= q; i++) {
    while (minl > query[id[i]].first)
      S.update(1, 1, n, minl - 1, maxr[minl - 1], 1), --minl;
    ans[id[i]] = S.query(1, 1, n, query[id[i]].first, query[id[i]].second);
  }
  for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
  return 0;
}
