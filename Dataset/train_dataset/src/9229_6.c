#include <bits/stdc++.h>
using namespace std;
int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  long long n, m, ta, tb, k;
  cin >> n >> m >> ta >> tb >> k;
  long long a[n];
  long long b[m];
  for (long long i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (long long i = 0; i < m; i++) {
    cin >> b[i];
  }
  if (k >= n) {
    cout << -1;
    return 0;
  }
  long long ans = 0;
  for (long long i = 0; i <= k; i++) {
    long long x = a[i] + ta;
    long long ptr = lower_bound(b, b + m, x) - b;
    ptr += (k - i);
    if (ptr >= m) {
      cout << -1;
      return 0;
    }
    ans = max(b[ptr] + tb, ans);
  }
  cout << ans;
}
