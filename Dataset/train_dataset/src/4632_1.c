#include <bits/stdc++.h>
const int maxn = 200005;
using namespace std;
long long money[maxn], c[maxn];
int main() {
  ios::sync_with_stdio(false);
  long long n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> money[i];
  long long ans = 0;
  for (long long d = 1; d <= m / n; d++) {
    c[n - 1] = money[n - 1];
    for (int i = n - 2; i >= 0; i--) c[i] = min(money[i], c[i + 1] - d);
    if (c[0] < ((d - 1) * n + 2) * d / 2) continue;
    long long sum = (2 * m - (d + 1) * n + 2) * d / 2;
    long long s = max(1LL, m - d * n + 1 - max(0LL, (sum - c[0])));
    long long space = (m - s + 1 - n * d);
    long long base = min(c[0], sum), ben = 0;
    ben += base;
    for (int i = 1; i < n; i++) {
      base += d;
      ben += base;
      c[i] -= base;
      long long shift = min(c[i], space);
      ben += shift;
      base += shift;
      space -= shift;
    }
    ans = max(ans, ben);
  }
  cout << ans << endl;
  return 0;
}
