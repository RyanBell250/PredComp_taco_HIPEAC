#include <bits/stdc++.h>
using namespace std;
const long long N = 1e6 + 5;
const double eps = 1e-9;
const long long INF = 1e18;
long long n, P;
long long fac[N];
signed main() {
  cin >> n >> P;
  fac[0] = 1;
  for (long long i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % P;
  long long ans = 0;
  for (long long i = 1; i <= n; i++) {
    long long tmp = fac[i] * (n - i + 1) % P * fac[n - i + 1] % P;
    ans = (ans + tmp) % P;
  }
  cout << ans << endl;
  return 0;
}
