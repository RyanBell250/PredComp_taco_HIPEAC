#include <bits/stdc++.h>
using namespace std;
int a[1000002];
int d[1000002];
int ans;
int main() {
  int n, m = 1e6, i, j, x;
  cin >> n;
  for (i = 1; i <= n; i++) {
    scanf("%d", &x);
    a[x]++;
  }
  for (i = 1; i <= m; i++) {
    if (a[i]) {
      d[i] = max(d[i], a[i]);
      for (j = 2 * i; j <= m; j += i) {
        d[j] = max(d[j], d[i] + a[j]);
      }
    }
  }
  for (i = 1; i <= m; i++) ans = max(ans, d[i]);
  cout << ans;
}
