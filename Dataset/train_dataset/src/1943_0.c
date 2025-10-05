#include <bits/stdc++.h>
using namespace std;
const int MAXN = 111111;
const int SQ = 200;
int n, m;
vector<int> go[MAXN];
vector<pair<int, int> > qq[MAXN], gg[MAXN];
int ans[MAXN], a[MAXN];
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    --l;
    --r;
    go[r].push_back(l);
  }
  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x;
    --y;
    qq[y].push_back(make_pair(x, i));
  }
  for (int i = 0; i < n; ++i) a[i] = i;
  for (int i = 0; i < n; ++i) {
    if (!go[i].empty()) {
      int l = go[i][0];
      int now = 0;
      int nb = 0;
      for (nb = 0; now + SQ <= l + 1; ++nb, now += SQ) {
        while (!gg[nb].empty() && gg[nb].back().first >= l) gg[nb].pop_back();
        if (gg[nb].empty() || gg[nb].back().second < l) {
          gg[nb].push_back(make_pair(l, i));
        } else {
          gg[nb].back().second = i;
        }
      }
      if (l >= now) {
        for (int j = now; j < now + SQ && j < i; ++j) {
          int x = lower_bound(gg[nb].begin(), gg[nb].end(),
                              make_pair(a[j] + 1, -1)) -
                  gg[nb].begin();
          --x;
          if (x != -1) a[j] = max(a[j], gg[nb][x].second);
        }
        gg[nb].clear();
        for (int j = now; j <= l; ++j)
          if (a[j] >= l) a[j] = max(a[j], i);
      }
    }
    for (auto e : qq[i]) {
      int l = e.first;
      int b = a[l];
      int nb = l / SQ;
      int x = lower_bound(gg[nb].begin(), gg[nb].end(), make_pair(b + 1, -1)) -
              gg[nb].begin();
      --x;
      if (x != -1) b = max(b, gg[nb][x].second);
      ans[e.second] = b;
    }
  }
  for (int i = 0; i < q; ++i) {
    printf("%d\n", ans[i] + 1);
  }
  return 0;
}
