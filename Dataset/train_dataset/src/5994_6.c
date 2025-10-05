#include <bits/stdc++.h>
using namespace std;
const int inf = 1000 * 1000 * 1000;
const int mod = 1000 * 1000 * 1000 + 7;
const int maxn = 2000000;
int n, m;
long long a[maxn], sum[maxn], cur, d, ans, can[maxn];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> d;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
  for (int i = 1; i <= n;) {
    cur = sum[i - 1];
    int j = i - 1;
    while (j + 1 <= n && cur + d >= sum[j + 1] - cur) j++;
    if (j == i - 1) {
      can[0] = true;
      for (int k = 1; k <= j; k++)
        for (int l = sum[j]; l >= 0; l--) can[l + a[k]] |= can[l];
      cur = 0;
      while (cur != sum[j]) {
        int mx = 0;
        for (int k = cur; k <= cur + d; k++)
          if (can[k]) mx = k;
        cur = mx;
        ++ans;
      }
      cout << sum[j] << ' ' << ans;
      return 0;
    }
    i = j + 1;
  }
  can[0] = true;
  for (int k = 1; k <= n; k++)
    for (int l = sum[n]; l >= 0; l--) can[l + a[k]] |= can[l];
  cur = 0;
  while (cur != sum[n]) {
    int mx = 0;
    for (int k = cur; k <= cur + d; k++)
      if (can[k]) mx = k;
    cur = mx;
    ++ans;
  }
  cout << sum[n] << ' ' << ans;
  return 0;
}
