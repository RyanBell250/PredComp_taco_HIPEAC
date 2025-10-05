#include <bits/stdc++.h>
using namespace std;
int const MAX = 100 * 100 + 41;
int n, l, r;
int a[MAX];
int b[MAX];
int d[MAX][2];
pair<int, int> c[MAX];
int ans;
bool cmp(pair<int, int> a, pair<int, int> b) {
  if (a.first == b.first) {
    return a.second > b.second;
  } else {
    return a.first < b.first;
  }
}
int calc(int p, int h, int add) {
  if (h < l) return 0;
  int res = 0;
  for (int i = n; i >= p + 1; i--) {
    if (h >= r) break;
    if (c[i].first == 0) break;
    res++;
    h += c[i].second;
  }
  if (h <= r) res += add;
  return res;
}
void solve() {
  for (int i = 1; i <= n; i++) {
    c[i] = make_pair(b[i], a[i]);
  }
  sort(c + 1, c + n + 1, cmp);
  d[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    if (c[i].first) {
      for (int j = 0; j <= MAX - 1; j++) {
        if (d[j][0] && !d[j][1]) {
          ans = max(ans, calc(i, j, 1));
        }
      }
      for (int j = 0; j <= MAX - 1 - c[i].second; j++) {
        if (d[j][1] && !d[j + c[i].second][1]) {
          ans = max(ans, calc(i, j + c[i].second, 1));
        }
      }
      for (int j = 0; j <= MAX - 1 - c[i].second; j++) {
        if (d[j][0] && !d[j + c[i].second][0]) {
          ans = max(ans, calc(i, j + c[i].second, 0));
        }
      }
      for (int j = MAX - 1 - c[i].second; j >= 0; j--) {
        if (d[j][1]) {
          d[j + c[i].second][1] = 1;
        }
      }
      for (int j = 0; j <= MAX - 1; j++) {
        if (d[j][0]) {
          d[j][1] = 1;
        }
      }
      for (int j = MAX - 1 - c[i].second; j >= 0; j--) {
        if (d[j][0]) {
          d[j + c[i].second][0] = 1;
        }
      }
    } else {
      for (int j = MAX - 1 - c[i].second; j >= 0; j--) {
        if (d[j][0]) {
          d[j + c[i].second][0] = 1;
        }
      }
    }
  }
  printf("%d\n", ans);
}
int main() {
  scanf("%d %d %d", &n, &l, &r);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
  }
  solve();
  return 0;
}
