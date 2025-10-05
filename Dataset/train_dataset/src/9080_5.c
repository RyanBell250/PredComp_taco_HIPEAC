#include <bits/stdc++.h>
using namespace std;
long long a, b, n;
long long g[100005], s1;
signed main() {
  cin >> a >> b;
  long long l = 1, r = 1e5;
  while (l <= r) {
    long long mid = l + r >> 1;
    if (mid * (mid + 1) / 2 <= a + b)
      n = mid, l = mid + 1;
    else
      r = mid - 1;
  }
  for (long long i = n; i >= 1; i--)
    if (a >= i) {
      a -= i;
      g[i] = 1;
      s1++;
    }
  cout << s1 << endl;
  for (long long i = 1; i <= n; i++)
    if (g[i] == 1) cout << i << ' ';
  cout << endl << n - s1 << endl;
  for (long long i = 1; i <= n; i++)
    if (g[i] == 0) cout << i << ' ';
  return puts(""), 0;
}
