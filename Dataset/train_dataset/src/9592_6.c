#include <bits/stdc++.h>
using namespace std;
const int N = 100005;
long long n[5], t[5], a[N], s[N], b[N];
void down(long long a[], long long p, long long n) {
  long long i = p, t;
  if (p * 2 <= n)
    if (a[p] > a[p * 2]) i = p * 2;
  if (p * 2 + 1 <= n)
    if (a[i] > a[p * 2 + 1]) i = p * 2 + 1;
  if (i == p) return;
  t = a[i];
  a[i] = a[p];
  a[p] = t;
  down(a, i, n);
}
int main() {
  long long m, i, k, x, ans;
  cin >> n[1] >> n[2] >> n[3];
  cin >> t[1] >> t[2] >> t[3];
  cin >> m;
  for (i = 1; i <= m; i++) {
    scanf("%I64d", &a[i]);
    s[i] = a[i];
  }
  for (k = 1; k <= 3; k++) {
    n[k] = min(n[k], m);
    sort(a + 1, a + m + 1);
    memset(b, 0, sizeof(b));
    for (i = 1; i <= m; i++) {
      x = max(a[i], b[1]) + t[k];
      a[i] = b[1] = x;
      down(b, 1, n[k]);
    }
  }
  ans = 0;
  for (i = 1; i <= m; i++) ans = max(ans, a[i] - s[i]);
  cout << ans << endl;
}
