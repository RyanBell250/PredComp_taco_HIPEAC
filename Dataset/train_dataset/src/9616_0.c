#include <bits/stdc++.h>
using namespace std;
signed main() {
  long long n;
  cin >> n;
  long long ans = 0;
  long long L = -4 * 45, R = 45;
  map<long long, long long> vls;
  for (long long i = L; i <= R; i++) vls[i] = 1e18;
  for (long long i = 0; i < 100; i++) {
    for (long long j = 0; j < 100; j++) {
      for (long long k = 0; k < 100; k++) {
        long long nm = -4 * i + 5 * j + 45 * k;
        if (nm >= L && nm <= R) vls[nm] = min(vls[nm], i + j + k);
      }
    }
  }
  for (long long i = L; i <= R; i++) {
    if (vls[i] <= n) {
      ans++;
    }
  }
  for (long long i = L; i < L + 4; i++) {
    long long op = vls[i];
    if (op < n) ans += n - op;
  }
  for (long long i = R - 44; i <= R; i++) {
    long long op = vls[i];
    if (op < n) ans += n - op;
  }
  cout << ans;
  return 0;
}
