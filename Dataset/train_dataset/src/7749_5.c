#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
const int N = 100010;
const int M = 50004;
const int LOG = 16;
int sparse[LOG][M];
long long a[N];
long long pref[N];
long long prefSum[N];
int n;
long long solveTriang(long long A, long long B, long long C) {
  if (C < 0) return 0;
  if (A > B) swap(A, B);
  long long p = C / B;
  long long k = B / A;
  long long d = (C - p * B) / A;
  return solveTriang(B - k * A, A, C - A * (k * p + d + 1)) +
         (p + 1) * (d + 1) + k * p * (p + 1) / 2;
}
long long solve2(long long A, long long CA, long long B, long long CB,
                 long long C) {
  if (C >= A * CA + B * CB) return CA * CB;
  if (C < 0) return 0;
  return solveTriang(A, B, C) - solveTriang(A, B, C - A * CA) -
         solveTriang(A, B, C - B * CB) + solveTriang(A, B, C - A * CA - B * CB);
}
long long solve(long long B) {
  long long ans = 0;
  for (int i = 1; i < n; i++)
    if (a[i] > 0) {
      long long L = min(a[i], B / i);
      ans += L * (a[i] + 1) - L * (L + 1) / 2;
    }
  int r = 1;
  for (int l = 1; l < n; l++) {
    if (a[l] == 0) continue;
    if (r > l) ans += a[l] * (pref[r - 1] - pref[l]);
    while (r < n && prefSum[r] - prefSum[l] <= B) {
      if (r > l && a[r] > 0)
        ans +=
            solve2(l, a[l], r, a[r], B - (prefSum[r - 1] - prefSum[l]) - l - r);
      r++;
    }
    if (r == n) continue;
    ans += solve2(l, a[l], r, a[r], B - (prefSum[r - 1] - prefSum[l]) - l - r);
  }
  return ans;
}
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &sparse[0][i]);
  for (int k = 0; k < LOG - 1; k++)
    for (int i = 0; i < n; i++)
      sparse[k + 1][i] =
          gcd(sparse[k][i], (i + (1 << k) < n ? sparse[k][i + (1 << k)] : 0));
  for (int l = 0; l < n; l++) {
    int cur = 0;
    int r = l;
    while (r < n) {
      cur = gcd(cur, sparse[0][r]);
      int rr = r;
      for (int k = LOG - 1; rr < n && k >= 0; k--) {
        int x = sparse[k][rr];
        if (x % cur == 0) {
          rr += (1 << k);
        }
      }
      rr = min(n, rr);
      a[cur] += rr - r;
      r = rr;
    }
  }
  long long m = (long long)n * (n + 1) / 2;
  m = m * (m + 1) / 2;
  m = (m + 1) / 2;
  n = N;
  for (int i = 1; i < n; i++) {
    pref[i] = pref[i - 1] + a[i];
    prefSum[i] = prefSum[i - 1] + a[i] * i;
  }
  long long l = -1, r = prefSum[n - 1];
  while (r - l > 1) {
    long long x = (l + r) / 2;
    if (solve(x) >= m)
      r = x;
    else
      l = x;
  }
  printf("%lld\n", r);
  return 0;
}
