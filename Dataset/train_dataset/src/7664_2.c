#include <bits/stdc++.h>
using namespace std;
struct Q {
  int r1, r2, c1, c2, idx;
};
int n, m, k, q;
Q qs[200000];
vector<int> qAtRow[100001];
vector<int> qAtCol[100001];
vector<int> atCol[100001];
vector<int> atRow[100001];
bool must[200000];
bool res[200000];
int v[100001];
int Z = 400001;
int seg[400001];
int at, val;
void update(int n, int s, int e) {
  if (at < s || at > e) return;
  if (s == e) {
    if (seg[n] == (1 << 29))
      seg[n] = val;
    else
      seg[n] = val;
    return;
  }
  update(n * 2, s, (s + e) / 2);
  update(n * 2 + 1, (s + e) / 2 + 1, e);
  seg[n] = max(seg[n * 2], seg[n * 2 + 1]);
}
int l, r;
int get(int n, int s, int e) {
  if (l > e || r < s) return -1;
  if (s >= l && e <= r) return seg[n];
  return max(get(n * 2, s, (s + e) / 2), get(n * 2 + 1, (s + e) / 2 + 1, e));
}
int main() {
  scanf("%d%d%d%d", &n, &m, &k, &q);
  for (int i = 0; i < k; ++i) {
    int r, c;
    scanf("%d%d", &r, &c);
    atCol[c].push_back(r);
    atRow[r].push_back(c);
  }
  for (int i = 0; i < q; ++i) {
    Q &t = qs[i];
    scanf("%d%d%d%d", &t.r1, &t.c1, &t.r2, &t.c2);
    t.idx = i;
    qAtCol[t.c1].push_back(i);
    qAtRow[t.r1].push_back(i);
  }
  for (int i = 0; i < Z; ++i) seg[i] = 1 << 29;
  for (int i = n; i > 0; --i) {
    for (int j = 0; j < atRow[i].size(); ++j) {
      at = atRow[i][j];
      val = i;
      update(1, 1, m);
    }
    for (int j = 0; j < qAtRow[i].size(); ++j) {
      Q &t = qs[qAtRow[i][j]];
      l = t.c1;
      r = t.c2;
      int a = get(1, 1, m);
      if (a <= 0 || a > t.r2) must[t.idx] = true;
    }
  }
  for (int i = 0; i < Z; ++i) seg[i] = 1 << 29;
  for (int i = m; i > 0; --i) {
    for (int j = 0; j < atCol[i].size(); ++j) {
      at = atCol[i][j];
      val = i;
      update(1, 1, n);
    }
    for (int j = 0; j < qAtCol[i].size(); ++j) {
      Q &t = qs[qAtCol[i][j]];
      l = t.r1;
      r = t.r2;
      int a = get(1, 1, n);
      if (must[t.idx] && (a <= 0 || a > t.c2)) res[t.idx] = true;
    }
  }
  for (int i = 0; i < q; ++i)
    if (res[i])
      puts("NO");
    else
      puts("YES");
  return 0;
}
