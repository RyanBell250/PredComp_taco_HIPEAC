#include <bits/stdc++.h>
using namespace std;
const int N = 530;
const long long mod = 1000000007;
inline long long pw(long long a, long long b) {
  long long r = 1;
  a %= mod;
  for (; b; b >>= 1, a = a * a % mod)
    if (b & 1) r = r * a % mod;
  return r;
}
int f, b, p[N], c[N], k;
long long n, a[N], bs[N], t[N], md[N], res[N];
inline void mul(long long* a, long long* b) {
  for (int i = 0; i < k + k; i++) t[i] = 0;
  for (int i = 0; i < k; i++)
    if (a[i])
      for (int j = 0; j < k; j++) t[i + j] = (t[i + j] + a[i] * b[j]) % mod;
  for (int i = k + k - 1; i >= k; i--)
    if (t[i])
      for (int j = 0; j <= k; j++)
        t[i - k + j] = (t[i - k + j] + t[i] * md[j]) % mod;
  for (int i = 0; i < k; i++) a[i] = t[i];
}
void pw(long long* a, long long b) {
  for (int i = 0; i < k; i++) res[i] = 0;
  res[0] = 1;
  for (; b; b >>= 1, mul(a, a))
    if (b & 1) mul(res, a);
  for (int i = 0; i < k; i++) a[i] = res[i];
}
int main() {
  scanf("%d%d%lld", &f, &b, &n);
  for (int i = 0; i < f; i++) scanf("%d", &p[i]);
  for (int i = 0; i < b; i++) scanf("%d", &c[i]), k = max(k, c[i]);
  for (int i = 0; i < b; i++) md[k - c[i]]++;
  for (int i = 0; i < f; i++) {
    for (int j = 0; j < k; j++) a[j] = 0;
    a[1] = 1;
    if (k == 1) a[0] = md[0];
    pw(a, p[i]);
    for (int j = 0; j < k; j++) bs[j] = (bs[j] + a[j]) % mod;
  }
  pw(bs, n);
  for (int i = k - 1; i; i--)
    if (bs[i])
      for (int j = 0; j <= k; j++)
        if (i - k + j >= 0)
          bs[i - k + j] = (bs[i - k + j] + bs[i] * md[j]) % mod;
  printf("%lld\n", bs[0]);
  return 0;
}
