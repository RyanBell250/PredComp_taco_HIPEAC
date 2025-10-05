#include <bits/stdc++.h>
#pragma GCC target("pclmul")
using ul = std::uint32_t;
using ull = std::uint64_t;
using li = std::int32_t;
using ll = std::int64_t;
using llf = long double;
using uss = std::uint8_t;
ul n, m;
const ul maxn = 5e5;
const ul maxm = 2 * maxn;
char a[maxn + 2];
char b[maxn + 2];
char s[maxm + 2];
char sa[maxm + maxn + 1];
char srbr[maxm + maxn + 1];
ul zsa[maxm + maxn + 1];
ul zsrbr[maxm + maxn + 1];
void getz(const char str[], ul z[], ul len) {
  z[1] = len;
  for (ul i = 2, l = 1, r = 1; i <= len; ++i) {
    ul tar = i - l + 1, mx = std::max(i, r + 1) - i;
    z[i] = std::min(z[tar], mx);
    while (i + z[i] <= len && str[i + z[i]] == str[z[i] + 1]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      r = i + z[i] - 1;
      l = i;
    }
  }
}
ul f(ul x) { return zsa[x + m]; }
ul g(ul x) { return zsrbr[n + 1 - x + m]; }
class node {
 public:
  ull sum = 0;
  ul cnt = 0;
  ul lson = 0;
  ul rson = 0;
};
node tree[maxn * 20 + 1];
ul tim = 0;
void insert(ul pos, ul v, ul nl, ul nr, ul oid, ul& nid) {
  ++tim;
  nid = tim;
  tree[nid] = tree[oid];
  tree[nid].sum += v;
  ++tree[nid].cnt;
  if (nl == nr) {
    return;
  }
  ul midl = nl + nr >> 1;
  ul midr = midl + 1;
  if (pos <= midl) {
    insert(pos, v, nl, midl, tree[nid].lson, tree[nid].lson);
  } else {
    insert(pos, v, midr, nr, tree[nid].rson, tree[nid].rson);
  }
}
void query(ul l, ul r, ul nl, ul nr, ul nid, ul& c, ull& s) {
  if (l <= nl && r >= nr) {
    c += tree[nid].cnt;
    s += tree[nid].sum;
    return;
  }
  ul midl = nl + nr >> 1;
  ul midr = midl + 1;
  if (l <= midl && tree[nid].lson) {
    query(l, r, nl, midl, tree[nid].lson, c, s);
  }
  if (r >= midr && tree[nid].rson) {
    query(l, r, midr, nr, tree[nid].rson, c, s);
  }
}
std::pair<ul, ul> bpbl[maxn + 1];
ul lentonid[maxn + 2];
int main() {
  std::scanf("%u%u%s%s%s", &n, &m, a + 1, b + 1, s + 1);
  std::memcpy(sa + 1, s + 1, m);
  std::memcpy(sa + m + 1, a + 1, n);
  sa[m] = 0;
  getz(sa, zsa, m + n);
  std::memcpy(srbr + 1, s + 1, m);
  std::memcpy(srbr + m + 1, b + 1, n);
  std::reverse(srbr + 1, srbr + m + 1);
  std::reverse(srbr + m + 1, srbr + m + n + 1);
  srbr[m] = 0;
  getz(srbr, zsrbr, m + n);
  for (ul i = 1; i <= n; ++i) {
    bpbl[i].first = i;
    bpbl[i].second = g(i);
  }
  std::sort(bpbl + 1, bpbl + n + 1,
            [](const std::pair<ul, ul>& a, const std::pair<ul, ul>& b) {
              return a.second > b.second;
            });
  for (ul i = n, j = 1; i >= 1; --i) {
    while (j <= n && bpbl[j].second > i) {
      ++j;
    }
    lentonid[i] = lentonid[i + 1];
    for (ul k = j; k <= n && bpbl[k].second == i; ++k) {
      insert(bpbl[k].first, i, 1, n, lentonid[i], lentonid[i]);
    }
  }
  ull ans = 0;
  for (ul i = 1; i <= n; ++i) {
    ul c = 0;
    ull s = 0;
    query(i, i + m - 2, 1, n, lentonid[std::min(m - f(i), n + 1)], c, s);
    ans += s - ull(c) * ull(m - f(i) - 1);
  }
  std::printf("%llu\n", ans);
  return 0;
}
