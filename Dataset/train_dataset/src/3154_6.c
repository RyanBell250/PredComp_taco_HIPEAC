#include <bits/stdc++.h>
using namespace std;
int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    long long a, b, c, d, e, f;
    scanf("%lld %lld %lld %lld %lld %lld", &a, &b, &c, &d, &e, &f);
    if (e > f) {
      swap(e, f);
      swap(c, d);
    }
    long long ans = 0;
    for (long long i = 0; i <= c && i * e <= a; ++i) {
      long long j = min(d, (a - i * e) / f);
      long long n = c - i;
      long long m = d - j;
      long long k = min(n, b / e);
      long long l = min(m, (b - k * e) / f);
      ans = max(ans, i + j + k + l);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
