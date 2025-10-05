#include <bits/stdc++.h>
using namespace std;
int main() {
  const long M = 1000001;
  vector<long> v(M, 0);
  long n;
  cin >> n;
  for (long p = 0; p < n; p++) {
    long a, b;
    cin >> a >> b;
    v[a] = b;
  }
  long ma(0);
  vector<long> f(M, 0);
  f[0] = (v[0] > 0) ? 1 : 0;
  for (long p = 1; p < M; p++) {
    if (v[p] > 0) {
      if (p - v[p] - 1 < 0)
        f[p] = 1;
      else
        f[p] = f[p - v[p] - 1] + 1;
    } else
      f[p] = f[p - 1];
    ma = max(f[p], ma);
  }
  cout << n - ma;
  return 0;
}
