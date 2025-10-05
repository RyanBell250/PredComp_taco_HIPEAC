#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5e5 + 3;
int Te[4 * MAXN], A[MAXN];
void up(int idx, int l, int r, int l1, int r1, int v) {
  if (l > r1 || r < l1) return;
  if (l >= l1 && r <= r1) {
    Te[idx] = v;
    return;
  }
  int md = (l + r) / 2;
  up(idx * 2, l, md, l1, r1, v);
  up(idx * 2 + 1, md + 1, r, l1, r1, v);
  Te[idx] = min(Te[idx * 2], Te[idx * 2 + 1]);
}
int get(int idx, int l, int r, int l1, int r1) {
  if (l >= l1 && r <= r1) return Te[idx];
  if (l > r1 || r < l1) return (1 << 26);
  int md = (l + r) >> 1;
  return min(get(idx * 2, l, md, l1, r1), get(idx * 2 + 1, md + 1, r, l1, r1));
}
vector<pair<int, int> > Q[MAXN];
vector<int> res;
int main() {
  map<int, int> mp;
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%d", &A[i]);
    up(1, 0, n - 1, i, i, (1 << 26));
    mp[A[i]] = -1;
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    Q[b - 1].push_back(make_pair(a - 1, i));
    res.push_back(0);
  }
  for (int i = 0; i < n; i++) {
    sort(Q[i].begin(), Q[i].end());
    int x = mp[A[i]];
    if (x != -1) up(1, 0, n - 1, x, x, i - x);
    mp[A[i]] = i;
    for (int l = 0; l < Q[i].size(); l++)
      res[Q[i][l].second] = get(1, 0, n - 1, Q[i][l].first, i);
  }
  for (int i = 0; i < m; i++) {
    int x = res[i];
    if (x == (1 << 26)) x = -1;
    printf("%d\n", x);
  }
}
