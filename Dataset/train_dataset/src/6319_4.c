#include <bits/stdc++.h>
using namespace std;
template <class P, class Q>
inline void smin(P &a, Q b) {
  if (b < a) a = b;
}
template <class P, class Q>
inline void smax(P &a, Q b) {
  if (a < b) a = b;
}
const int maxn = 100 + 10;
const int ctv = 32;
int n, t;
int a[maxn];
int cnt[999];
int ldp[3 * maxn][maxn], rdp[3 * maxn][maxn];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> t;
  for (int i = 0, _n = (int)(n); i < _n; i++) cin >> a[i], cnt[a[i]]++;
  for (int i = 0, _n = (int)(2 * n + ctv); i < _n; i++)
    for (int j = 0, _n = (int)(n); j < _n; j++) {
      for (int k = 0, _n = (int)(j); k < _n; k++)
        if (a[k] <= a[j]) smax(ldp[i][j], ldp[i][k]);
      if (i)
        for (int k = (int)(j), _n = (int)(n); k < _n; k++)
          if (a[k] <= a[j]) smax(ldp[i][j], ldp[i - 1][k]);
      ldp[i][j]++;
    }
  for (int i = 0, _n = (int)(2 * n + ctv); i < _n; i++)
    for (int j = (int)(n), _x = (int)(0); j-- > _x;) {
      for (int k = (int)(n), _x = (int)(j + 1); k-- > _x;)
        if (a[j] <= a[k]) smax(rdp[i][j], rdp[i][k]);
      if (i)
        for (int k = (int)(j + 1), _x = (int)(0); k-- > _x;)
          if (a[j] <= a[k]) smax(rdp[i][j], rdp[i - 1][k]);
      rdp[i][j]++;
    }
  if (t <= 2 * n + ctv)
    cout << *max_element(ldp[t - 1], ldp[t - 1] + n) << '\n';
  else {
    int ans = 0;
    for (int i = 0, _n = (int)(n); i < _n; i++)
      for (int j = 0, _n = (int)(n); j < _n; j++)
        if (a[i] == a[j])
          smax(ans, ldp[n + ctv / 2 - 1][i] + cnt[a[i]] * (t - 2 * n - ctv) +
                        rdp[n + ctv / 2 - 1][j]);
    cout << ans << '\n';
  }
  return 0;
}
