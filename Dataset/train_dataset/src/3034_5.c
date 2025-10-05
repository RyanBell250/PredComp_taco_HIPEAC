#include <bits/stdc++.h>
long long MOD = 1000000009;
long long inf = 1e18;
using namespace std;
long long a[50];
long long b[50];
long long k[50];
long long p[50];
long long u, r, n;
long long ans = -inf;
void Solve(long long x, long long pp) {
  if (x == u) {
    long long temp = 0LL;
    for (long long i = 0; i < n; i++) {
      temp += a[i] * k[i];
    }
    if (temp > ans) ans = temp;
    return;
  }
  if ((u - x) % 2 == 0) {
    long long temp = 0LL;
    for (long long i = 0; i < n; i++) {
      temp += a[i] * k[i];
    }
    if (temp > ans) ans = temp;
  }
  if (pp != 0) {
    for (long long i = 0; i < n; i++) {
      a[i] = a[i] ^ b[i];
    }
    Solve(x + 1, 0LL);
    for (long long i = 0; i < n; i++) {
      a[i] = a[i] ^ b[i];
    }
  }
  long long c[50];
  for (long long i = 0; i < n; i++) {
    c[i] = a[i];
  }
  for (long long i = 0; i < n; i++) {
    a[i] = c[p[i] - 1LL] + r;
  }
  Solve(x + 1, 1LL);
  for (long long i = 0; i < n; i++) {
    a[i] = c[i];
  }
  return;
}
int main() {
  ios::sync_with_stdio(0);
  cin >> n >> u >> r;
  for (long long i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (long long i = 0; i < n; i++) {
    cin >> b[i];
  }
  for (long long i = 0; i < n; i++) {
    cin >> k[i];
  }
  for (long long i = 0; i < n; i++) {
    cin >> p[i];
  }
  Solve(0, 1);
  cout << ans;
  return 0;
}
